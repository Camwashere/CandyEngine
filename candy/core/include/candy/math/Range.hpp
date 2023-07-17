#pragma once
#include "MathOps.hpp"
#include "vector/Vector2Base.hpp"
namespace Candy::Math{
  template <typename T>
  class Range : public VectorBase<T, 2>
  {
  public:
    using VectorBase<T, 2>::min;
    using VectorBase<T, 2>::max;
  
  public:
    Range() : VectorBase<T, 2>(0, 1){}
    explicit Range(T maxValue) : VectorBase<T, 2>(0, maxValue){}
    Range(T minValue, T maxValue) : VectorBase<T, 2>(minValue, maxValue){}
    Range(const Range& other) : VectorBase<T, 2>(other){}
  
  public:
    static T Wrap(T value, T min, T max)
    {
      T offset;
      if (value < min)
      {
        int iterations = Math::FloorToInt(value/max);
        offset = Abs(max*iterations-value);
        return offset;
      }
      else if (value >= max)
      {
        int iterations = Math::FloorToInt(value/max);
        offset = value-max*iterations;
        return offset;
      }
      else
      {
        return value;
      }
    }
    static Range<T> Max(){return Range<T>(Limit<T>::Min(), Limit<T>::Max());}
    static Range<T> InvertedMax(){return Range<T>(Limit<T>::Max(), Limit<T>::Min());}
  
  public:
    using VectorBase<T, 2>::operator ==;
    using VectorBase<T, 2>::operator !=;
  
  
  
  
  public:
    T GetMin()const{return min;}
    T GetMax()const{return max;}
    void* GetMinAsVoid(){return static_cast<void*>(&min);}
    void* GetMaxAsVoid(){return static_cast<void*>(&max);}
    void Set(const Range<T>& other){min=other.min; max=other.max;}
    void SetMin(T minValue){min=minValue;}
    void SetMax(T maxValue){max=maxValue;}
    void SetMaxMin(T value){min = Math::Min(min, value); max = Math::Max(max, value);}
    void ExpandMin(T minAmount){min-=minAmount;}
    void ExpandMax(T maxAmount){max+=maxAmount;}
    void Expand(T expandAmount){min-=expandAmount; max+=expandAmount;}
    void Expand(T minAmount, T maxAmount){min-=minAmount; max+=maxAmount;}
    void ExpandClamped(T expandAmount, T minBound, T maxBound){min = Math::Clamp(min-expandAmount, minBound, maxBound); max = Math::Clamp(max+=expandAmount, minBound, maxBound);}
    void ExpandClamped(T minAmount, T maxAmount, T minBound, T maxBound){min = Math::Clamp(min-minAmount, minBound, maxBound); max = Math::Clamp(max+=maxAmount, minBound, maxBound);}
  
  
  public:
    T Clamp(T value)const{return Math::Clamp(value, min, max);}
    bool InRangeInclusive(float value){return value >= min && value <= max;}
    bool InRangeExclusive(float value){return value > min && value < max;}
    bool InRangeMinInclusive(float value){return value >= min && value < max;}
    bool InRangeMaxInclusive(float value){return value > min && value <= max;}
  
  public:
    std::string ToString()const{return "(" + min + "-" + max + ")";}
    
    
    
    
    
  };
  
}

template<typename T>
std::ostream& operator << (const Candy::Math::Range<T>& range, std::ostream& ostream){
  ostream << "(" << range.min << "-" << range.max << ")";
  return ostream;
}