#include "xiso/common/byteutils/byteutils.h"
#include <cstring>

namespace xiso {
namespace common {
namespace byteutils {

std::string bytes2hexstr(const unsigned char *buf, unsigned int len)
{
    static const char hex_table[] = "0123456789ABCDEF";

    if (buf == nullptr)
        return "";

    std::string message;
    message.reserve(len * 3);
    for (int i = 0; i < len; i++) {
        unsigned char byte = buf[i];
        message.push_back(hex_table[(byte >> 4) & 0x0F]);
        message.push_back(hex_table[byte & 0x0F]);
        if (i + 1 != len)
            message.push_back(' ');
    }
    return message;
}

int hexstr2bytes(unsigned char *dst, unsigned int maxlen, const std::string &hexstr)
{
    const static auto hex_value = [](char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        }
        return 0;
    };

    memset(dst, 0, maxlen);

    int length = 0;
    int chSize = 0;
    for (int i = 0; i < hexstr.length(); i++) {
        if (hexstr.at(i) == ' ')
            continue;

        // 防止越界
        if (length >= maxlen)
            break;

        if ((chSize++) % 2 == 0) {
            dst[length] += (hex_value(hexstr.at(i)) << 4);
        } else {
            dst[length++] += hex_value(hexstr.at(i));
        }
    }
    return length;
}

} // namespace byteutils
} // namespace common
} // namespace xiso