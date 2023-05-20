#pragma once

#include <random>
#include <list>

namespace Candy::Math{
        class Random {
        private:
            static std::default_random_engine GENERATOR;
        public:
            static void GlobalSetSeed(long seed);
            
            static float Range();
            
            static float Range(float max);
            
            static float Range(float min, float max);
            
            static int RangeInt();
            
            static int RangeInt(int max);
            
            static int RangeInt(int min, int max);
        
        private:
            std::default_random_engine generator;
            std::uniform_real_distribution<float> dist;
            long seed;
        
        public:
            Random();
            
            explicit Random(long seedValue);
            
            Random(long seedValue, float min, float max);
        
        
        public:
            void SetSeed(long seedValue);
            
            void SetMin(float min);
            
            void SetMax(float max);
            
            void SetRange(float min, float max);
            
            void Reset();
            
            long GetSeed() const;
            
            float GetMin() const;
            
            float GetMax() const;
            
            float Next();
            
            std::list<float> Next(int amount);
            
            int NextInt();
            
            std::list<int> NextInt(int amount);
            
        };
}

