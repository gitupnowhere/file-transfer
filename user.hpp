/// \file user.hpp
///

#ifndef USER_HPP
#define USER_HPP

#include <stdio.h>
#include <limits.h>
#include <unordered_map>
#include "protocol.h"

enum states {connected, identifying, data_linking, ready, uploading, downloading};

struct user_unit {
    /// 接收控制信息的套接字
    int sock;

    /// 用户名
    char username[NAME_MAX + 4];

    /// 用户状态
    states state;

    /// 当前工作目录
    char pwd[PATH_MAX + 4];

    /// 用于接收数据的套接字
    int data_sock;

    /// stream_id到FILE*的映射
    std::unordered_map<stream_id_t, FILE*> fps;
};


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