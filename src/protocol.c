/// \file protocol.c
///

#include "protocol.h"

#include <string.h>
#include <arpa/inet.h>
#include <endian.h>


/// \brief 将协议报文头部转换为可直接发送的字节流
/// 依据协议报文格式
/// 将结构体中的信息按顺序存入到字节流中
/// 并完成字节序的转换
///
/// \param head 已填写好的报文头部
/// \param buffer 储存转换结果的缓冲区
/// \param buffer_size 缓冲区大小
/// \return  正常时返回转换的字节数 错误返回-1
int proto_to_str(const struct protocol_head * head, void * buffer, size_t buffer_size) {
    uint8_t * p = buffer;
    if (head == NULL || p == NULL || buffer_size < 8
    || (head->options.flag_i && head->options.id > 0x1fffu)
    || (head->options.flag_o && buffer_size < 16))
        return -1;

    *p = head->common_head.stream_id;
    p += sizeof(stream_id_t);

    *p = head->common_head.command;
    p += sizeof(command_t);

    *(length_t *)p = htons(head->common_head.length);
    p += sizeof(length_t);

    memset(p, 0, 4);
    *p |= head->options.flag_i ? 0x80u : 0;
    *p |= head->options.flag_c ? 0x40u : 0;
    *p |= head->options.flag_o ? 0x20u : 0;
    if (head->options.flag_i)
        *(uint16_t *)p |=  htons(head->options.id);
    p += sizeof(uint16_t);

    if(head->options.flag_c)
        *(uint16_t *)p =  htons(head->options.checksum);
    p += sizeof(uint16_t);

    if(head->options.flag_o) {
        *(uint64_t *)p = htobe64(head->options.offset);
        return 16;
    } else {
        return 8;
    }
}

/// \brief 将字节流解析为common_head和options
/// \details
/// 依据协议报文格式
/// 将字节流中的信息存入到对应的结构体中
/// 并完成字节序的转换
///
/// \param buffer 储存待解析的字节流的缓冲区
/// \param buffer_size 缓冲区大小
/// \param common_head 储存解析后的common_head 若字节流不含有该字段则填NULL
/// \param options 储存解析后的options 若字节流不含有该字段或不需要解析则填NULL
/// \return  正常时返回转换的字节数 错误返回-1
int str_to_proto(const void * buffer, size_t buffer_size, struct protocol_common_head * common_head, struct protocol_common_options * options) {
    const uint8_t * p = buffer;
    int original_size = buffer_size;

    if (common_head) {
        if (buffer_size < 4)
            return -1;

        common_head -> stream_id = *p;
        p += sizeof(stream_id_t);

        common_head->command = *p;
        p += sizeof(command_t);

        common_head -> length = ntohs(*(const length_t *)p);
        p += sizeof(length_t);

        buffer_size -= 4;
    }

    if (options) {
        if (buffer_size < 4)
            return -1;
        options->flag_i = (*p) & 0x80u ? true : false;
        options->flag_c = (*p) & 0x40u ? true : false;
        options->flag_o = (*p) & 0x20u ? true : false;
        options->id = ntohs(*(const uint16_t *)p) & 0x1fffu;
        p += sizeof(uint16_t);

        options->checksum = ntohs(*(const uint16_t *)p);
        p += sizeof(uint16_t);

        buffer_size -= 4;

        if (options->flag_o) {
            if (buffer_size < 8)
                return -1;
            options->offset = be64toh(*(const uint64_t *)p);
            buffer_size -= 8;
        } else {
            options->offset = 0;
        }
    }

    return original_size - buffer_size;
}
