#include "candy/base/UUID.hpp"
#include <random>

namespace Candy {
  
  static std::random_device s_RandomDevice;
  static std::mt19937_64 s_Engine(s_RandomDevice());
  static std::uniform_int_distribution<std::uint64_t> s_UniformDistribution;
  
  UUID::UUID() : value(s_UniformDistribution(s_Engine))
  {
  }
  
  UUID::UUID(std::uint64_t uuid) : value(uuid)
  {
  }
  
}