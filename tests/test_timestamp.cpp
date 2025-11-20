#include "xiso/common/timestamp.h"
#include <chrono>
#include <gtest/gtest.h>

TEST(TEST_TIMESTAMP, TIMESTAMP)
{
    uint64_t                millis = 1758012060123;
    xiso::common::Timestamp ts((std::chrono::milliseconds(millis)));

    EXPECT_EQ(ts.to_milliseconds(), millis);
    EXPECT_STREQ(ts.to_string().c_str(), "2025-09-16 16:41:00.123000");
    EXPECT_STREQ(ts.to_string(false).c_str(), "2025-09-16 16:41:00");
    EXPECT_STREQ(ts.date_string().c_str(), "20250916");
    EXPECT_STREQ(ts.time_string().c_str(), "164100");
    EXPECT_EQ(ts.to_seconds(), 1758012060);
    EXPECT_EQ(ts.to_minutes(), 29300201);
    EXPECT_EQ(ts.to_hours(), 488336);

    EXPECT_STREQ(ts.fmt_string("%Y-%m-%d %H:%M:%S").c_str(), "2025-09-16 16:41:00");
    EXPECT_STREQ(ts.fmt_string("%Y-%m-%d %H:%M").c_str(), "2025-09-16 16:41");
    EXPECT_STREQ(ts.fmt_string("%Y-%m-%d %H").c_str(), "2025-09-16 16");
    EXPECT_STREQ(ts.fmt_string("%Y-%m-%d").c_str(), "2025-09-16");
    EXPECT_STREQ(ts.fmt_string("%Y%m").c_str(), "202509");
    EXPECT_STREQ(ts.fmt_string("%Y").c_str(), "2025");
}