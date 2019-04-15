/// \file main.cpp
///

#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unordered_set>
#include <string.h>
#include "control.hpp"
#include <stdio.h>
#include <unistd.h>

#include "user.hpp"
#include "config.hpp"

static char buffer[PATH_MAX];

inline bool operator==(const user_unit &lhs, const user_unit &rhs) {
    return lhs.sock == rhs.sock;
}

inline bool operator!=(const user_unit &lhs, const user_unit &rhs) {
    return !(rhs == lhs);
}

template <>
struct std::hash<user_unit> {
    size_t operator() (const user_unit user) {
        return user.sock;
    }
};


int main() {
    int ser_sock;
    ser_sock = socket(AF_INET, SOCK_STREAM, 0);

    std::unordered_set<user_unit> users;

    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);

    int max_fd;

   
    for(;;) {
        FD_SET(ser_sock, &read_fds);
        max_fd = ser_sock;

        for (auto & user : users) {
            FD_SET(user.sock, &read_fds);
            max_fd = std::max(max_fd, user.sock);
            if (user.data_sock != -1) {
                if (user.state == uploading)
                    FD_SET(user.data_sock, &read_fds);
                else if (user.state == downloading)
                    FD_SET(user.data_sock, &write_fds);
                max_fd = std::max(max_fd, user.data_sock);
            }   
        }


        if (select(max_fd+1 , &read_fds, &write_fds, NULL, NULL) < 0)
            exit(1);
        
        for (auto & user : users) {
            if (recv(user.sock, buffer, buffer_size, 0) <= 0) {
                exit(&user);
                continue;
            }
            
            switch(user.state) {
                case connected:
                    break;
                case identifying:
                    break;
                case ready:
                    break;
                case uploading:
                    break;
                case downloading:
                    break;
            }
        }
    }
}