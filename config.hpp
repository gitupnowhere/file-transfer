/// \file config.hpp
/// \brief 定义程序中所有约定的设置

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <climits>
#include <cstdio>
#include <sys/select.h>

/// 缓冲区大小
const size_t buffer_size = 3000;

/// 命令接收端口
const int cmd_port = 60000;

///
const int max_transmissions = 3;

const uint16_t random_port_low_limit = 50000;

const uint16_t random_port_up_limit = 59999;

const timeval select_timeout = {1, 0};

#endif //CONFIG_HPP
