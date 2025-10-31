#pragma once

namespace xiso {
namespace common {
namespace nettools {

/**
 * @brief 主机序转网络序(8字节)
 *
 * @param val 主机序
 * @return unsigned long long 网络序
 */
unsigned long long htonll(unsigned long long val);

/**
 * @brief 网络序转主机序(8字节)
 *
 * @param val 网络序
 * @return unsigned long long 主机序
 */
unsigned long long ntohll(unsigned long long val);

} // namespace nettools
} // namespace common
} // namespace xiso