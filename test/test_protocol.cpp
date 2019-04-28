//
// Created by Ju Yuanmao on 2019-04-25.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "protocol.h"

bool operator==(const protocol_common_head &lhs, const protocol_common_head &rhs) {
    return lhs.stream_id == rhs.stream_id &&
           lhs.command == rhs.command &&
           lhs.length == rhs.length;
}

bool operator==(const protocol_common_options &lhs, const protocol_common_options &rhs) {
    return lhs.flag_i == rhs.flag_i &&
           lhs.flag_c == rhs.flag_c &&
           lhs.flag_o == rhs.flag_o &&
           lhs.id == rhs.id &&
           lhs.ack == rhs.ack &&
           lhs.checksum == rhs.checksum &&
           lhs.offset == rhs.offset;
}

bool operator==(const protocol_head &lhs, const protocol_head &rhs) {
    return lhs.common_head == rhs.common_head &&
           lhs.options == rhs.options;
}

TEST_CASE() {
    protocol_head test_head;
    test_head.common_head.stream_id = 0x01;
    test_head.common_head.command = PUSH;
    test_head.common_head.length = 0xfeff;

    test_head.options.flag_i = 1;
    test_head.options.flag_c = 0;
    test_head.options.flag_o = 0;

    test_head.options.id = 0x10;
    test_head.options.checksum = 0;
    test_head.options.offset = 0;

    uint8_t test_str[8] = {
            0x01, PUSH, 0xfe, 0xff,
            0x80, 0x10, 0x00, 0x00,
    };

    protocol_head out_head;
    uint8_t out_str[8];

    SECTION("proto_to_str") {
        int len = proto_to_str(&test_head, out_str, 8);
        REQUIRE(len == 8);
        REQUIRE(memcmp(test_str, out_str, 8) == 0);
    }

    SECTION("str_to_proto") {
        int len = str_to_proto(test_str, 8, &out_head.common_head, &out_head.options);
        REQUIRE(len == 8);
        REQUIRE(out_head == test_head);
    }

}

