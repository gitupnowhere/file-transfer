/// \file config.hpp
/// \brief 定义程序中所有约定的设置

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <climits>
#include <cstdio>

/// 缓冲区大小
const size_t buffer_size = 3000;

/// 命令接收端口
const int cmd_port = 60000;

///
const int max_transmissions = 3;

#endif //CONFIG_HPP
