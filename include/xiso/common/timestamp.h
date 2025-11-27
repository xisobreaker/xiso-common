#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace xiso {
namespace common {

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(std::chrono::system_clock::time_point tp);
    explicit Timestamp(std::chrono::system_clock::duration ts);
    ~Timestamp();

public:
    static Timestamp now();

    /**
     * @brief 使用指定格式解析字符串为时间戳
     *
     * @param str 时间字符串
     * @param format 格式化字符串(默认"%Y-%m-%d %H:%M:%S")
     * @return Timestamp
     */
    static Timestamp from_string(const std::string &str, const std::string &format = "%Y-%m-%d %H:%M:%S");

public:
    /**
     * @brief 格式化时间戳为字符串
     *
     * @param format 格式化字符串(默认"%Y-%m-%d %H:%M:%S")
     * @return std::string
     */
    std::string fmt_string(const std::string &format = "%Y-%m-%d %H:%M:%S") const;

    /**
     * @brief 获取时间戳的字符串表示(格式"%Y-%m-%d %H:%M:%S.ffffff")
     *
     * @param containsMicros 是否包含微秒(默认true)
     * @return std::string
     */
    std::string to_string(bool containsMicros = true) const;

    /**
     * @brief 获取时间戳的日期部分(格式"%Y%m%d")
     *
     * @return std::string
     */
    std::string date_string() const;

    /**
     * @brief 获取时间戳的时间部分(格式"%H%M%S")
     *
     * @return std::string
     */
    std::string time_string() const;

    /**
     * @brief 时间戳加法
     *
     * @param ts 时间间隔
     * @return Timestamp
     */
    void add(std::chrono::system_clock::duration ts);

    /**
     * @brief 时间戳减法
     *
     * @param ts 时间间隔
     * @return Timestamp
     */
    void sub(std::chrono::system_clock::duration ts);

    int64_t to_hours() const;
    int64_t to_minutes() const;
    int64_t to_seconds() const;
    int64_t to_milliseconds() const;
    int64_t to_microseconds() const;
    int64_t to_nanoseconds() const;

private:
    std::chrono::system_clock::time_point tp_;
    struct timeval                        tv_;
    struct tm                             tm_;
};

} // namespace common
} // namespace xiso