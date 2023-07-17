#include <candy/noise/PerlinNoise.hpp>

namespace Candy::Noise
{
    PerlinNoise::PerlinNoise() : random(), period(256), period2(512), periodMinusOne(255){
        random.SetSeed(0);
        BuildPermutations();
    }
    
    PerlinNoise::PerlinNoise(long seed, int periodValue) : random(), period(periodValue), period2(periodValue*2), periodMinusOne(periodValue-1){
        random.SetSeed(seed);
        BuildPermutations();
    }
    
    
    
    float PerlinNoise::Evaluate(float x) const {
        int X = Math::FloorToInt(x) & periodMinusOne;
        x -= Math::Floor(x);
        float u = Math::Interpolate::Fade(x);
        float value = Math::Interpolate::Lerp(u, Grad(perm[X], x), Grad(perm[X + 1], x - 1));
        return (value+1)/2.0f;
    }
    
    float PerlinNoise::Evaluate(float x, float y) const {
        // Find unit plane that contains the point
        int X = Math::FloorToInt(x) & periodMinusOne;
        int Y = Math::FloorToInt(y) & periodMinusOne;
        
        x-= Math::Floor(x);
        y-= Math::Floor(y);
        
        // Compute Math::Interpolate::fade curves
        float u = Math::Interpolate::Fade(x);
        float v = Math::Interpolate::Fade(y);
        
        int A = (perm[X]+Y) & periodMinusOne;
        int B = (perm[X+1] + Y) & periodMinusOne;
        
        float value = Math::Interpolate::Lerp(v, Math::Interpolate::Lerp(u, Grad(perm[A], x, y), Grad(perm[B], x - 1, y)),
                                              Math::Interpolate::Lerp(u, Grad(perm[A + 1], x, y - 1), Grad(perm[B + 1], x - 1, y - 1)));
        return (value+1.0f)*0.5f;
    }
    
    float PerlinNoise::Evaluate(float x, float y, float z) const {
        // Find unit cube that contains the point
        int X = Math::FloorToInt(x) & periodMinusOne;
        int Y = Math::FloorToInt(y) & periodMinusOne;
        int Z = Math::FloorToInt(z) & periodMinusOne;
        // Find relative X, Y, Z of point in cube
        x-= Math::Floor(x);
        y-= Math::Floor(y);
        z-= Math::Floor(z);
        // Compute Math::Interpolate::fade curves for each of X, Y, Z
        float u = Math::Interpolate::Fade(x);
        float v = Math::Interpolate::Fade(y);
        float w = Math::Interpolate::Fade(z);
        // Hash coordinates of the 8 cube corners
        int A  = (perm[X ] + Y) & periodMinusOne;
        int B  = (perm[X+1] + Y) & periodMinusOne;
        int AA = (perm[A] + Z) & periodMinusOne;
        int BA = (perm[B] + Z) & periodMinusOne;
        int AB = (perm[A+1] + Z) & periodMinusOne;
        int BB = (perm[B+1] + Z) & periodMinusOne;
        // Add blended results from 8 corners of the cube
        float value = Math::Interpolate::Lerp(w, Math::Interpolate::Lerp(v, Math::Interpolate::Lerp(u, Grad(perm[AA  ], x, y  , z  ), Grad(perm[BA  ], x - 1, y  , z  )),
                                                                         Math::Interpolate::Lerp(u, Grad(perm[AB  ], x, y - 1, z  ), Grad(perm[BB  ], x - 1, y - 1, z  ))),
                                              Math::Interpolate::Lerp(v, Math::Interpolate::Lerp(u, Grad(perm[AA + 1], x, y  , z - 1), Grad(perm[BA + 1], x - 1, y  , z - 1)),
                                                                      Math::Interpolate::Lerp(u, Grad(perm[AB + 1], x, y - 1, z - 1), Grad(perm[BB + 1], x - 1, y - 1, z - 1))));
        return (value+1.0f)*0.5f;
    }
    
    
    
    float PerlinNoise::Evaluate(const Math::Vector2 &vec) const {
        return Evaluate(vec.x, vec.y);
    }
    
    float PerlinNoise::Evaluate(const Math::Vector3 &vec) const {
        return Evaluate(vec.x, vec.y, vec.z);
    }
    
    
    
    void PerlinNoise::BuildPermutations()
    {
        random.SetMax((float)periodMinusOne);
        perm.reset(new int[period2]);
        
        for (int i=0; i<period; i++)
        {
            perm[i] = Math::FloorToInt(random.Next());
            
        }
        for (int i=0; i<period; i++)
        {
            perm[period+i] = perm[i];
        }
    }
    
    
}