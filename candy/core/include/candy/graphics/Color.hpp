#pragma once
#include "color/ColorBase.hpp"
#include "candy/math/Vector.hpp"
#include "candy/math/Quaternion.hpp"
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
        Color();
        explicit Color(float value);
        Color(float redValue, float greenValue, float blueValue, float alphaValue = 1.0f) : Math::VectorBase<float, 4>(redValue, greenValue, blueValue, alphaValue){}
        Color(const Color &other);
        //explicit Color(const float* data);
        explicit Color(const std::string& hex);
        explicit Color(const Math::Vector2& vector);
        explicit Color(const Math::Vector3& vector);
        explicit Color(const Math::Vector4& vector);
        explicit Color(const Math::Quaternion& quaternion);
        
        template<typename E>
        Color(const VectorExpression<float, E> &expr) : VectorBase<float, 4>(expr) {}
    
    
    public:
      
        using VectorBase<float, 4>::operator==;
        using VectorBase<float, 4>::operator!=;
        using VectorBase<float, 4>::operator+=;
        using VectorBase<float, 4>::operator-=;
        using VectorBase<float, 4>::operator*=;
        using VectorBase<float, 4>::operator/=;
        
        bool operator==(const Color &other) const;
        
        bool operator!=(const Color &other) const;
        
        
        explicit operator Math::Vector2()const;
        explicit operator Math::Vector3()const;
        explicit operator Math::Quaternion()const;
    
    public:
        void Invert();
        [[nodiscard]] float Grayscale() const;
    
    public:
        [[nodiscard]] float MaxComponent()const;
        [[nodiscard]] Color Inverted()const;
        [[nodiscard]] Color ReversedRGB()const;
        [[nodiscard]] Color ReversedRGBA()const;
    
    public:
        [[nodiscard]] Math::Vector2 ToVector2()const;
        [[nodiscard]] Math::Vector3 ToVector3()const;
        [[nodiscard]] Math::Vector4 ToVector4()const;
        [[nodiscard]] Math::Quaternion ToQuaternion()const;
        [[nodiscard]] Color rr() const;
        [[nodiscard]] Color rg() const;
        [[nodiscard]] Color rb() const;
        [[nodiscard]] Color gr() const;
        [[nodiscard]] Color gg() const;
        [[nodiscard]] Color gb() const;
        [[nodiscard]] Color br() const;
        [[nodiscard]] Color bg() const;
        [[nodiscard]] Color bb() const;
        [[nodiscard]] Color rrr() const;
        [[nodiscard]] Color rrg() const;
        [[nodiscard]] Color rrb() const;
        [[nodiscard]] Color rgr() const;
        [[nodiscard]] Color rgg() const;
        [[nodiscard]] Color rgb() const;
        [[nodiscard]] Color rbr() const;
        [[nodiscard]] Color rbg() const;
        [[nodiscard]] Color rbb() const;
        [[nodiscard]] Color grr() const;
        [[nodiscard]] Color grg() const;
        [[nodiscard]] Color grb() const;
        [[nodiscard]] Color ggr() const;
        [[nodiscard]] Color ggg() const;
        [[nodiscard]] Color ggb() const;
        [[nodiscard]] Color gbr() const;
        [[nodiscard]] Color gbg() const;
        [[nodiscard]] Color gbb() const;
        [[nodiscard]] Color brr() const;
        [[nodiscard]] Color brg() const;
        [[nodiscard]] Color brb() const;
        [[nodiscard]] Color bgr() const;
        [[nodiscard]] Color bgg() const;
        [[nodiscard]] Color bgb() const;
        [[nodiscard]] Color bbr() const;
        [[nodiscard]] Color bbg() const;
        [[nodiscard]] Color bbb() const;
        
        
    };
}

