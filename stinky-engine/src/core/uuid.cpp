#include "stinkypch.h"
#include "uuid.h"

#include <random>

namespace stinky {

    static std::random_device s_RandomDevice;
    static std::mt19937_64 eng(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

    uuid::uuid()
            : m_UUID(s_UniformDistribution(eng))
    {
    }

    uuid::uuid(uint64_t uuid)
            : m_UUID(uuid)
    {
    }

    uuid::uuid(const uuid& other) = default;

}