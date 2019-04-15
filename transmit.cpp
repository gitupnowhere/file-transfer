/// \file transmit.cpp
///

#include "transmit.hpp"


/// \brief 处理put请求
/// \details
/// 在ready状态下运行
/// 不需要检查用户状态
/// 生成用于标示文件的stream_id
/// 根据文件名以只读方式打开文件
/// 将对应的stream_id和FILE*加入到fps中
/// 从管理连接发送对应的put_ok回应报文
/// 用户转为uploading状态
///
/// \param user 待处理事件的用户
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int put(user_unit * user, char * filename) {
    return 0;
}

/// \brief 处理get请求
/// \details
/// 根据文件名以写方式打开文件
/// 将对应的stream_id和FILE*加入到fps中
/// 从管理连接发送对应的get_ok回应报文
/// 用户转为downloading状态
///
/// \param user 待处理事件的用户
/// \param stream_id 用于标示文件的stream_id
/// \param filename 文件名
/// \return 正常返回0 错误返回-1
int get(user_unit * user, uint8_t stream_id, char * filename) {
    return 0;
}