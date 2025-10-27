#include "xiso/common/timestamp.h"
#include <chrono>
#include <gtest/gtest.h>

TEST(TEST_TIMESTAMP, TEST_TIMESTAMP)
{
    uint64_t                millis = 1758012060000;
    xiso::common::Timestamp ts((std::chrono::milliseconds(millis)));

    EXPECT_EQ(ts.to_milliseconds(), millis);
    EXPECT_STREQ(ts.to_string().c_str(), "2025-09-16 16:41:00.000000");
}