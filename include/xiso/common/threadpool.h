#pragma once

#include <functional>
#include <future>
#include <vector>
#include <queue>

namespace xiso {
namespace common {

class ThreadPool
{
public:
    ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_lock_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks_.emplace([task]() {
                (*task)();
            });
        }
        condition_.notify_one();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(queue_lock_);
        return tasks_.empty();
    }

private:
    std::vector<std::thread>          workers_;
    std::queue<std::function<void()>> tasks_;
    mutable std::mutex                queue_lock_;
    std::condition_variable           condition_;
    bool                              stop_;
};

} // namespace common
} // namespace xiso