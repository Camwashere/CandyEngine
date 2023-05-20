#include "Rectangle.hpp"
#include "imgui_internal.h"
namespace Candy
{
    using namespace Math;
    namespace Shape
    {
        bool Rectangle::operator==(const Rectangle &other) const
        {
            return min == other.min && max == other.max;
        }
        
        bool Rectangle::operator!=(const Rectangle &other) const
        {
            return !((*this) == other);
        }
        
        bool Rectangle::operator<(const Rectangle &other) const
        {
            return min < other.min && max < other.max;
            
        }
        
        bool Rectangle::operator<=(const Rectangle &other) const
        {
            return min <= other.min && max <= other.max;
            
        }
        
        bool Rectangle::operator>(const Rectangle &other) const
        {
            return min > other.min && max > other.max;
            
        }
        
        bool Rectangle::operator>=(const Rectangle &other) const
        {
            return min >= other.min && max >= other.max;
            
        }
        
        
        Math::Vector2 Rectangle::GetCenter() const
        { return {(min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f}; }
        
        Math::Vector2 Rectangle::GetSize() const
        { return {max.x - min.x, max.y - min.y}; }
        
        float Rectangle::GetWidth() const
        { return max.x - min.x; }
        
        float Rectangle::GetHeight() const
        { return max.y - min.y; }
        
        float Rectangle::GetArea() const
        { return (max.x - min.x) * (max.y - min.y); }
        
        Math::Vector2 Rectangle::GetTopLeft() const
        { return min; }
        
        Math::Vector2 Rectangle::GetTopRight() const
        { return {max.x, min.y}; }
        
        Math::Vector2 Rectangle::GetBottomLeft() const
        { return {min.x, max.y}; }
        
        Math::Vector2 Rectangle::GetBottomRight() const
        { return max; }
        
        bool Rectangle::Contains(const Math::Vector2 &p) const
        { return p.x >= min.x && p.y >= min.y && p.x < max.x && p.y < max.y; }
        
        bool Rectangle::Contains(const Rectangle &r) const
        { return r.min.x >= min.x && r.min.y >= min.y && r.max.x <= max.x && r.max.y <= max.y; }
        
        bool Rectangle::Overlaps(const Rectangle &r) const
        { return r.min.y < max.y && r.max.y > min.y && r.min.x < max.x && r.max.x > min.x; }
        
        void Rectangle::Add(const Math::Vector2 &p)
        {
            if (min.x > p.x) min.x = p.x;
            if (min.y > p.y) min.y = p.y;
            if (max.x < p.x) max.x = p.x;
            if (max.y < p.y) max.y = p.y;
        }
        
        void Rectangle::Add(const Rectangle &r)
        {
            if (min.x > r.min.x) min.x = r.min.x;
            if (min.y > r.min.y) min.y = r.min.y;
            if (max.x < r.max.x) max.x = r.max.x;
            if (max.y < r.max.y) max.y = r.max.y;
        }
        
        void Rectangle::Expand(const float amount)
        {
            min.x -= amount;
            min.y -= amount;
            max.x += amount;
            max.y += amount;
        }
        
        void Rectangle::Expand(const Math::Vector2 &amount)
        {
            min.x -= amount.x;
            min.y -= amount.y;
            max.x += amount.x;
            max.y += amount.y;
        }
        
        void Rectangle::Translate(const Math::Vector2 &d)
        {
            min.x += d.x;
            min.y += d.y;
            max.x += d.x;
            max.y += d.y;
        }
        
        void Rectangle::TranslateX(float dx)
        {
            min.x += dx;
            max.x += dx;
        }
        
        void Rectangle::TranslateY(float dy)
        {
            min.y += dy;
            max.y += dy;
        }
        
        void Rectangle::ClipWith(const Rectangle &r)
        {
            min = Vector2::Max(min, r.min);
            max = Vector2::Min(max, r.max);
        } // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
        void Rectangle::ClipWithFull(const Rectangle &r)
        {
            min.Clamp(r.min, r.max);
            max.Clamp(r.min, r.max);
        } // Full version, ensure both points are fully clipped.
        void Rectangle::Floor()
        {
            min.x = Math::Floor(min.x);
            min.y = Math::Floor(min.y);
            max.x = Math::Floor(max.x);
            max.y = Math::Floor(max.y);
        }
        
        bool Rectangle::IsInverted() const
        { return min.x > max.x || min.y > max.y; }
        
        Math::Vector4 Rectangle::ToVector4() const
        { return {min.x, min.y, max.x, max.y}; }
        
        Math::Vector2 Rectangle::NormalizePoint(const Math::Vector2 &point) const
        { return (point - min) / (max - min); }
        
        Rectangle::operator ImRect() const
        { return {min.x, min.y, max.x, max.y}; }
        
    }
}

