#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <set>
#include <thread>

namespace xiso {
namespace common {

class Scheduled
{
    using ScheduledFunc = std::function<void()>;
    using SystemClock   = std::chrono::system_clock;

    struct CrontabTask {
        std::function<void()>                callback;
        std::chrono::time_point<SystemClock> nextTime;
        std::chrono::microseconds            period;

        bool operator<(const CrontabTask &task) const { return this->nextTime < task.nextTime; }
    };

public:
    Scheduled();
    ~Scheduled();

public:
    /**
     * @brief 添加一次性任务
     *
     * @param fn 任务回调
     * @param tp 开始时间
     */
    void addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp);

    /**
     * @brief 添加定时周期任务
     *
     * @param fn 任务回调
     * @param tp 开始时间
     * @param period 任务周期
     */
    void addTask(ScheduledFunc                             &&fn,
                 const std::chrono::time_point<SystemClock> &tp,
                 const std::chrono::microseconds            &period);

    /**
     * @brief 添加周期任务
     *
     * @tparam Rep
     * @tparam Period
     * @param fn 任务回调
     * @param period 任务周期
     * @param start_now 立即执行任务
     */
    template <typename Rep, typename Period>
    void addTask(ScheduledFunc &&fn, const std::chrono::duration<Rep, Period> &period, bool start_now = false)
    {
        if (start_now) {
            addTask(std::move(fn), SystemClock::now(), period);
        } else {
            addTask(std::move(fn), SystemClock::now() + period, period);
        }
    }

private:
    bool                         stop_;
    std::mutex                   task_lock_;
    std::condition_variable      condition_;
    std::unique_ptr<std::thread> worker_;
    std::multiset<CrontabTask>   task_list_;
};

} // namespace common
} // namespace xiso