/// \file control.cpp
///

#include "control.hpp"

#include <stdio.h>
#include <unistd.h>

/// \brief 处理显示当前路径下文件和路径的请求
/// \details
/// 在ready状态下进入该函数
/// 从系统获取对应用户pwd下的文件列表
/// 发送对应的LS_RES报文
/// 若失败则发送BAD_LS报文
///
/// \param user 待处理请求的用户
/// \return 正常返回0 错误返回-1
int ls(const user_unit * user) {
    return 0;
}

/// \brief 处理变更当前工作路径的请求
/// \details
/// 根据path修改user的pwd
/// 同时检查path的合法性
/// 若失败 则发送BAD_CD报文
///
/// \param user 待处理请求的用户
/// \param path 路径名
/// \return 正常返回0 错误返回-1
int cd(user_unit * user, char * path) {
    return 0;
}

/// \brief 处理创建路径的请求
/// \details
/// 根据path在user的pwd下创建新目录
/// 若失败 则发送BAD_CD报文
///
/// \param user 待处理请求的用户
/// \param arg 新路径名
/// \return 正常返回0 错误返回-1
int mkdir(const user_unit * user, char * arg) {
    return 0;
}

/// \brief 用户退出时 释放一切用户资源
/// \details
/// 关闭管理套接字
/// 关闭数据套接字
/// 关闭所有文件
///
/// \param user 用户
/// \return 正常返回0 错误返回-1
int exit(const user_unit * user) {
    int flg = 0;

    flg |= close(user->sock);

    flg |= close(user->data_sock);

    for (auto & it : user->read_fps) {
        flg |= fclose(it.second);
    }

    for (auto & it : user->read_fps) {
        flg |= fclose(it.second);
    }

    return flg;
}
