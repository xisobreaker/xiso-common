#include "xiso/common/threadpool.h"
#include <atomic>
#include <gtest/gtest.h>

TEST(TEST_THREADPOOL, TEST_THREADPOOL)
{
    xiso::common::ThreadPool       threadPool(8);
    std::atomic<int>               counter(0);
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 100; i++) {
        auto future = threadPool.enqueue(
            [&counter](int i) {
                counter.fetch_add(i);
            },
            i + 1);
        futures.push_back(std::move(future));
    }

    // 等待所有线程池任务完成
    for (auto &future : futures) {
        future.wait();
    }

    // 1-100的累加值为5050
    EXPECT_EQ(counter.load(), 5050);
}
