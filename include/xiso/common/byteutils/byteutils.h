#pragma once

#include <string>

namespace xiso {
namespace common {
namespace byteutils {

/**
 * @brief 十六进制数据转 hex
 *
 * @param buf 十六进制数据
 * @param len 数据长度
 * @return std::string hex字符串
 */
std::string bytes2hexstr(const unsigned char *buf, unsigned int len);

/**
 * @brief hex 字符串转 byte 数组
 *
 * @param dst
 * @param src 源数据
 * @param srcLen 源数据长度
 * @return int 实际数据长度
 */
int hexstr2bytes(unsigned char *dst, unsigned int maxlen, const std::string &hexstr);

} // namespace byteutils
} // namespace common
} // namespace xiso
