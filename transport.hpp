/// \file transport.hpp
///

#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include "protocol.h"
#include "user.hpp"

/// \brief 处理put请求
/// \param user 待处理事件的用户
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int put(user_unit * user, char * filename);

/// \brief 处理get请求
/// \param user 待处理事件的用户
/// \param stream_id 用于标示文件的stream_id
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int get(user_unit * user, uint8_t stream_id, char * filename);

/// \brief 在数据连接上处理信息
/// \param user 待处理的用户
/// \return 正常返回0 错误返回-1
int transport(user_unit * user);

#endif //TRANSPORT_HPP
