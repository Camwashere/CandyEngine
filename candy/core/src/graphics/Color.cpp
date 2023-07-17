#include <candy/graphics/Color.hpp>
#include <bits/stdc++.h>

namespace Candy {
    using namespace Math;
    Color::Color() : Math::VectorBase<float, 4>() {}
    Color::Color(const Color &other) : Math::VectorBase<float, 4>(other){};
    Color::Color(float value) : Math::VectorBase<float, 4>(value){}
    //Color::Color(const float *data) : VectorBase<float, 4>(data) {}
    Color::Color(const Math::Vector2 &vector) : VectorBase<float, 4>(vector.x, vector.y, 0, 1){}
    Color::Color(const Math::Vector3 &vector) : VectorBase<float, 4>(vector.x, vector.y, vector.z, 1) {}
    Color::Color(const Math::Vector4 &vector) : VectorBase<float, 4>(vector) {}
    Color::Color(const Math::Quaternion &quaternion) : VectorBase<float, 4>(quaternion.x, quaternion.y, quaternion.z, quaternion.w) {}
    
    const Color Color::red(1, 0, 0);
    const Color Color::green(0, 1, 0);
    const Color Color::blue(0, 0, 1);
    const Color Color::black(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::white(1, 1, 1);
    const Color Color::grey(0.5f, 0.5f, 0.5f);
    const Color Color::clear(0, 0, 0, 0);
    
    const Color Color::teal(0, 1, 1);
    const Color Color::magenta(1, 0, 1);
    const Color Color::yellow(1.0f, 0.92f, 0.016);
    const Color Color::orange(1.0f, 0.647f, 0.0f);
    const Color Color::purple(0.627f, 0.125f, 0.941f);
    const Color Color::brown(0.588f, 0.294f, 0.0f);
    const Color coral(1.0f, 0.5f, 0.31f);
    
    
    
    
    Color::operator Math::Vector2()const{return ToVector2();}
    Color::operator Math::Vector3()const{return ToVector3();}
    Color::operator Math::Quaternion()const{return ToQuaternion();}
    
    
    
    Math::Vector2 Color::ToVector2()const
    {
        return {r, g};
    }
    Math::Vector3 Color::ToVector3()const
    {
        return {r, g, b};
    }
    Math::Vector4 Color::ToVector4()const
    {
        return {r, g, b, a};
    }
    Math::Quaternion Color::ToQuaternion() const
    {
        return {r, g, b, a};
    }
    
    
    Color Color::Lerp(const Color &left, const Color &right, float t) {
        float oneMinusT = 1 - t;
        return {left.r * oneMinusT + right.r * t, left.g * oneMinusT + right.g * t, left.b * oneMinusT + right.b, left.a * oneMinusT + right.a};
    }
    
    Color Color::LerpClamped(const Color &a, const Color &b, float t) {
        if (t < 0) {
            return a;
        }
        if (t > 1) {
            return b;
        }
        float oneMinusT = 1 - t;
        return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t,
                a.w * oneMinusT + b.w * t};
    }
    
    Color Color::InverseLerp(const Color &a, const Color &b, float t) {
        return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z), (t - a.w) / (b.w - a.w)};
    }
    
    Color Color::Max(const Color &a, const Color &b) {
        return {Math::Max(a.r, b.r), Math::Max(a.g, b.g), Math::Max(a.b, b.b), Math::Max(a.a, b.a)};
    }
    
    Color Color::Min(const Color &a, const Color &b) {
        return {Math::Min(a.r, b.r), Math::Min(a.g, b.g), Math::Min(a.b, b.b), Math::Min(a.a, b.a)};
    }
    
    Color Color::Average(const Color &a, const Color &b) {
        return (a+b)/2.0f;
    }
    
    Color Color::Normalize(const Color &vec) {
        return vec.Normalized();
    }
    Color Color::Grey(float shade)
    {
        return {shade, shade, shade, 1.0f};
    }
    
    
    
    
   
    
    
    
    void Color::Invert() {r = 1.0f-r; g=1.0f-g; b=1.0f-b;}
    
    float Color::MaxComponent() const {return Math::Max(r, g, b, a);}
    
    Color Color::Inverted() const {return Color(1.0f-r, 1.0f-g, 1.0f-b);}
    
    Color Color::ReversedRGB() const {return Color(b, g, r, a);}
    
    Color Color::ReversedRGBA() const {return Color(a, b, g, r);}
    
    
    float Saturate(float f){ return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
    
    float Color::Grayscale() const { return (0.299f * r) + (0.587f * g) + (0.114f * b); }
    
    Color Color::rr() const {
        return {r, r, 0, a};
    }
    
    Color Color::rg() const {
        return {r, g, 0, a};
    }
    
    Color Color::rb() const {
        return {r, b, 0, a};
    }
    
    Color Color::gr() const {
        return {g, r, 0, a};
    }
    
    Color Color::gg() const {
        return {g, g, 0, a};
    }
    
    Color Color::gb() const {
        return {g, b, 0, a};
    }
    
    Color Color::br() const {
        return {b, r, 0, a};
    }
    
    Color Color::bg() const {
        return {b, g, 0, a};
    }
    
    Color Color::bb() const {
        return {b, b, 0, a};
    }
    
    Color Color::rrr() const {
        return {r, r, r, a};
    }
    
    Color Color::rrg() const {
        return {r, r, g, a};
    }
    
    Color Color::rrb() const {
        return {r, r, b, a};
    }
    
    Color Color::rgr() const {
        return {r, g, r, a};
    }
    
    Color Color::rgg() const {
        return {r, g, g, a};
    }
    
    Color Color::rgb() const {
        return {r, g, b, a};
    }
    
    Color Color::rbr() const {
        return {r, b, r, a};
    }
    
    Color Color::rbg() const {
        return {r, b, g, a};
    }
    
    Color Color::rbb() const {
        return {r, b, b, a};
    }
    
    Color Color::grr() const {
        return {g, r, r, a};
    }
    
    Color Color::grg() const {
        return {g, r, g, a};
    }
    
    Color Color::grb() const {
        return {g, r, b, a};
    }
    
    Color Color::ggr() const {
        return {g, g, r, a};
    }
    
    Color Color::ggg() const {
        return {g, g, g, a};
    }
    
    Color Color::ggb() const {
        return {g, g, b, a};
    }
    
    Color Color::gbr() const {
        return {g, b, r, a};
    }
    
    Color Color::gbg() const {
        return {g, b, g, a};
    }
    
    Color Color::gbb() const {
        return {g, b, b, a};
    }
    
    Color Color::brr() const {
        return {b, r, r, a};
    }
    
    Color Color::brg() const {
        return {b, r, g, a};
    }
    
    Color Color::brb() const {
        return {b, r, b, a};
    }
    
    Color Color::bgr() const {
        return {b, g, r, a};
    }
    
    Color Color::bgg() const {
        return {b, g, g, a};
    }
    
    Color Color::bgb() const {
        return {b, g, b, a};
    }
    
    Color Color::bbr() const {
        return {b, b, r, a};
    }
    
    Color Color::bbg() const {
        return {b, b, g, a};
    }
    
    Color Color::bbb() const {
        return {b, b, b, a};
    }
    
}



