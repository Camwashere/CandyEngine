#pragma once
#include "../../../include/Candy/Math.hpp"
#include "ColorForwardDef.hpp"
namespace Candy {
    struct Color32 : public ColorBase<ColorFormat::RGB32>, public Math::VectorBase<uint8, 4> {
    private:
        static uint8 ClampValue(uint8 value);
        
        static Color32 CLAMP(uint8 r, uint8 g, uint8 b, uint8 a);
        
        //uint8 r, g, b, a;
    
    public:
        static constexpr uint32 RED_SHIFT = 0;
        static constexpr uint32 GREEN_SHIFT = 8;
        static constexpr uint32 BLUE_SHIFT =16;
        static constexpr uint32 ALPHA_SHIFT=24;
        static constexpr uint32 ALPHA_MASK=0xFF000000;
    
    public:
        Color32();
        
        Color32(uint8 redValue, uint8 greenValue, uint8 blueValue, uint8 alphaValue = 255);
        
        Color32(const Color32 &other);
    
    private:
        inline uint8 *ptr() { return &r; }
        
        [[nodiscard]] inline const uint8 *ptr() const { return &r; }
    
    public:
    public:
        inline uint8 &operator[](int index) { return ptr()[index]; }
        
        inline uint8 operator[](int index) const { return ptr()[index]; }
        
        bool operator==(const Color32 &other) const;
        
        bool operator!=(const Color32 &other) const;
        
        Color32 operator+(const Color32 &other) const;
        
        Color32 operator-(const Color32 &other) const;
        
        Color32 operator*(const Color32 &other) const;
        
        Color32 operator*(uint8 scalar) const;
        
        void operator+=(const Color32 &other);
        
        void operator-=(const Color32 &other);
        
        void operator*=(const Color32 &other);
        
        void operator*=(uint8 scalar);
    
    public:
        Color ToRGBA()const;
        
    };
}




