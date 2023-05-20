#include "Color.hpp"
#include "ColorAll.hpp"
#include <bits/stdc++.h>
namespace Candy {
    using namespace Math;
    Color::Color() : Math::VectorBase<float, 4>() {}
    Color::Color(const Color &other) : Math::VectorBase<float, 4>(other){};
    Color::Color(float value) : Math::VectorBase<float, 4>(value){}
    Color::Color(const float *data) : VectorBase<float, 4>(data) {}
    Color::Color(const std::string &hex) : VectorBase<float, 4>(HEXtoRGB(hex)){}
    Color::Color(uint hexValue) : VectorBase<float, 4>(HEXtoRGB(hexValue)) {}
    Color::Color(const Math::Vector2 &vector) : VectorBase<float, 4>(vector.x, vector.y, 0, 1){}
    Color::Color(const Math::Vector3 &vector) : VectorBase<float, 4>(vector.x, vector.y, vector.z, 1) {}
    Color::Color(const Math::Vector4 &vector) : VectorBase<float, 4>(vector) {}
    Color::Color(const Math::Quaternion &quaternion) : VectorBase<float, 4>(quaternion.x, quaternion.y, quaternion.z, quaternion.w) {}
    Color::Color(const Color32 &other) : VectorBase<float, 4>(RGB32toRGB(other)) {}
    Color::Color(const ColorHSV &other) : VectorBase<float, 4>(HSVtoRGB(other)) {}
    Color::Color(const ColorHSL &other) : VectorBase<float, 4>(HSLtoRGB(other)) {}
    Color::Color(const ColorCMYK &other) : VectorBase<float, 4>(CMYKtoRGB(other)) {}
    Color::Color(const ColorYIQ &other) : VectorBase<float, 4>(YIQtoRGB(other)) {}
    
    const Color Color::red(1, 0, 0);
    const Color Color::green(0, 1, 0);
    const Color Color::blue(0, 0, 1);
    const Color Color::black(0, 0, 0);
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
    
    Color Color::HSVtoRGB(float h, float s, float v, float a) {
        float s1 = s / 100.0f;
        float v1 = v / 100.0f;
        float c = s1 * v;
        float x = c * (1 - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = v1 - c;
        float r, g, b;
        if (h >= 0 && h < 60) {
            r = c, g = x, b = 0;
        } else if (h >= 60 && h < 120) {
            r = x, g = c, b = 0;
        } else if (h >= 120 && h < 180) {
            r = 0, g = c, b = x;
        } else if (h >= 180 && h < 240) {
            r = 0, g = x, b = c;
        } else if (h >= 240 && h < 300) {
            r = x, g = 0, b = c;
        } else {
            r = c, g = 0, b = x;
        }
        return {(r + m), (g + m), (b + m), a};
    }
    
    Color Color::HSVtoRGB(const ColorHSV &hsv) {
        return HSVtoRGB(hsv.h, hsv.s, hsv.v, hsv.a);
    }
    
    Color Color::RGB32toRGB(uint8 r, uint8 g, uint8 b, uint8 a) {
        return Color(static_cast<float>(r/255.0f), static_cast<float>(g/255.0f), static_cast<float>(b/255.0f), static_cast<float>(a/255.0f));
    }
    
    Color Color::RGB32toRGB(const Color32 &color) {
        return Color(RGB32toRGB(color.r, color.g, color.b, color.a));
    }
    
    
    
    float HueToRgb(float p, float q, float t){
        if(t < 0) t += 1;
        if(t > 1) t -= 1;
        if(t < 1/6) return p + (q - p) * 6 * t;
        if(t < 1/2) return q;
        if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
        return p;
    }
    
    Color Color::HSLtoRGB(float h, float s, float l, float a) {
        float r, g, b;
        if (s==0)
        {
            r = g = b = l;
        }
        else
        {
            float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            float p = 2 * l - q;
            r = HueToRgb(p, q, h + 1/3);
            g = HueToRgb(p, q, h);
            b = HueToRgb(p, q, h - 1/3);
        }
        return Color(r, g, b, a);
    }
    
    Color Color::HSLtoRGB(const ColorHSL &hsl) {
        return HSLtoRGB(hsl.h, hsl.s, hsl.l, hsl.a);
    }
    
    Color Color::CMYKtoRGB(const ColorCMYK &cmyk) {
        return Color();
    }
    
    Color Color::YIQtoRGB(const ColorYIQ &yiq) {
        return Color();
    }
    
    std::vector<std::string> SplitWithCharacters(const std::string& str, int splitLength) {
        int NumSubstrings = str.length() / splitLength;
        std::vector<std::string> ret;
        
        for (int i = 0; i < NumSubstrings; i++) {
            ret.push_back(str.substr(i * splitLength, splitLength));
        }
        
        // If there are leftover characters, create a shorter item at the end.
        if (str.length() % splitLength != 0) {
            ret.push_back(str.substr(splitLength * NumSubstrings));
        }
        
        return ret;
    }
    
    Color Color::HEXtoRGB(const std::string &hexValue) {
        std::string hex = hexValue;
        float r, g, b;
        if (hex.at(0) == '#') {
            hex.erase(0, 1);
        }
        
        while (hex.length() != 6) {
            hex += "0";
        }
        
        std::vector<std::string> colori = SplitWithCharacters(hex, 2);
        
        r = stoi(colori[0], nullptr, 16);
        g = stoi(colori[1], nullptr, 16);
        b = stoi(colori[2], nullptr, 16);
        
        return Color(r, g, b);
    }
    
    
    
    Color Color::HEXtoRGB(uint hexValue) {
        return Color(((hexValue >> 16) & 0xFF) / 255.0f, ((hexValue >> 8) & 0xFF) / 255.0f,
                     ((hexValue) & 0xFF) / 255.0);
    }
    
    bool Color::operator==(const Color &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    
    bool Color::operator!=(const Color &other) const {
        return !(r == other.r && g == other.g && b == other.b && a == other.a);
    }
    
    void Color::operator+=(const Color &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        a += other.a;
    }
    
    void Color::operator-=(const Color &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        a -= other.a;
    }
    
    void Color::operator*=(const Color &other) {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        a *= other.a;
    }
    
    void Color::operator/=(const Color &other) {
        r /= other.r;
        g /= other.g;
        b /= other.b;
        a /= other.a;
    }
    
    void Color::operator*=(float scalar) {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        a *= scalar;
    }
    
    void Color::operator/=(float scalar) {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        a /= scalar;
    }
    
    Color::operator Math::Vector2()const{return ToVector2();}
    Color::operator Math::Vector3()const{return ToVector3();}
    Color::operator Math::Vector4() const {return ToVector4();}
    Color::operator Math::Quaternion()const{return ToQuaternion();}
    
    
    
    Math::Vector2 Color::ToVector2()const
    {
        return Math::Vector2(r, g);
    }
    Math::Vector3 Color::ToVector3()const
    {
        return Math::Vector3(r, g, b);
    }
    Math::Vector4 Color::ToVector4()const
    {
        return Math::Vector4(r, g, b, a);
    }
    Math::Quaternion Color::ToQuaternion() const
    {
        return Math::Quaternion(r, g, b, a);
    }
    
    
    Color32 Color::ToColor32()const
    {
        return Color32(Math::RoundToInt(r*255), Math::RoundToInt(g*255), Math::RoundToInt(b*255), Math::RoundToInt(a*255));
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
        return Color(Math::Max(a.r, b.r), Math::Max(a.g, b.g), Math::Max(a.b, b.b), Math::Max(a.a, b.a));
    }
    
    Color Color::Min(const Color &a, const Color &b) {
        return Color(Math::Min(a.r, b.r), Math::Min(a.g, b.g), Math::Min(a.b, b.b), Math::Min(a.a, b.a));
    }
    
    Color Color::Average(const Color &a, const Color &b) {
        return (a+b)/2.0f;
    }
    
    Color Color::Normalize(const Color &vec) {
        return vec.Normalized();
    }
    Color Color::Grey(float shade)
    {
        return Color(shade, shade, shade, 1.0f);
    }
    
    
    
    
    void Color::Normalize() {
        float mag = Magnitude();
        r/=mag;
        g/=mag;
        b/=mag;
        a/=mag;
    }
    
    Color Color::Normalized() const {
        float mag = Magnitude();
        return {r / mag, g / mag, b/mag, a/mag};
    }
    
    float Color::Magnitude() const {
        return Sqrt(r*r + g*g + b*b + a*a);
    }
    
    float Color::SqrMagnitude() const {
        return r*r + g*g + b*b + a*a;
    }
    
    
    
    void Color::Invert() {r = 1.0f-r; g=1.0f-g; b=1.0f-b;}
    
    float Color::MaxComponent() const {return Math::Max(r, g, b, a);}
    
    Color Color::Inverted() const {return Color(1.0f-r, 1.0f-g, 1.0f-b);}
    
    Color Color::ReversedRGB() const {return Color(b, g, r, a);}
    
    Color Color::ReversedRGBA() const {return Color(a, b, g, r);}
    
    
    float Saturate(float f){ return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
    uint32 Color::Pack()const
    {
        uint32 out;
        out  = ((uint32)((int)(Saturate(r) * 255.0f + 0.5f))) << Color32::RED_SHIFT;
        out |= ((uint32)((int)(Saturate(g) * 255.0f + 0.5f))) << Color32::GREEN_SHIFT;
        out |= ((uint32)((int)(Saturate(b) * 255.0f + 0.5f))) << Color32::BLUE_SHIFT;
        out |= ((uint32)((int)(Saturate(a) * 255.0f + 0.5f))) << Color32::ALPHA_SHIFT;
        return out;
    }
    
    Color Color::PackedToColor(uint32 packedValue)
    {
        constexpr static float s = 1.0f / 255.0f;
        return Color(
                ((packedValue >> Color32::RED_SHIFT) & 0xFF) * s,
                ((packedValue >> Color32::GREEN_SHIFT) & 0xFF) * s,
                ((packedValue >> Color32::BLUE_SHIFT) & 0xFF) * s,
                ((packedValue >> Color32::ALPHA_SHIFT) & 0xFF) * s);
    }
    
    
    
    float Color::Grayscale() const { return (0.299f * r) + (0.587f * g) + (0.114f * b); }
    
    Color Color::rr() const {
        return Color(r, r, 0, a);
    }
    
    Color Color::rg() const {
        return Color(r, g, 0, a);
    }
    
    Color Color::rb() const {
        return Color(r, b, 0, a);
    }
    
    Color Color::gr() const {
        return Color(g, r, 0, a);
    }
    
    Color Color::gg() const {
        return Color(g, g, 0, a);
    }
    
    Color Color::gb() const {
        return Color(g, b, 0, a);
    }
    
    Color Color::br() const {
        return Color(b, r, 0, a);
    }
    
    Color Color::bg() const {
        return Color(b, g, 0, a);
    }
    
    Color Color::bb() const {
        return Color(b, b, 0, a);
    }
    
    Color Color::rrr() const {
        return Color(r, r, r, a);
    }
    
    Color Color::rrg() const {
        return Color(r, r, g, a);
    }
    
    Color Color::rrb() const {
        return Color(r, r, b, a);
    }
    
    Color Color::rgr() const {
        return Color(r, g, r, a);
    }
    
    Color Color::rgg() const {
        return Color(r, g, g, a);
    }
    
    Color Color::rgb() const {
        return Color(r, g, b, a);
    }
    
    Color Color::rbr() const {
        return Color(r, b, r, a);
    }
    
    Color Color::rbg() const {
        return Color(r, b, g, a);
    }
    
    Color Color::rbb() const {
        return Color(r, b, b, a);
    }
    
    Color Color::grr() const {
        return Color(g, r, r, a);
    }
    
    Color Color::grg() const {
        return Color(g, r, g, a);
    }
    
    Color Color::grb() const {
        return Color(g, r, b, a);
    }
    
    Color Color::ggr() const {
        return Color(g, g, r, a);
    }
    
    Color Color::ggg() const {
        return Color(g, g, g, a);
    }
    
    Color Color::ggb() const {
        return Color(g, g, b, a);
    }
    
    Color Color::gbr() const {
        return Color(g, b, r, a);
    }
    
    Color Color::gbg() const {
        return Color(g, b, g, a);
    }
    
    Color Color::gbb() const {
        return Color(g, b, b, a);
    }
    
    Color Color::brr() const {
        return Color(b, r, r, a);
    }
    
    Color Color::brg() const {
        return Color(b, r, g, a);
    }
    
    Color Color::brb() const {
        return Color(b, r, b, a);
    }
    
    Color Color::bgr() const {
        return Color(b, g, r, a);
    }
    
    Color Color::bgg() const {
        return Color(b, g, g, a);
    }
    
    Color Color::bgb() const {
        return Color(b, g, b, a);
    }
    
    Color Color::bbr() const {
        return Color(b, b, r, a);
    }
    
    Color Color::bbg() const {
        return Color(b, b, g, a);
    }
    
    Color Color::bbb() const {
        return Color(b, b, b, a);
    }
    
}



