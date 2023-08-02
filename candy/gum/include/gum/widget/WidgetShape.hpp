#pragma once
#include <cstdint>
#include <vector>
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
namespace Candy::Gum
{
  struct WidgetShapeData
  {
    std::vector<Math::Vector2> vertices;
    std::vector<Math::Vector2> uvs;
    std::vector<uint32_t> indices;
  };
  class WidgetShape
  {
  private:
    uint32_t shapeType;
    
  public:
    static const WidgetShape Rectangle;
    static const WidgetShape Circle;
    static const WidgetShape Triangle;
    
  public:
    WidgetShape(uint32_t shapeType, const std::vector<Math::Vector2>& vertices, const std::vector<uint32_t>& indices);
    ~WidgetShape()=default;
    
    [[nodiscard]] uint32_t GetShapeType()const;
    [[nodiscard]] const std::vector<Math::Vector2>& GetVertices()const;
    [[nodiscard]] const std::vector<uint32_t>& GetIndices()const;
  };
}