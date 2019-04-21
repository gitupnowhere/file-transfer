/// \file user.hpp
///

#ifndef USER_HPP
#define USER_HPP

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <unordered_map>
#include "protocol.h"
#include "config.hpp"

enum states {connected, identifying, data_linking, ready};

struct user_unit {
    /// 接收控制信息的套接字
    const int sock;

    /// 用户名
    char username[NAME_MAX + 4];

    /// 用户状态
    states state;

    /// 当前工作目录
    char pwd[PATH_MAX + 4];

    /// 用于接收数据的套接字
    int data_sock;

    /// 下载的stream_id到只读FILE*的映射
    std::unordered_map<stream_id_t, FILE*> read_fps;

    /// 记录传输超时的时刻
    std::unordered_map<stream_id_t, clock_t> timeout_stamp;

    /// 上传的stream_id到只读FILE*的映射
    std::unordered_map<stream_id_t, FILE*> write_fps;

    /// 用于缓存未处理完的报文的头部的信息
    protocol_head recv_protocol_head_buffer;

    /// 接收缓存
    char recv_buffer[buffer_size];

    explicit user_unit(int sock);
};

inline bool operator==(const user_unit &lhs, const user_unit &rhs) {
    return lhs.sock == rhs.sock;
}

inline bool operator!=(const user_unit &lhs, const user_unit &rhs) {
    return !(rhs == lhs);
}

namespace std {
    template<>
    struct hash<user_unit> {
        size_t operator()(const user_unit &user) {
            return user.sock;
        }
    };
}

/// \brief 由用户名查询密码
/// \param user
/// \param out_string 用于储存结果的字符串
/// \param str_size 储存区域的大小
/// \return 正常返回0 错误返回-1
int password(const user_unit * user, char * out_string, size_t str_size);

/// \brief 修改用户密码
/// \param user 用户
/// \param new_password 储存新密码的字符串
/// \return 正常返回0 错误返回-1
int change_password(const user_unit * user, char * new_password);


#endif // user.hpp