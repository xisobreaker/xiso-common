#include "xiso/common/byteutils/byteutils.h"
#include <gtest/gtest.h>

TEST(TEST_BYTEUTILS, BYTES2HEX)
{
    unsigned char buf[]  = {0x01, 0x02, 0x03, 0x04};
    std::string   hexstr = xiso::common::byteutils::bytes2hexstr(buf, sizeof(buf));
    EXPECT_STREQ(hexstr.c_str(), "01 02 03 04");
}

TEST(TEST_BYTEUTILS, HEX2BYTES)
{
    unsigned char buf[] = {0x01, 0x02, 0x03, 0x04};

    std::string   hexstr1 = "01 02 03 04";
    unsigned char tmpbuf1[4];
    xiso::common::byteutils::hexstr2bytes(tmpbuf1, 4, hexstr1);
    EXPECT_TRUE(memcmp(buf, tmpbuf1, 4) == 0);

    std::string   hexstr2 = "01020304";
    unsigned char tmpbuf2[4];
    xiso::common::byteutils::hexstr2bytes(tmpbuf2, 4, hexstr2);
    EXPECT_TRUE(memcmp(buf, tmpbuf2, 4) == 0);
}