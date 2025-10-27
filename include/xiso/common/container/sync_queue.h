// =====================================================================================
//  Copyright (C) 2025 by shaojx. All rights reserved

//  文 件 名:  sync_queue.h
//  作    者:  shaojx
//  创建时间：  2025-10-27 09:45
//  描    述:
// =====================================================================================

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <type_traits>

namespace xiso {
namespace common {
namespace container {

/**
 * 线程安全的同步队列
 */
template <typename T>
class SyncQueue
{
    typedef std::deque<T> self_type;

public:
    SyncQueue(uint32_t size = 0) : max_size_(size), shutdown_(false){};
    virtual ~SyncQueue(){};

public:
    /**
     * @brief 放入队列
     *
     * @param data 入队列数据
     */
    void push_back(const T &data)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (max_size_ > 0 && max_size_ <= queue_.size()) {
                T &t = queue_.front();
                delete_queue_object(t);
                queue_.pop_front();
            }
            queue_.push_back(data);
        }
        condition_.notify_one();
    }

    /**
     * @brief
     *
     * @param data
     */
    void push_back(T &&data)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (max_size_ > 0 && max_size_ <= queue_.size()) {
                T &t = queue_.front();
                delete_queue_object(t);
                queue_.pop_front();
            }
            queue_.push_back(std::move(data));
        }
        condition_.notify_one();
    }

    /**
     * @brief 出队列, 非阻塞读取
     *
     * @param data
     * @return true
     * @return false
     */
    bool pop_front(T &data)
    {
        if (!queue_.empty() && !shutdown_) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!queue_.empty() && !shutdown_) {
                data = queue_.front();
                queue_.pop_front();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 弹出所有元素
     *
     * @param data_queue
     * @return true
     * @return false
     */
    bool pop_all(std::deque<T> &data_queue)
    {
        if (!queue_.empty() && !shutdown_) {
            std::lock_guard<std::mutex> lock(mutex_);
            data_queue = std::move(queue_);
        }
        return false;
    }

    /**
     * @brief 阻塞等待出队列
     *
     * @param data
     * @return true
     * @return false
     */
    bool wait_pop_front(T &data)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty() && !shutdown_) {
            condition_.wait(lock);

            if (shutdown_)
                return false;
        }

        data = queue_.front();
        queue_.pop_front();
        return true;
    }

    /**
     * @brief 阻塞等待但设置超时
     *
     * @param data
     * @param waitMS
     * @return true
     * @return false
     */
    bool wait_pop_front(T &data, int waitMS)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            condition_.wait_for(lock, std::chrono::milliseconds(waitMS));

            if (queue_.empty())
                return false;
        }

        data = queue_.front();
        queue_.pop_front();
        return true;
    }

    /**
     * @brief 阻塞等待弹出所有数据
     *
     * @param data_queue
     * @return true
     * @return false
     */
    bool wait_pop_all(std::deque<T> &data_queue)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty() && !shutdown_) {
            condition_.wait(lock);

            if (shutdown_)
                return false;
        }

        data_queue = std::move(queue_);
        return true;
    }

    /**
     * @brief 阻塞等待弹出所有数据
     *
     * @param data_queue
     * @return true
     * @return false
     */
    bool wait_pop_all(std::deque<T> &data_queue, int waitMS)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            condition_.wait_for(lock, std::chrono::milliseconds(waitMS));

            if (queue_.empty())
                return false;
        }

        data_queue = std::move(queue_);
        return true;
    }

    /**
     * @brief 所有出队操作退出阻塞状态
     *
     */
    void shutdown()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        while (!queue_.empty()) {
            T &data = queue_.front();
            delete_queue_object(data);
            queue_.pop_front();
        }
        shutdown_ = true;
        condition_.notify_all();
    }

    /**
     * @brief 获取队列大小
     *
     * @return unsigned int
     */
    unsigned int size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return static_cast<unsigned int>(queue_.size());
    }

    /**
     * @brief 队列是否为空
     *
     * @return true
     * @return false
     */
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    void reset() { shutdown_ = false; }

private:
    template <typename E = T>
    typename std::enable_if<std::is_pointer<E>::value>::type delete_queue_object(T &obj)
    {
        delete obj;
    }

    template <typename E = T>
    typename std::enable_if<!std::is_pointer<E>::value>::type delete_queue_object(const E &)
    {
    }

private:
    uint32_t                max_size_;
    std::atomic<bool>       shutdown_;
    std::deque<T>           queue_;
    mutable std::mutex      mutex_;
    std::condition_variable condition_;
};

} // namespace container
} // namespace common
} // namespace xiso