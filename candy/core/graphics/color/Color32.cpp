#include "Color32.hpp"
#include <algorithm>
#include "ColorAll.hpp"
namespace Candy {
    Color32::Color32() : Math::VectorBase<uint8, 4>() {}
    
    Color32::Color32(uint8 redValue, uint8 greenValue, uint8 blueValue, uint8 alphaValue) : Math::VectorBase<uint8, 4>(redValue, greenValue, blueValue, alphaValue) {}
    
    Color32::Color32(const Color32 &other) : Math::VectorBase<uint8, 4>(other) {}
    
    uint8 Color32::ClampValue(uint8 value) { return value < 0 ? 0 : value > 255 ? 255 : value; }
    
    Color32 Color32::CLAMP(uint8 r, uint8 g, uint8 b, uint8 a) {
        return Color32(ClampValue(r), ClampValue(g), ClampValue(b), ClampValue(a));
    }
    
    bool Color32::operator==(const Color32 &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    
    bool Color32::operator!=(const Color32 &other) const { return !(*this == other); }
    
    Color32 Color32::operator+(const Color32 &other) const {
        return CLAMP(r + other.r, g + other.g, b + other.b, a + other.a);
    }
    
    Color32 Color32::operator-(const Color32 &other) const {
        return CLAMP(r - other.r, g - other.g, b - other.b, a - other.a);
    }
    
    Color32 Color32::operator*(const Color32 &other) const {
        return CLAMP(r * other.r, g * other.g, b * other.b, a * other.a);
    }
    
    Color32 Color32::operator*(uint8 scalar) const {
        return CLAMP(r * scalar, g * scalar, b * scalar, a * scalar);
    }
    
    
    void Color32::operator+=(const Color32 &other) {
        r = ClampValue(r + other.r);
        g = ClampValue(g + other.g);
        b = ClampValue(b + other.b);
        a = ClampValue(a + other.a);
    }
    
    void Color32::operator-=(const Color32 &other) {
        r = ClampValue(r - other.r);
        g = ClampValue(g - other.g);
        b = ClampValue(b - other.b);
        a = ClampValue(a - other.a);
    }
    
    void Color32::operator*=(const Color32 &other) {
        r = ClampValue(r * other.r);
        g = ClampValue(g * other.g);
        b = ClampValue(b * other.b);
        a = ClampValue(a * other.a);
    }
    
    void Color32::operator*=(uint8 scalar) {
        r = ClampValue(r * scalar);
        g = ClampValue(g * scalar);
        b = ClampValue(b * scalar);
        a = ClampValue(a * scalar);
    }
    
    Color Color32::ToRGBA()const
    {
        return Color(r/255.f, g/255.f, b/255.f, a/255.f);
    }
}


