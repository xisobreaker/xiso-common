#include "xiso/common/nettools/inet_address.h"
#include <gtest/gtest.h>

TEST(TEST_NETTOOLS, TEST_INETADDRESS)
{
    xiso::common::nettools::InetAddress addr("127.0.0.1", 8080);
    EXPECT_STREQ(addr.toIpPort().c_str(), "127.0.0.1:8080");
}