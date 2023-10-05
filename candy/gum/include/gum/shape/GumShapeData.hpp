#pragma once
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
#include <gum/GumTypes.hpp>
#include <candy/collections/DualMap.hpp>
namespace Candy::Gum
{
  struct ShapeVertex
  {
    Math::Vector2 position;
    Math::Vector2 uv;
  };
  
  struct GumShapeDataInternal
  {
    std::vector<ShapeVertex> vertices;
    std::vector<uint16_t> indices;
  };
  
  
  
  
  
  class GumShapeDataRegistry
  {
  public:
    static GumID RegisterShapeData(const GumShapeDataInternal& shapeData);
    static GumID RegisterShapeData(const std::string& name, const GumShapeDataInternal& shapeData);
    static GumID GetShapeDataID(const std::string& name);
    static std::string GetShapeName(GumID shapeDataID);
    static const GumShapeDataInternal& GetShapeData(GumID shapeDataID);
    static const GumShapeDataInternal& GetShapeData(const std::string& name);
  };
}