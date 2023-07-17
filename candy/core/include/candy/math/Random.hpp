#pragma once
#include <random>
#include <list>
namespace Candy::Math
{
  template<typename T>
  class Random {
  
  private:
    static inline std::default_random_engine GENERATOR = std::default_random_engine(0);
  public:
    static void GlobalSetSeed(uint64_t seed);
    static T Value();
    static T Range(T min, T max);
  
  
  private:
    std::default_random_engine generator;
    std::uniform_real_distribution<T> dist;
    int64_t seed;
  
  public:
    Random();
    explicit Random(int64_t seedValue);
    Random(int64_t seedValue, T min, T max);
  
  
  public:
    void SetSeed(int64_t seedValue);
    void SetMin(T min);
    void SetMax(T max);
    void SetRange(T min, T max);
    void Reset();
    [[nodiscard]] int64_t GetSeed() const;
    [[nodiscard]] T GetMin() const;
    [[nodiscard]] T GetMax() const;
    T Next();
    
    std::list<T> Next(size_t amount);
    
    
  };
  
  typedef Random<float> RandomF;
  typedef Random<double> RandomD;
  typedef Random<int> RandomI;
  
}

#include "Random.inl"