#pragma once
#include "Limit.hpp"
namespace Candy::Math
{
  template<typename T> void Random<T>::GlobalSetSeed(uint64_t seed)
  {
    GENERATOR.seed(seed);
  }
  template<typename T> T Random<T>::Value()
  {
    std::uniform_real_distribution<T> dist;
    return dist(GENERATOR);
  }
  
  template<typename T> T Random<T>::Range(T min, T max)
  {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(GENERATOR);
  }
  template<typename T>
  Random<T>::Random() : seed(0), generator(0), dist(0, 1) {} //NOLINT
  
  template<typename T>
  Random<T>::Random(int64_t seedValue) : seed(seedValue), generator(seedValue), dist(0, 1) {}
  
  template<typename T>
  Random<T>::Random(int64_t seedValue, T min, T max) : seed(seedValue), generator(seedValue), dist(min, max) {}

  
  template<typename T>
  void Random<T>::SetSeed(int64_t seedValue)
  {
    seed = seedValue;
    generator.seed(seed);
  }
  template<typename T>
  void Random<T>::SetMin(T min)
  {
    dist = std::uniform_real_distribution(min, dist.max());
  }
  template<typename T>
  void Random<T>::SetMax(T max)
  {
    dist = std::uniform_real_distribution(dist.min(), max);
  }
  template<typename T>
  void Random<T>::SetRange(T min, T max)
  {
    dist = std::uniform_real_distribution(min, max);
  }
  template<typename T>
  void Random<T>::Reset()
  {
    generator.seed(seed);
    dist = std::uniform_real_distribution(dist.min(), dist.max());
  }
  template<typename T>
  int64_t Random<T>::GetSeed() const
  {
    return seed;
  }
  template<typename T>
  T Random<T>::GetMin() const {return dist.min();}
  template<typename T>
  T Random<T>::GetMax() const {return dist.max();}
  template<typename T>
  T Random<T>::Next() {return dist(generator);}
  
  template<typename T>
  std::list<T> Random<T>::Next(size_t amount)
  {
    std::list<float> values(amount);
    for (int i = 0; i < amount; i++) {
      values.push_back(dist(generator));
    }
    return values;
  }
}
