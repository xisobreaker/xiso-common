#pragma once

#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

namespace xiso {
namespace common {
namespace nettools {

class InetAddress
{
public:
    InetAddress();
    explicit InetAddress(uint16_t port, bool loopbackOnly = false);
    explicit InetAddress(const char *ip, uint16_t port);
    explicit InetAddress(const struct sockaddr_in &addr);

public:
    /**
     * @brief 设置sockaddr_in结构体
     *
     * @param addr
     */
    void setSockAddr(const struct sockaddr_in &addr);

    /**
     * @brief 获取sockaddr_in结构体指针
     *
     * @return const struct sockaddr*
     */
    const struct sockaddr *getSockAddr() const;

    /**
     * @brief 获取sockaddr_in结构体长度
     *
     * @return const int
     */
    const int getSockAddrLen() const;

    /**
     * @brief 转换为ip:port格式的字符串
     *
     * @return std::string
     */
    std::string toIpPort() const;

private:
    struct sockaddr_in addr_;
};

} // namespace nettools
} // namespace common
} // namespace xiso
