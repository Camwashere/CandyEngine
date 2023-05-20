#pragma once

#include "ColorForwardDef.hpp"
#include "../../../include/Candy/Math.hpp"
#include <string>
namespace Candy {
    
    struct Color : public ColorBase<ColorFormat::RGB>, public Math::VectorBase<float, 4>{
    public:
        static const Color red;
        static const Color green;
        static const Color blue;
        static const Color black;
        static const Color white;
        static const Color grey;
        static const Color clear;
        
        static const Color teal;
        static const Color magenta;
        static const Color yellow;
        static const Color orange;
        static const Color purple;
        static const Color brown;
        static const Color coral;
    
    public:
        static Color Lerp(const Color& left, const Color& right, float t);
        static Color LerpClamped(const Color &a, const Color &b, float t);
        static Color InverseLerp(const Color &a, const Color &b, float t);
        static Color Max(const Color &a, const Color &b);
        static Color Min(const Color &a, const Color &b);
        static Color Average(const Color &a, const Color &b);
        static Color Normalize(const Color &vec);
        static Color Grey(float shade);
    
    
    public:
        static Color RGB32toRGB(uint8 r, uint8 g, uint8 b, uint8 a=255);
        static Color RGB32toRGB(const Color32& color);
        static Color HSVtoRGB(float h, float s, float v, float a=1.0f);
        static Color HSVtoRGB(const ColorHSV& hsv);
        static Color HSLtoRGB(float h, float s, float l, float a=1.0f);
        static Color HSLtoRGB(const ColorHSL& hsl);
        static Color CMYKtoRGB(const ColorCMYK& cmyk);
        static Color YIQtoRGB(const ColorYIQ& yiq);
        static Color HEXtoRGB(uint hexValue);
        static Color HEXtoRGB(const std::string& hexValue);
        static Color PackedToColor(uint32 packedValue);
    
    
    
    public:
        Color();
        Color(float value);
        constexpr Color(float redValue, float greenValue, float blueValue, float alphaValue = 1.0f) : Math::VectorBase<float, 4>(redValue, greenValue, blueValue, alphaValue){}
        Color(const Color &other);
        Color(const float* data);
        Color(const std::string& hex);
        Color(uint32 packedValue);
        Color(const Math::Vector2& vector);
        Color(const Math::Vector3& vector);
        Color(const Math::Vector4& vector);
        Color(const Math::Quaternion& quaternion);
        Color(const Color32& other);
        Color(const ColorHSV& other);
        Color(const ColorHSL& other);
        Color(const ColorCMYK& other);
        Color(const ColorYIQ& other);
        
        template<typename E>
        Color(const VectorExpression<float, E> &expr) : VectorBase<float, 4>(expr) {}
    
    
    public:
        
        bool operator==(const Color &other) const;
        
        bool operator!=(const Color &other) const;
        
        
        void operator+=(const Color &other);
        
        void operator-=(const Color &other);
        
        void operator*=(const Color &other);
        
        void operator/=(const Color &other);
        
        void operator*=(float scalar);
        
        void operator/=(float scalar);
        
        operator Math::Vector2()const;
        operator Math::Vector3()const;
        operator Math::Vector4()const;
        operator Math::Quaternion()const;
    
    public:
        void Normalize();
        Color Normalized()const;
        float Magnitude() const;
        float SqrMagnitude() const;
        void Invert();
        float Grayscale() const;
    
    public:
        float MaxComponent()const;
        Color Inverted()const;
        Color ReversedRGB()const;
        Color ReversedRGBA()const;
    
    public:
        uint32 Pack()const;
        Math::Vector2 ToVector2()const;
        Math::Vector3 ToVector3()const;
        Math::Vector4 ToVector4()const;
        Math::Quaternion ToQuaternion()const;
        Color32 ToColor32()const;
        Color rr() const;
        Color rg() const;
        Color rb() const;
        Color gr() const;
        Color gg() const;
        Color gb() const;
        Color br() const;
        Color bg() const;
        Color bb() const;
        Color rrr() const;
        Color rrg() const;
        Color rrb() const;
        Color rgr() const;
        Color rgg() const;
        Color rgb() const;
        Color rbr() const;
        Color rbg() const;
        Color rbb() const;
        Color grr() const;
        Color grg() const;
        Color grb() const;
        Color ggr() const;
        Color ggg() const;
        Color ggb() const;
        Color gbr() const;
        Color gbg() const;
        Color gbb() const;
        Color brr() const;
        Color brg() const;
        Color brb() const;
        Color bgr() const;
        Color bgg() const;
        Color bgb() const;
        Color bbr() const;
        Color bbg() const;
        Color bbb() const;
        
        
    };
}

