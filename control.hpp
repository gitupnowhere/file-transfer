/// \file control.hpp
///

#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "user.hpp"

/// \brief 处理显示当前路径下文件和路径的请求
/// \param user 待处理请求的用户
/// \return 正常返回0 错误返回-1
int ls(const user_unit * user);

/// \brief 处理变更当前工作路径的请求
/// \param user 待处理请求的用户
/// \param path 路径名
/// \return 正常返回0 错误返回-1
int cd(user_unit * user, char * path);

/// \brief 处理创建路径的请求
/// \param user 待处理请求的用户
/// \param arg 新路径名
/// \return 正常返回0 错误返回-1
int mkdir(const user_unit * user, char * arg);

/// \brief 用户退出时 释放一切用户资源
/// \param user 用户
/// \return 正常返回0 错误返回-1
int exit(const user_unit * user);


#endif //CONTROL_HPP
