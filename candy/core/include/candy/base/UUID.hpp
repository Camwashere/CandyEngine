#pragma once
#include <cstdint>
namespace Candy
{
  class UUID
  {
  private:
    std::uint64_t value;
  
  public:
    UUID();
    UUID(std::uint64_t uuid);
    UUID(const UUID&)=default;
    
    operator std::uint64_t() const{return value;}
  };
}

namespace std {
  template <typename T> struct hash;
  
  template<>
  struct hash<Candy::UUID>
  {
    std::size_t operator()(const Candy::UUID& uuid) const
    {
      return (std::uint64_t)uuid;
    }
  };
  
}