#include "xiso/common/random.h"
#include <gtest/gtest.h>

TEST(TEST_RANDOM, TEST_RANDOM)
{
    xiso::common::Random random;

    for (int i = 0; i < 100; i++) {
        int value = random.random(0, 100);
        EXPECT_GE(value, 0);
        EXPECT_LE(value, 100);
    }
}