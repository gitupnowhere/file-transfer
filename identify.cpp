/// \file identify.cpp
///

#include "identify.hpp"



/// \brief 处理login请求
/// \details
/// 在connected状态下
/// 将用户名写入user_unit结构体中
/// 不需要对于用户名的合法性做审查
/// 调用calloc函数为chap数据记录分配空间
/// 将指针记录在chap_map中
/// 生成质询数据
/// 发送chap数据
/// 然后转达identifying状态
///
/// \param user 待处理的用户
/// \param username 从报文中获取的用户名
/// \return 正常返回0 错误返回-1
int login(user_unit * user, char * username, std::unordered_map<user_unit, char*> chap_map) {
    return 0;
}

/// \brief 核查质询结果
/// \details
/// 调用password函数获知用户密码
/// 计算chap的正确结果
/// 将回应结果与其比对
/// 判断用户是否通过
/// 无论用户是否通过或发生任何错误
/// 必须调用free将chap_map中指针指向的内存释放
/// 必须调用chap_map.erase擦出对应元素
///
/// \param user 待核查用户
/// \param chap_ans 待核查结果
/// \return 用户通过返回0 否则返回-1
int chap(user_unit * user, char * chap_ans, std::unordered_map<user_unit, char*> chap_map) {
    return 0;
}