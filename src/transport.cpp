/// \file transport.cpp
///

#include "transport.hpp"
#include "user.hpp"

/// \brief 处理put请求
/// \details
/// 在ready状态下
/// 收到对应请求时
/// 调用该函数
/// 不需要检查用户状态
/// 生成用于标示文件的stream_id
/// 根据文件名以只读方式打开文件
/// 将对应的stream_id和FILE*加入到read_fps中
/// 从管理连接发送对应的put_ok回应报文
///
/// \param user 待处理事件的用户
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int put(user_unit * user, char * filename) {
    return 0;
}

/// \brief 处理get请求
/// \details
/// 在ready状态下
/// 收到对应请求时
/// 调用该函数
/// 不需要检查用户状态
/// 根据文件名以写方式打开文件
/// 将对应的stream_id和FILE*加入到write_fps中
/// 从管理连接发送对应的get_ok回应报文
///
/// \param user 待处理事件的用户
/// \param stream_id 用于标示文件的stream_id
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int get(user_unit * user, uint8_t stream_id, char * filename) {
    return 0;
}

/// \brief 在数据连接上处理信息
/// \details
/// 在user->read_fds不为空或user->write_fds不为空时调用
///
/// \param user 待处理的用户
/// \return 正常返回0 错误返回-1
int transport(user_unit * user) {
    return 0;
}
