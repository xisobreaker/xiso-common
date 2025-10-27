#include "xiso/common/nettools/inet_address.h"
#include <cstring>
#include <arpa/inet.h>
#include <stdexcept>

namespace xiso {
namespace common {
namespace nettools {

InetAddress::InetAddress()
{
}

InetAddress::InetAddress(uint16_t port, bool loopbackOnly)
{
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family      = AF_INET;
    in_addr_t ip          = loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY;
    addr_.sin_addr.s_addr = htonl(ip);
    addr_.sin_port        = htons(port);
}

InetAddress::InetAddress(const char *ip, uint16_t port)
{
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port   = htons(port);
    if (::inet_pton(AF_INET, ip, &addr_.sin_addr) <= 0) {
        throw std::runtime_error("inet_pton error: " + std::string(ip));
    }
}

InetAddress::InetAddress(const struct sockaddr_in &addr) : addr_(addr)
{
}

void InetAddress::setSockAddr(const struct sockaddr_in &addr)
{
    addr_ = addr;
}

const struct sockaddr *InetAddress::getSockAddr() const
{
    return reinterpret_cast<const struct sockaddr *>(&addr_);
}

std::string InetAddress::toIpPort() const
{
    char   buf[64] = {0};
    size_t size    = sizeof(buf);

    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, size);
    size_t   len  = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    snprintf(buf + len, size - len, ":%d", port);
    return buf;
}

} // namespace nettools
} // namespace common
} // namespace xiso