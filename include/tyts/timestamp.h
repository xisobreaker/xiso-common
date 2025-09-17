#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace tyts {

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(std::chrono::system_clock::time_point tp);

    template <typename Rep, typename Period>
    Timestamp(std::chrono::duration<Rep, Period> ts);
    ~Timestamp();

public:
    static Timestamp now();

public:
    std::string to_string() const;
    std::string date_string() const;
    std::string time_string() const;

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

template <typename Rep, typename Period>
Timestamp::Timestamp(std::chrono::duration<Rep, Period> ts) : tp_(ts)
{
    uint64_t ns = tp_.time_since_epoch().count();
    tv_.tv_sec  = ns / 1000000000;
    tv_.tv_usec = ns % 1000000000 / 1000;
    localtime_r(&tv_.tv_sec, &tm_);
};

} // namespace tyts