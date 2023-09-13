#pragma once

#include <cmath>
#include "Limit.hpp"

namespace Candy::Math
{
    
    static constexpr const float MAX_FLOAT = Limit<float>::Max();
    static constexpr const float MIN_FLOAT = Limit<float>::Min();
    static constexpr const double MAX_DOUBLE = Limit<double>::Max();
    static constexpr const double MIN_DOUBLE = Limit<double>::Min();
    static constexpr const int MAX_INT = Limit<int>::Max();
    static constexpr const int MIN_INT = Limit<int>::Min();
    static constexpr const unsigned int MAX_UINT = Limit<unsigned int>::Max();
    static constexpr const unsigned int MIN_UINT = 0;
    static constexpr const char MAX_CHAR = Limit<char>::Max();
    static constexpr const char MIN_CHAR = Limit<char>::Min();
    static constexpr const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
    static constexpr const float Euler = 2.7182818284590452353602874713526624977572470f;
    static constexpr const float Tau = 6.28318530717958647692f;
    static constexpr const float Sqrt2 = 1.41421356237309504880f;
    static constexpr const float Sqrt3 = 1.73205080756887729352f;
    static constexpr const float Sqrt5 = 2.23606797749978969640f;
    static constexpr const float GoldenRatio = 1.61803398874989484820f;
    static constexpr const float SuperGoldenRatio = 1.46557123187676802665f;
    static constexpr const float SilverRatio = 2.41421356237309504880f;
    static constexpr const float Wallis = 2.09455148154232659148f;
    static constexpr const float Lemniscate = 2.62205755429211981046f;
    static constexpr const float Gravity = 6.67430f;
    static constexpr const float SpeedOfLightMetersPerSecond = 299792458.0f;
    
    template<int N>
    struct powerStruct;
    
    template<int N>
    struct powerStruct
    {
        template<typename T>
        static constexpr T Calc(const T &x)
        {
            if (N % 2 == 0)
            {
                return powerStruct<N / 2>::Calc(x * x);
            }
            else if (N % 3 == 0)
            {
                return powerStruct<N / 3>::Calc(x * x * x);
            }
            return powerStruct<N - 1>::Calc(x) * x;
        }
    };
    
    template<>
    struct powerStruct<0>
    {
        template<typename T>
        static constexpr T Calc(const T &)
        { return 1; }
    };
    
    template<typename T>
    inline float Floor(T value)
    { return std::floor(value); }
    
    template<typename T>
    inline float Ceil(float value)
    { return std::ceil(value); }
    
    template<typename T>
    inline float Round(float value)
    { return std::round(value); }
    
    
    inline int FloorToInt(float value)
    { return int(value + 16777218.) - 16777218; }
    
    inline int FloorToInt(double value)
    { return int(value + 16777218.) - 16777218; }
    
    
    inline int FloorToInt(int value)
    {return value;}
    
    inline int CeilToInt(float value)
    { return 16777218 - int(16777218. - value); }
    
    inline int RoundToInt(float value)
    {
        union Cast
        {
            double d;
            int i;
        };
        volatile Cast c;
        c.d = 6755399441055743.5 + value;
        return c.i;
    }
    
    inline int RoundToInt(double value)
    {
        union Cast
        {
            double d;
            long l;
        };
        volatile Cast c;
        c.d = value + 6755399441055743.5;
        return c.l;
    }
    
    template<int N, typename T>
    inline constexpr T Pow(const T &a)
    { return powerStruct<N>::Calc(a); }
    
    template<typename T>
    inline constexpr T Pow(const T &a, const T &b)
    { return std::pow(a, b); }
    
    template<typename T>
    inline constexpr T ToRadians(T degrees)
    { return degrees * (PI / 180.0); }
    
    template<typename T>
    inline constexpr T ToDegrees(T radians)
    { return radians * (180.0 / PI); }
    
    template<typename T>
    int Sign(T value)
    { return (value > 0) - (value < 0); }
  
    inline float SignFloat(float x)
    {return (x < 0) ? -1.0f : 1.0f;}
    
    template<typename T>
    inline T Sin(T angle)
    { return std::sin(angle); }
    
    template<typename T>
    inline T Cos(T angle)
    { return std::cos(angle); }
    
    template<typename T>
    inline T Tan(const T &angle)
    { return std::tan(angle); }
    
    template<typename T>
    inline T Csc(const T &angle)
    { return 1 / Sin(angle); }
    
    template<typename T>
    inline T Sec(const T &angle)
    { return 1 / Cos(angle); }
    
    template<typename T>
    inline T Cot(const T &angle)
    { return 1 / Tan(angle); }
    
    template<typename T>
    inline T Asin(const T &x)
    { return std::asin(x); }
    
    template<typename T>
    inline T Acos(const T &x)
    { return std::acos(x); }
    
    template<typename T>
    inline T Atan(const T &x)
    { return std::atan(x); }
    
    template<typename T>
    inline T Atan2(const T &y, const T &x)
    { return std::atan2(y, x); }
    
    template<typename T>
    inline T Sqrt(T value)
    { return std::sqrt(value); }
    
    template<>
    inline float Sqrt<float>(float value)
    { return sqrtf(value); }
    
    template<typename T>
    inline T Cbrt(const T &value)
    { return std::cbrt(value); }
    
    template<typename T>
    inline T Root(const T &root, const T &value)
    { return std::pow(value, 1 / root); }
    
    template<typename T>
    inline T Exp(T x)
    { return std::pow(Euler, x); }
    
    template<typename T>
    inline T Exp2(T  x)
    { return std::pow(2, x); }
    
    template<typename T>
    inline T Log10(T x)
    { return std::log10(x); }
    
    template<typename T>
    inline T Log2(const T &x)
    { return std::log2(x); }
    
    template<typename T>
    inline T Ln(const T &x)
    { return std::log(x); }
    
    template<typename T>
    inline T LogBase(const T &base, const T &x)
    { return std::log10(x) / std::log10(base); }
    
    template<typename T>
    inline bool IsPositive(const T &value)
    { return value > 0; }
    
    template<typename T>
    inline bool IsNegative(const T &value)
    { return value < 0; }
    
    inline bool IsEven(int value)
    { return value % 2 == 0; }
    
    inline bool IsOdd(int value)
    { return !IsEven(value); }
    
    inline bool IsEven(long value)
    { return value % 2 == 0; }
    
    inline bool IsOdd(long value)
    { return !IsEven(value); }
    
    inline bool IsEven(long long value)
    { return value % 2 == 0; }
    
    inline bool IsOdd(long long value)
    { return !IsEven(value); }
    
    
    template<typename T>
    inline T Pow2(const T &a)
    { return a * a; }
    
    template<typename T>
    inline T Pow3(const T &a)
    { return a * a * a; }
    
    template<typename T>
    inline T Pow4(const T &a)
    { return a * a * a * a; }
    
    template<typename T>
    inline T Pow5(const T &a)
    { return a * a * a * a * a; }
    
    template<typename T>
    inline T Pow6(const T &a)
    { return a * a * a * a * a * a; }
    
    template<typename T>
    inline T Pow7(const T &a)
    { return a * a * a * a * a * a * a; }
    
    template<typename T>
    inline T Pow8(const T &a)
    { return a * a * a * a * a * a * a * a; }
    
    template<typename T>
    inline T Pow9(const T &a)
    { return a * a * a * a * a * a * a * a * a; }
    
    template<typename T>
    inline T Pow10(const T &a)
    { return a * a * a * a * a * a * a * a * a * a; }
    
    template<typename T>
    inline T Pow100(const T &a)
    { return Pow10(a) * Pow10(a); }
    
    template<typename T>
    inline T Clamp(const T &value, const T &min, const T &max)
    {
        return value < min ? min : value > max ? max : value;
    }
    
    template<typename T>
    inline T Clamp01(const T &value)
    { return value < 0 ? 0 : value > 1 ? 1 : value; }
    
    template<typename T>
    inline T Max(const T &a, const T &b)
    { return a < b ? b : a; }
    
    template<typename T>
    inline T Max(const T &a, const T &b, const T &c)
    { return Max(a, Max(b, c)); }
    
    template<typename T>
    inline T Max(const T &a, const T &b, const T &c, const T &d)
    { return Max(Max(a, b), Max(c, d)); }
    
    template<typename T>
    inline T Min(const T &a, const T &b)
    { return b < a ? b : a; }
    
    template<typename T>
    inline T Abs(const T &a)
    { return std::abs(a); }
    
    template<typename T>
    inline T Normalize(const T &value, const T &min, const T &max)
    { return (value - min) / (max - min); }
    
    template<typename T>
    inline T BellCurve(const T &x, const T &curveHeight, const T &curveWidth)
    {
        return std::pow(Euler, (-curveHeight * x * x) + curveWidth);
    }
    
    template<typename T>
    inline T Porabola(const T &x, const T &curveIntensity, const T &xShift)
    {
        return curveIntensity * Pow2(x - xShift);
    }
    
    template<typename T>
    T Epsilon()
    { return std::numeric_limits<T>::epsilon(); }
    
    template<typename T>
    bool EpsilonEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
    {return (a == b) || (Abs(a - b) < epsilon);}
  
  template<typename T>
  bool EpsilonNotEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
  {return ! EpsilonEqual(a, b, epsilon);}
  
  
    
    
    namespace Interpolate
    {
        inline float Smoothstep(float edge0, float edge1, float x)
        {
            if (x < edge0)
            {
                return 0.0f;
            }
            if (x >= edge1)
            {
                return 1.0f;
            }
            return x * x * (3 - 2 * x);
        }
        
        // Ken Perlin improved smoothstep. (slightly slower running time)
        inline float Smootherstep(float edge0, float edge1, float x)
        {
            x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
            return ((6 * x - 15) * x + 10) * x * x * x;
        }
        
        inline float InverseSmoothstep(float x)
        { return 0.5f - Sin(Asin(1.0f - 2.0f * x) / 3.0f); }
        
        inline float Lerp(float a, float b, float t)
        { return a + t * (b - a); }
        
        inline float CosineInterpolate(float a, float b, float t)
        {
            float t2 = (1.0f - Cos(t * PI)) / 2.0f;
            return a * (1.0f - t2) + b * t2;
        }
        
        inline float Fade(float t)
        { return ((6 * t - 15) * t + 10) * t * t * t; }
    }
    
}
