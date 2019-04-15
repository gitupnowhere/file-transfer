/// \file protocol.h
///

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint8_t stream_id_t;

struct protocol_head_t {
    stream_id_t stream_id;
    uint8_t command;
    uint16_t length;
    bool flag_i;
    bool flag_c;
    bool flag_o;
    uint16_t id_or_ack;
    uint16_t checksum;
    uint64_t offset;
};

void proto_to_str(const struct protocol_head_t * protocolHead, void * buffer, size_t buffer_size);

void str_to_proto(const void * buffer, size_t buffer_size, struct protocol_head_t * protocolHead);


/// \brief 用于用户登陆
/// \details 在数据部分应填写用户名
#define LOGIN       0x01

/// \brief 发送质询结果
/// \details 填写在数据部分
#define CHAP_ANS    0x02

/// \brief 用户退出
#define EXIT        0x03

/// \brief 请求下载
/// \details
/// 对于中断后继续传输
/// 应将标志位O置为1并在file offset字段中填入已下载的字节数
/// 在数据部分填入对应该文件的stream id
/// 在stream id后跟需要下载的文件名
#define GET         0x04

/// \brief 请求上传
/// \details 在数据部分填入上传文件名
#define PUT         0x05

/// \brief 请求当前目录下的文件列表
#define LS          0x06

/// \brief 切换当前目录
/// \details 在数据部分填入目录名称
#define CD          0x07

/// \brief 在当前工作目录下新建目录
/// \details 在数据部分填入新目录的名称
#define MKDIR       0x08

/// \brief 发送质询数据
/// \details 在数据部分填写质询数据
#define CHAP        0x11

/// \brief 通知用户认证通过
/// \details 在数据部分以大端序的uint16_t填入数据连接的端口号
#define PASSED      0x12

/// \brief 回复下载请求
#define GET_OK      0x14

/// \brief 回复上传请求
/// \details
/// 对于中断后继续传输
/// 应将标志位O置为1
/// 并在file offset字段中填入已下载的字节数
/// 在数据部分填入对应该文件的stream id
#define PUT_OK      0x15

/// \brief 回应ls的结果
/// \details 在数据部分填入ls的结果
#define LS_RES      0x16

/// \brief 拒绝下载请求
/// \details 可在数据部分填入原因
#define	BAD_GET     0x24

/// \brief 拒绝下载请求
/// \details 可在数据部分填入原因
#define BAS_PUT	    0x25

/// \brief 拒绝请求当前目录下的文件列表
/// \details 可在数据部分填入原因
#define	BAD_LS      0x26

/// \brief 拒绝下切换目录的请求
/// \details 可在数据部分填入原因
#define BAD_CD      0x27

/// \brief 拒绝创建目录
/// \details 可在数据部分填入原因
#define BAD_MKDIR   0x28

/// \brief 推送数据
#define	PUSH        0x31
/// \brief 对于数据回应
#define	DATA_ACK    0x32

/// \brief 修改密码
/// \details 在数据部分按照<用户名><空格><新密码>的方式填写
#define CHPASSWD    0x41

/// \brief 命令无法解析
#define  BAD_CMD    0xf1

/// \brief 校验和错误
#define CHECKSUM_ERROR 0xf2


#endif //PROTOCOL_H
