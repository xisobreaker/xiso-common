#include "xiso/common/threadpool.h"
#include <atomic>
#include <gtest/gtest.h>

TEST(TEST_THREADPOOL, TEST_THREADPOOL)
{
    xiso::common::ThreadPool       threadPool(4);
    std::atomic<int>               counter(0);
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 100; i++) {
        auto future = threadPool.enqueue(
            [&counter](int i) {
                counter.fetch_add(i);
            },
            i);
        futures.push_back(std::move(future));
    }

    for (auto &future : futures) {
        future.wait();
    }
    EXPECT_EQ(counter.load(), 4950);
}
