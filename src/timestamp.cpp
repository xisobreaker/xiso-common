#include "tyts/timestamp.h"
#include <chrono>
#include <cstring>

using namespace std::chrono;

namespace tyts {

Timestamp::Timestamp() : Timestamp(std::chrono::microseconds::zero())
{
}

Timestamp::Timestamp(std::chrono::system_clock::time_point tp) : tp_(tp)
{
    uint64_t ns = tp_.time_since_epoch().count();
    tv_.tv_sec  = ns / 1000000000;
    tv_.tv_usec = ns % 1000000000 / 1000;
    localtime_r(&tv_.tv_sec, &tm_);
}

Timestamp::~Timestamp()
{
}

Timestamp Timestamp::now()
{
    return Timestamp(std::chrono::system_clock::now());
}

std::string Timestamp::to_string() const
{
    char buffer[32] = {};
#if __cplusplus >= 201103L
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_);
    snprintf(buffer + strlen(buffer), 32 - strlen(buffer), ".%06ld", tv_.tv_usec / 1000);
    return std::string(buffer);
#else
    snprintf(buffer,
             32,
             "%04d-%02d-%02d %02d:%02d:%02d.%06ld",
             tm_.tm_year + 1900,
             tm_.tm_mon + 1,
             tm_.tm_mday,
             tm_.tm_hour,
             tm_.tm_min,
             tm_.tm_sec,
             timeval_.tv_usec);
#endif
    return std::string(buffer);
}

std::string Timestamp::date_string() const
{
    char buffer[32] = {};
    snprintf(buffer, 32, "%04d%02d%02d", tm_.tm_year + 1900, tm_.tm_mon + 1, tm_.tm_mday);
    return std::string(buffer);
}

std::string Timestamp::time_string() const
{
    char buffer[32] = {};
    snprintf(buffer, 32, "%02d%02d%02d", tm_.tm_hour, tm_.tm_min, tm_.tm_sec);
    return std::string(buffer);
}

int64_t Timestamp::to_hours() const
{
    return duration_cast<hours>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::to_minutes() const
{
    return duration_cast<minutes>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::to_seconds() const
{
    return duration_cast<seconds>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::to_milliseconds() const
{
    return duration_cast<milliseconds>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::to_microseconds() const
{
    return duration_cast<microseconds>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::to_nanoseconds() const
{
    return duration_cast<nanoseconds>(tp_.time_since_epoch()).count();
}

} // namespace tyts