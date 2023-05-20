#pragma once

#include <algorithm>
#include "MathOps.hpp"
#include <string>
#include <ostream>
namespace Candy::Math{
    template <typename T>
    class Range
    {
    
    private:
        T min;
        T max;
    
    public:
        Range() : min(0), max(1){}
        Range(T maxValue) : min(0), max(maxValue){}
        Range(T minValue, T maxValue) : min(minValue), max(maxValue){}
        Range(const Range& other) : min(other.min), max(other.max){}
    
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
        bool operator == (const Range& other)const{return min==other.min&&max==other.max;}
        bool operator != (const Range& other)const{return !(min==other.min&&max==other.max);}
        std::ostream& operator << (std::ostream& ostream)const{
            ostream << "(" << min << "-" << max << ")";
            return ostream;
        }
        
        friend std::ostream& operator << (const Range& range, std::ostream& ostream){
            ostream << "(" << range.min << "-" << range.max << ")";
            return ostream;
        }
    
    
    public:
        T Difference()const{return max-min;}
        T GetMin()const{return min;}
        T GetMax()const{return max;}
        void* GetMinAsVoid(){return static_cast<void*>(&min);}
        void* GetMaxAsVoid(){return static_cast<void*>(&max);}
        void Set(T minValue, T maxValue){min=minValue; max=maxValue;}
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
