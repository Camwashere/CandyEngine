#pragma once
#include "candy/graphics/Color.hpp"
#include "candy/math/Vector.hpp"
#include "candy/math/geometry/Bounds2D.hpp"
#include "candy/math/curve/BezierCurveQuadratic.hpp"
namespace Candy::Gum
{
  struct ShapeVertex
  {
    Math::Vector2 position;
    Math::Vector2 uv;
    Color color;
  };
  
  struct GumShapeData
  {
    std::vector<ShapeVertex> vertices;
    std::vector<uint16_t> indices;
  };
  
  class GumShapeBase
  {
  protected:
    Math::Bounds2D boundingBox;
    uint32_t shapeDataIndex=0;
    
    
  protected:
    virtual void CalculateBoundingBox()=0;
    [[nodiscard]] virtual bool ShapeContains(const Math::Vector2& point)const=0;
    
  public:
    [[nodiscard]] bool Contains(const Math::Vector2& point) const;
    [[nodiscard]] const Math::Bounds2D& GetBoundingBox() const;
  };
  
  class GumShape
  {
  private:
    std::vector<Math::Vector2> points;
    Math::Bounds2D boundingBox;
    
  private:
    void CalculateBoundingBox();
    
    
  public:
    GumShape()=default;
    
    void AddPoint(const Math::Vector2& point);
    void AddLine(const Math::Vector2& start, const Math::Vector2& end);
    void AddCurve(const Math::BezierCurveQuadratic& curve, float curvatureThreshold=0.1f, size_t minSubdivisions=2, size_t maxSubdivisions=20);
    
  public:
    [[nodiscard]] bool Contains(const Math::Vector2& point) const;
    
    [[nodiscard]] const std::vector<Math::Vector2>& GetPoints() const;
    [[nodiscard]] const Math::Bounds2D& GetBoundingBox() const;
    
    
    
  };
}