#include "tyts/scheduled.h"

namespace tyts {

Scheduled::Scheduled() : stop_(false)
{
    worker_.reset(new std::thread([this]() {
        while (true) {
            std::unique_lock<std::mutex> lock(task_lock_);
            condition_.wait(lock, [this]() {
                return stop_ || !task_list_.empty();
            });

            if (stop_)
                return;

            auto task = *task_list_.begin();
            if (SystemClock::now() >= task.nextTime) {
                task_list_.erase(task_list_.begin());
                lock.unlock();
                task.callback();

                // 添加下次任务
                if (task.period.count() > 0) {
                    lock.lock();
                    task.nextTime = task.nextTime + task.period;
                    task_list_.insert(std::move(task));
                }
            } else {
                condition_.wait_until(lock, task.nextTime);
            }
        }
    }));
}

Scheduled::~Scheduled()
{
    stop_ = false;
    if (worker_) {
        if (worker_->joinable())
            worker_->join();
        worker_.reset();
    }
}

void Scheduled::addTask(ScheduledFunc &&fn, const std::chrono::time_point<SystemClock> &tp)
{
    addTask(std::move(fn), tp, std::chrono::microseconds::zero());
}

void Scheduled::addTask(ScheduledFunc                             &&fn,
                        const std::chrono::time_point<SystemClock> &tp,
                        const std::chrono::microseconds            &period)
{
    // 添加任务到有序队列
    CrontabTask task;
    task.callback = std::move(fn);
    task.nextTime = tp;
    task.period   = period;

    {
        std::lock_guard<std::mutex> guard(task_lock_);
        task_list_.insert(std::move(task));
    }
    condition_.notify_one();
}

} // namespace tyts