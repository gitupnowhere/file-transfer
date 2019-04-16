/// \file identify.hpp
///

#ifndef IDENTIFY_HPP
#define IDENTIFY_HPP

#include "user.hpp"

#include <unordered_map>

/// \brief 处理login请求
/// \param user 待处理的用户
/// \param username 从报文中获取的用户名
/// \param chap_map 记录质询数据的字典
/// \return 正常返回0 错误返回-1
int login(user_unit * user, char * username, std::unordered_map<user_unit, char*> & chap_map);

/// \brief 核查质询结果
/// \param user 待核查用户
/// \param chap_ans 待核查结果
/// \param chap_map 记录质询数据的字典
/// \return 用户通过返回0 否则返回-1
int chap(user_unit * user, char * chap_ans, std::unordered_map<user_unit, char*> & chap_map);

#endif //IDENTIFY_HPP
