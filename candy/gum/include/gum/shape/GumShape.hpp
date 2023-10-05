#pragma once
#include "GumShapeData.hpp"
#include "candy/math/geometry/Bounds2D.hpp"
#include "candy/math/curve/BezierCurveQuadratic.hpp"
namespace Candy::Gum
{
  enum class ShapeMutability
  {
    STATIC=0,
    DYNAMIC=1,
  };
  class GumShape
  {
  private:
    
    GumID dataRegistryID;
    ShapeMutability mutability=ShapeMutability::STATIC;
    
  protected:
    Math::Bounds2D boundingBox;
    
    
  protected:
    
    [[nodiscard]] virtual bool ShapeContains(const Math::Vector2& point)const=0;
    
    
    
  public:
    explicit GumShape(ShapeMutability shapeMutability);
    
    GumShape(const GumShape& other);
    virtual ~GumShape() = 0;
  
  public:
    virtual void ReCalculateBoundingBox();
    [[nodiscard]] const GumShapeDataInternal& GetInternalData() const;
    [[nodiscard]] bool Contains(const Math::Vector2& point) const;
    [[nodiscard]] bool BoundingBoxContains(const Math::Vector2& point)const;
    [[nodiscard]] const Math::Bounds2D& GetBoundingBox() const;
    [[nodiscard]] std::string GetName()const;
  };
  
  
}