#include "xiso/common/random.h"
#include <ctime>

namespace xiso {
namespace common {

Random::Random() : Random(std::time(nullptr))
{
}

Random::Random(uint64_t seed)
{
    engine_.seed(seed);
}

Random::~Random()
{
}

uint32_t Random::random(uint32_t min, uint32_t max)
{
    return (engine_() % (max - min + 1) + min);
}

} // namespace common
} // namespace xiso