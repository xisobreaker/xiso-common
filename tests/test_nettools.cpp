#include "xiso/common/nettools/inet_address.h"
#include <gtest/gtest.h>

TEST(TEST_NETTOOLS, TEST_INETADDRESS)
{
    xiso::common::nettools::InetAddress addr1("127.0.0.1", 8080);
    EXPECT_STREQ(addr1.toIpPort().c_str(), "127.0.0.1:8080");

    xiso::common::nettools::InetAddress addr2(8080, true);
    EXPECT_STREQ(addr2.toIpPort().c_str(), "127.0.0.1:8080");

    xiso::common::nettools::InetAddress addr3(8080);
    EXPECT_STREQ(addr3.toIpPort().c_str(), "0.0.0.0:8080");
}