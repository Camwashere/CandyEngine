#include "UUID.hpp"
#include <random>
#include <unordered_map>
namespace Candy {
    
    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64> s_UniformDistribution;
    
    UUID::UUID() : value(s_UniformDistribution(s_Engine))
    {
    }
    
    UUID::UUID(uint64 uuid) : value(uuid)
    {
    }
    
}