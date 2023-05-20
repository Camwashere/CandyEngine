#pragma once
#include <memory>
#include "../../include/Candy/Math.hpp"


namespace Candy::Noise
{
    class PerlinNoise
    {
    private:
        Math::Random random;
        int period;
        int period2;
        int periodMinusOne;
        std::unique_ptr<int[]> perm;
    
    private:
        void BuildPermutations();
        float Grad(int hash, float x)const;
        float Grad(int hash, float x, float y)const;
        float Grad(int hash, float x, float y, float z)const;
    
    public:
        PerlinNoise();
        PerlinNoise(long seed, int periodValue=256);
    
    
    public:
        int GetPeriod()const{return period;}
        void Set(long seed, int periodValue){period=periodValue;period2=period*2;periodMinusOne=period-1; random.SetSeed(seed); BuildPermutations();}
        void SetPeriod(int periodValue){period=periodValue;period2=period*2;periodMinusOne=period-1; BuildPermutations();}
        void SetSeed(long seed){random.SetSeed(seed); BuildPermutations();}
    
    
    public:
        float Evaluate(float x)const;
        float Evaluate(float x, float y)const;
        float Evaluate(float x, float y, float z)const;
        
        float Evaluate(const Math::Vector2& vec)const;
        float Evaluate(const Math::Vector3& vec)const;
        
    };
}