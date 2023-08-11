#pragma once
#include <cstdint>
#include <vector>
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
#include <unordered_map>
#include <filesystem>
namespace Candy::Gum
{
  struct GumShapeData
  {
    std::string name;
    std::vector<Math::Vector2> vertices;
    std::vector<Math::Vector2> uvs;
    std::vector<uint32_t> indices;
    
  };
  class GumShape
  {
  private:
    uint32_t id;
    
  private:
    static std::vector<GumShapeData> shapeData;
    static std::unordered_map<std::string, uint32_t> shapeNameMap;
    
  private:
    static void InitDefaultShapes();
    static void LoadShapes(const std::filesystem::path& shapePath);
  
  public:
    static const GumShape None;
    static const GumShape Rectangle;
    static const GumShape Triangle;
    
  
  public:
    GumShape();
    GumShape(uint32_t shapeID);
    explicit GumShape(const std::string& name);
    ~GumShape()=default;
    
  public:
    operator uint32_t()const;
    [[nodiscard]] std::string GetName()const;
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] const GumShapeData& GetData()const;
    
    
  public:
    static void Init(const std::filesystem::path& shapePath = std::filesystem::path());
    static uint32_t RegisterShape(const GumShapeData& shapeData);
    static GumShapeData GetShapeData(const std::string& name);
    static GumShapeData GetShapeData(uint32_t id);
    static GumShape GetShape(const std::string& name);
  };
}