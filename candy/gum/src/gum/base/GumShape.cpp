#include <gum/base/GumShape.hpp>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  using namespace Math;
  std::vector<GumShapeData> GumShape::shapeData;
  std::unordered_map<std::string, uint32_t> GumShape::shapeNameMap;
  const GumShape GumShape::None=0;
  const GumShape GumShape::Rectangle=1;
  const GumShape GumShape::Triangle=2;
  
  // Rectangle geometry
  static const Vector2 rectanglePositions[4] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, -1.0f}, {0.0f, -1.0f}};
  static const Vector2 rectangleUVs[4] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}};
  static const uint32_t rectangleIndices[6] = {0, 1, 2, 2, 3, 0};
  
  // Triangle geometry
  static const Vector2 trianglePositions[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.5f, 0.5f}};
  static const Vector2 triangleUVs[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.5f, 1.0f}};
  static const uint32_t triangleIndices[3] = {0, 1, 2};
  
  void GumShape::InitDefaultShapes()
  {
    GumShapeData data;
    data.name = "None";
    RegisterShape(data);
    InitRectangleData();
    InitTriangleData();
  }
  
  void GumShape::InitRectangleData()
  {
    GumShapeData data;
    data.name = "Rectangle";
    
    for (int i=0; i<4; i++)
    {
      GumShapeVertex vertex;
      vertex.position = rectanglePositions[i];
      vertex.uv = rectangleUVs[i];
      data.vertices.push_back(vertex);
    }
    data.indices.resize(6);
    for (int i=0; i<6; i++)
    {
      data.indices[i] = rectangleIndices[i];
    }
    RegisterShape(data);
  }
  void GumShape::InitTriangleData()
  {
    GumShapeData data;
    data.name = "Triangle";
    for (int i=0; i<3; i++)
    {
      GumShapeVertex vertex;
      vertex.position = trianglePositions[i];
      vertex.uv = triangleUVs[i];
      data.vertices.push_back(vertex);
    }
    
    data.indices.resize(3);
    for (int i=0; i<3; i++)
    {
      data.indices[i] = triangleIndices[i];
    }
    RegisterShape(data);
  }
  
  void GumShape::Init(const std::filesystem::path& shapePath)
  {
    InitDefaultShapes();
    if (! shapePath.empty())
    {
      LoadShapes(shapePath);
    }
  }
  
  void GumShape::LoadShapes(const std::filesystem::path& shapePath)
  {
  
  }
  
  GumShape::GumShape() : id(0)
  {
  
  }
  GumShape::GumShape(uint32_t shapeType) : id(shapeType)
  {
  
  }
  GumShape::GumShape(const std::string& name)
  {
    id = GetShape(name);
  }
  GumShape::operator uint32_t()const
  {
    return id;
  }
  std::string GumShape::GetName()const
  {
    CANDY_CORE_ASSERT(id < shapeData.size(), "Error, Shape ID is out of range!");
    return shapeData[id].name;
  }
  
  uint32_t GumShape::GetID()const
  {
    return id;
  }
  const GumShapeData& GumShape::GetData()const
  {
    CANDY_CORE_ASSERT(id < shapeData.size(), "Error, Shape ID is out of range!");
    return shapeData[id];
  }
  uint32_t GumShape::RegisterShape(const GumShapeData& data)
  {
    auto it = shapeNameMap.find(data.name);
    if (it == shapeNameMap.end())
    {
      CANDY_CORE_ERROR("Error, Shape name: {} is already registered!", data.name);
      return false;
    }
    uint32_t id = shapeData.size();
    shapeNameMap[data.name] = id;
    shapeData.push_back(data);
    return id;
  }
  
  GumShapeData GumShape::GetShapeData(const std::string& name)
  {
    auto it = shapeNameMap.find(name);
    if (it != shapeNameMap.end())
    {
      return shapeData[shapeNameMap[name]];
    }
    else
    {
      CANDY_CORE_ERROR("Error, Shape name: {} is not registered!", name);
      CANDY_CORE_ASSERT(false);
      return {};
    }
  }
  GumShapeData GumShape::GetShapeData(uint32_t id)
  {
    CANDY_CORE_ASSERT(id < shapeData.size(), "Error, Shape ID is out of range!");
    return shapeData[id];
  }
  
  GumShape GumShape::GetShape(const std::string& name)
  {
    auto it = shapeNameMap.find(name);
    if (it != shapeNameMap.end())
    {
      return shapeNameMap[name];
    }
    else
    {
      CANDY_CORE_ERROR("Error, Shape name: {} is not registered!", name);
      CANDY_CORE_ASSERT(false);
      return 0;
    }
  }
}