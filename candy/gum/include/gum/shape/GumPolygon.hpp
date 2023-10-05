#pragma once
#include "candy/graphics/Color.hpp"
#include "candy/math/Vector.hpp"
#include "candy/math/geometry/Bounds2D.hpp"
#include "candy/math/curve/BezierCurveQuadratic.hpp"
#include "GumShape.hpp"
namespace Candy::Gum
{
  
  class GumPolygon : public GumShape
  {
  private:
    std::vector<Math::Vector2> points;
    
    
  private:
    void CalculateBoundingBox();
    
  protected:
    [[nodiscard]] bool ShapeContains(const Math::Vector2& point) const override;
    
    
  public:
    explicit GumPolygon(ShapeMutability mutability);
    
    void AddPoint(const Math::Vector2& point);
    void AddLine(const Math::Vector2& start, const Math::Vector2& end);
    void AddCurve(const Math::BezierCurveQuadratic& curve, float curvatureThreshold=0.1f, size_t minSubdivisions=2, size_t maxSubdivisions=20);
    
  public:
    [[nodiscard]] const std::vector<Math::Vector2>& GetPoints() const;
    
    
    
  };
}