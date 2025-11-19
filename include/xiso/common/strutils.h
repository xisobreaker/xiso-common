#pragma once

#include <string>

namespace xiso {
namespace common {

/**
 * @brief 修剪左右两端字符
 *
 * @param msg 原始字符串
 * @param ch 要修剪的字符
 * @return std::string 修剪后的字符串
 */
std::string str_trim(const std::string &msg, const char ch);

/**
 * @brief 字符串替换
 *
 * @param msg 原始字符串
 * @param src 替换前的字符
 * @param dst 替换后的字符
 * @return std::string
 */
std::string str_replace(const std::string &msg, std::string src, std::string dst);

/**
 * @brief 起始字符串判断
 *
 * @param str 字符串
 * @param start 起始字符串
 * @return true
 * @return false
 */
bool str_startswith(const std::string &str, std::string start);

/**
 * @brief 结束字符串判断
 *
 * @param str 字符串
 * @param end 结束字符串
 * @return true
 * @return false
 */
bool str_endswith(const std::string &str, std::string end);

} // namespace common
} // namespace xiso