/// \file main.cpp
///

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <random>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#include "protocol.h"
#include "user.hpp"
#include "config.hpp"
#include "identify.hpp"
#include "transport.hpp"
#include "control.hpp"

uint16_t random_port(int sock);

uint16_t random_port(int sock) {
    sockaddr_in addr;
    static std::default_random_engine eg;
    std::uniform_int_distribution<uint16_t> dic(random_port_low_limit, random_port_up_limit);
    memset(&addr,0, sizeof(addr));
    addr.sin_family = AF_INET;
    for (;;) {
        addr.sin_port = htons(dic(eg));
        if (bind(sock, (sockaddr *)&addr, sizeof(addr)) == 0)
            break;
        if (errno != EADDRINUSE) {
            perror("");
            exit(errno);
        }
    }
    errno = 0;
    return addr.sin_port;
}

int main() {
    int ser_sock;
    ser_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (ser_sock == -1) {
        perror("socket create error:");
        exit(errno);
    }

    sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(cmd_port);

    if (bind(ser_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) != 0) {
        perror("bind error:");
        exit(errno);
    }

    listen(ser_sock, 0);


    std::unordered_map<int, user_unit> users;

    fd_set read_fds, write_fds;
    int max_fd;

    static char buffer[buffer_size];

    std::unordered_map<int, char*> chap_data;
    std::unordered_map<int, int> temp_sock;

    timeval t = select_timeout;

    for(;;) {
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);

        FD_SET(ser_sock, &read_fds);
        max_fd = ser_sock;

        for (auto & item : users) {
            auto & user = item.second;
            FD_SET(user.sock, &read_fds);
            max_fd = std::max(max_fd, user.sock);
        }

        for (auto & item : temp_sock) {
            FD_SET(item.second, &read_fds);
            max_fd = std::max(max_fd, item.second);
        }



        if (select(max_fd+1 , &read_fds, &write_fds, NULL, &t) < 0)
            exit(errno);

        if (FD_ISSET(ser_sock, &read_fds)) {
            int sock = accept(ser_sock, nullptr, nullptr);
            users.emplace(sock, user_unit(sock));
        }


        for (auto & item : users) {

            auto & user = item.second;

            if (FD_ISSET(user.sock, &read_fds)) {
                if (recv(user.sock, buffer, 4, 0) <= 0) {
                    exit(&user);
                    users.erase(user.sock);
                    continue;
                }

                protocol_head head;
                int head_len = 0;

                head_len += str_to_proto(buffer, sizeof(buffer), &head.common_head, nullptr);

                recv(user.sock, buffer+head_len, head.common_head.length-head_len, 0);
                head_len += str_to_proto(buffer, sizeof(buffer)-head_len, nullptr, &head.options);

                buffer[head.common_head.length] = '\0';


                switch (user.state) {
                    case connected:
                        if (head.common_head.command != LOGIN)
                            break;
                        buffer[head.common_head.length] = '\0';
                        login(&user, buffer+head_len, chap_data);
                        break;
                    case identifying:
                        if (head.common_head.command != CHAP_ANS)
                            break;
                        if (chap(&user, buffer+head_len, chap_data) != 0)
                            break;
                        memset(&head, 0, sizeof(head));
                        head.common_head.command = PASSED;
                        head.common_head.length = 8 + 2;
                        proto_to_str(&head, buffer, buffer_size);
                        temp_sock[user.sock] = socket(AF_INET, SOCK_STREAM, 0);
                        *(uint16_t *)(buffer+head_len) = random_port(temp_sock[user.sock]);
                        send(user.sock, buffer, 8+2, 0);
                        listen(temp_sock[user.sock], 2);
                        user.state = data_linking;
                        break;
                    case data_linking:
                        if (! FD_ISSET(temp_sock[user.sock], &read_fds))
                            break;
                        sockaddr_in addr1, addr2;
                        socklen_t len1, len2;
                        user.data_sock = accept(temp_sock[user.sock], (sockaddr *)&addr1, &len1);
                        getsockname(user.sock, (sockaddr *)&addr2, &len2);
                        if (memcmp(&addr1.sin_addr, &addr2.sin_addr, sizeof(addr1.sin_addr)) == 0) {
                            close(temp_sock[user.sock]);
                            temp_sock.erase(user.data_sock);
                            user.state = ready;
                        } else {
                            user.data_sock = -1;
                        }
                        break;
                    case ready:
                        if (!user.read_fps.empty() || !user.write_fps.empty())
                            transport(&user);
                        switch (head.common_head.command) {
                            case EXIT:
                                exit(&user);
                                break;
                            case GET:
                                get(&user, *(uint8_t *)(buffer+head_len), buffer+head_len+1);
                                break;
                            case PUT:
                                put(&user, buffer+head_len);
                                break;
                            case LS:
                                ls(&user);
                                break;
                            case CD:
                                cd(&user, buffer+head_len);
                                break;
                            case MKDIR:
                                mkdir(&user, buffer+head_len);
                                break;
                            case CHPASSWD:
                                change_password(&user, buffer+head_len);
                                memset(&head, 0, sizeof(head));
                                head.common_head.command = CHPASSWD_OK;
                                head.common_head.length = 8;
                                proto_to_str(&head, buffer, sizeof(buffer));
                                send(user.sock, buffer, 8, 0);
                            default:
                                memset(&head, 0, sizeof(head));
                                head.common_head.command = BAD_CMD;
                                head.common_head.length = 8;
                                proto_to_str(&head, buffer, sizeof(buffer));
                                send(user.sock, buffer, 8, 0);
                        }
                        break;
                }
            }
        }
    }
}