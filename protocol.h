/// \file protocol.h
///

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef uint8_t stream_id_t;
typedef uint8_t command_t;
typedef uint16_t length_t;

struct protocol_common_head {
    stream_id_t stream_id;
    command_t command;
    length_t length;
};

struct protocol_common_options {
    bool flag_i;
    bool flag_c;
    bool flag_o;
    union {
        uint16_t id;
        uint16_t ack;
    };
    uint16_t checksum;
    uint64_t offset;
};

struct protocol_head {
    struct protocol_common_head common_head;
    struct protocol_common_options options;
};


/// \brief 将协议报文头部转换为可直接发送的字节流
/// \param head 已填写好的报文头部
/// \param buffer 储存转换结果的缓冲区
/// \param buffer_size 缓冲区大小
/// \return 正常时返回转换的字节数 错误返回-1
int proto_to_str(const struct protocol_head * head, void * buffer, size_t buffer_size);

/// \brief 将字节流解析为common_head和options
/// \param buffer 储存待解析的字节流的缓冲区
/// \param buffer_size 缓冲区大小
/// \param common_head 储存解析后的common_head 若字节流不含有该字段则填NULL
/// \param options 储存解析后的options 若字节流不含有该字段或不需要解析则填NULL
/// \return  正常时返回转换的字节数 错误返回-1
int str_to_proto(const void * buffer, size_t buffer_size, struct protocol_common_head * common_head, struct protocol_common_options * options);


/// \brief 用于用户登陆
/// \details 在数据部分应填写用户名
#define LOGIN       0x01u

/// \brief 发送质询结果
/// \details 填写在数据部分
#define CHAP_ANS    0x02u

/// \brief 用户退出
#define EXIT        0x03u

/// \brief 请求下载
/// \details
/// 对于中断后继续传输
/// 应将标志位O置为1并在file offset字段中填入已下载的字节数
/// 在数据部分填入对应该文件的stream id
/// 在stream id后跟需要下载的文件名
#define GET         0x04u

/// \brief 请求上传
/// \details 在数据部分填入上传文件名
#define PUT         0x05u

/// \brief 请求当前目录下的文件列表
#define LS          0x06u

/// \brief 切换当前目录
/// \details 在数据部分填入目录名称
#define CD          0x07u

/// \brief 在当前工作目录下新建目录
/// \details 在数据部分填入新目录的名称
#define MKDIR       0x08u

/// \brief 发送质询数据
/// \details 在数据部分填写质询数据
#define CHAP        0x11u

/// \brief 通知用户认证通过
/// \details 在数据部分以大端序的uint16_t填入数据连接的端口号
#define PASSED      0x12u

/// \brief 回复下载请求
#define GET_OK      0x14u

/// \brief 回复上传请求
/// \details
/// 对于中断后继续传输
/// 应将标志位O置为1
/// 并在file offset字段中填入已下载的字节数
/// 在数据部分填入对应该文件的stream id
#define PUT_OK      0x15u

/// \brief 回应ls的结果
/// \details 在数据部分填入ls的结果
#define LS_RES      0x16u

/// \brief 拒绝下载请求
/// \details 可在数据部分填入原因
#define	BAD_GET     0x24u

/// \brief 拒绝下载请求
/// \details 可在数据部分填入原因
#define BAS_PUT	    0x25u

/// \brief 拒绝请求当前目录下的文件列表
/// \details 可在数据部分填入原因
#define	BAD_LS      0x26u

/// \brief 拒绝下切换目录的请求
/// \details 可在数据部分填入原因
#define BAD_CD      0x27u

/// \brief 拒绝创建目录
/// \details 可在数据部分填入原因
#define BAD_MKDIR   0x28u

/// \brief 推送数据
#define	PUSH        0x31u
/// \brief 对于数据回应
#define	DATA_ACK    0x32u
/// \brief 数据传输结束
#define	DATA_END    0x33u

/// \brief 修改密码
/// \details 在数据部分按照<用户名><空格><新密码>的方式填写
#define CHPASSWD    0x41u

/// \brief 命令无法解析
#define  BAD_CMD    0xf1u

/// \brief 校验和错误
#define CHECKSUM_ERROR 0xf2u

#if defined(__cplusplus)
}
#endif

#endif //PROTOCOL_H
