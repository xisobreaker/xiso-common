#pragma once

#include <cstdint>
#include <random>

namespace xiso {
namespace common {

class Random
{
public:
    Random();
    explicit Random(uint64_t seed);
    ~Random();

public:
    /**
     * @brief 获取[min, max]之间的随机数
     *
     * @param min 最小值
     * @param max 最大值
     * @return uint32_t
     */
    uint32_t random(uint32_t min, uint32_t max);

private:
    std::default_random_engine engine_;
};

} // namespace common
} // namespace xiso