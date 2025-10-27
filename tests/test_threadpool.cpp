#include "xiso/common/threadpool.h"
#include <atomic>
#include <gtest/gtest.h>
#include <thread>

TEST(TEST_THREADPOOL, TEST_THREADPOOL)
{
    xiso::common::ThreadPool threadPool(4);
    std::atomic<int>         counter(0);
    for (int i = 0; i < 100; i++) {
        threadPool.enqueue(
            [&counter](int i) {
                counter.fetch_add(i);
            },
            i);
    }

    while (!threadPool.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    EXPECT_EQ(counter.load(), 4950);
}