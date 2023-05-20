#include "Random.hpp"
namespace Candy::Math{
    Random::Random() : seed(0), generator(0), dist(0, 1) {}
    
    Random::Random(long seedValue) : seed(seedValue), generator(seedValue), dist(0, 1) {}
    
    Random::Random(long seedValue, float min, float max) : seed(seedValue), generator(seedValue), dist(min, max) {}
    
    std::default_random_engine Random::GENERATOR = std::default_random_engine(0);
    
    void Random::GlobalSetSeed(long seed) { GENERATOR.seed(seed); }
    
    float Random::Range() {
        std::uniform_real_distribution<float> dist;
        return dist(GENERATOR);
    }
    
    float Random::Range(float max) {
        std::uniform_real_distribution<float> dist(0, max);
        return dist(GENERATOR);
    }
    
    float Random::Range(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(GENERATOR);
    }
    
    int Random::RangeInt() {
        std::uniform_real_distribution<float> dist;
        return dist(GENERATOR);
    }
    
    int Random::RangeInt(int max) {
        std::uniform_real_distribution<double> dist(0, max);
        return dist(GENERATOR);
    }
    
    int Random::RangeInt(int min, int max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(GENERATOR);
    }
    
    void Random::SetSeed(long seedValue) {
        seed = seedValue;
        generator.seed(seed);
    }
    
    void Random::SetMin(float min) { dist = std::uniform_real_distribution(min, dist.max()); }
    
    void Random::SetMax(float max) { dist = std::uniform_real_distribution(dist.min(), max); }
    
    void Random::SetRange(float min, float max) { dist = std::uniform_real_distribution(min, max); }
    
    void Random::Reset() {
        generator.seed(seed);
        dist = std::uniform_real_distribution(dist.min(), dist.max());
    }
    
    long Random::GetSeed() const { return seed; }
    
    float Random::GetMin() const { return dist.min(); }
    
    float Random::GetMax() const { return dist.max(); }
    
    float Random::Next() { return dist(generator); }
    
    std::list<float> Random::Next(int amount) {
        std::list<float> values;
        for (int i = 0; i < amount; i++) {
            values.push_back(dist(generator));
        }
        return values;
    }
    
    int Random::NextInt() { return dist(generator); }
    
    std::list<int> Random::NextInt(int amount) {
        std::list<int> values;
        for (int i = 0; i < amount; i++) {
            values.push_back(dist(generator));
        }
        return values;
    }
    

}