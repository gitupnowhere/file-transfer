/// \file user.cpp
///

#include "user.hpp"

user_unit::user_unit(int sock) : sock(sock) {
    username[0] = '\0';
    state = connected;
    pwd[0] = '\0';
    data_sock = -1;
    memset(&recv_protocol_head_buffer, 0, sizeof(recv_protocol_head_buffer));
    memset(recv_buffer, 0, sizeof(recv_buffer));
}

/// \brief 由用户名查询密码
/// \param user 用户
/// \param out_string 用于储存结果的字符串
/// \param str_size 储存区域的大小
/// \return 正常返回0 错误返回-1
int password(const user_unit * user, char * out_string, size_t str_size) {
    return 0;
}

/// \brief 修改用户密码
/// \param user 用户
/// \param new_password 储存新密码的字符串
/// \return 正常返回0 错误返回-1
int change_password(const user_unit * user, char * new_password) {
    return 0;
}