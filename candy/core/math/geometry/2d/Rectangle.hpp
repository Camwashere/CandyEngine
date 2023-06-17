#pragma once
#include "../../linalg/vector/VectorAll.hpp"


namespace Candy::Shape
{

        struct Rectangle
        {
        public:
            Math::Vector2 min;
            Math::Vector2 max;
        
        
        public:
            constexpr Rectangle() : min(0, 0), max(0, 0){};
            constexpr Rectangle(const Math::Vector2& rectMin, const Math::Vector2& rectMax) : min(rectMin), max(rectMax) {}
            //constexpr Rectangle(const Math::Vector4& v) : min(v.x, v.y), max(v.x2, v.y2){}
            constexpr Rectangle(float x1, float y1, float x2, float y2)  : min(x1, y1), max(x2, y2){}
        
        
        
        public:
            bool operator==(const Rectangle& other) const;
            bool operator!=(const Rectangle& other) const;
            
            bool operator<(const Rectangle& other) const;
            bool operator<=(const Rectangle& other)const;
            bool operator>(const Rectangle& other) const;
            bool operator>=(const Rectangle& other) const;
        
        
        
        public:
            Math::Vector2 GetCenter() const;
            Math::Vector2 GetSize() const;
            float GetWidth() const;
            float GetHeight() const;
            float GetArea() const;
            
            Math::Vector2 GetTopLeft() const;
            Math::Vector2 GetTopRight() const;
            Math::Vector2 GetBottomLeft() const;
            Math::Vector2 GetBottomRight() const;
            bool Contains(const Math::Vector2& p) const;
            bool Contains(const Rectangle& r) const;
            bool Overlaps(const Rectangle& r) const;
            void Add(const Math::Vector2& p);
            void Add(const Rectangle& r);
            void Expand(const float amount);
            void Expand(const Math::Vector2& amount);
            void Translate(const Math::Vector2& d);
            void TranslateX(float dx);
            void TranslateY(float dy);
            void ClipWith(const Rectangle& r); // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
            void ClipWithFull(const Rectangle& r); // Full version, ensure both points are fully clipped.
            void Floor();
            bool IsInverted() const;
            Math::Vector4 ToVector4() const;
            Math::Vector2 NormalizePoint(const Math::Vector2& point)const;
            
            
            
            
            
        };
    
}