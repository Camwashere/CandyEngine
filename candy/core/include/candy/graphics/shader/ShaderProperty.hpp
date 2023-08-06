#pragma once
#include "ShaderData.hpp"
#include <candy/graphics/BufferLayout.hpp>
namespace Candy::Graphics
{
  
  
  struct ShaderPushProperty
  {
    uint32_t id;
    uint32_t parentID;
    std::string name;
    //ShaderData::Stage stage;
    ShaderData::Type type;
    uint32_t offset;
    uint32_t size;
  };
  
  struct ShaderPushBlock
  {
    uint32_t id;
    uint32_t offset=0;
    std::string name;
    //ShaderData::Stage stage;
    uint32_t size=0;
    std::vector<ShaderPushProperty> properties;
  
  public:
    void AddPushProperty(const ShaderPushProperty& property);
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] uint32_t GetSize()const;
  };
  
  
  struct ShaderProperty
  {
    uint32_t id;
    uint32_t parentID;
    uint32_t offset;
    uint32_t parentOffset;
    uint32_t size;
    std::string name;
    ShaderData::Type type;
    
    uint32_t GlobalOffset()const;
    
  };
  
  class ShaderSet;
  
  struct ShaderBlock
  {
    uint32_t id=0;
    std::vector<ShaderProperty> properties;
    uint32_t offset;
    uint32_t size;
    std::string name;
    ShaderData::Stage stage;
    uint32_t binding;
    uint32_t set;
    
    void AddProperty(const ShaderProperty& property);
    [[nodiscard]] uint32_t GetID()const;
  };
  
  struct ShaderTexture
  {
    uint32_t id;
    std::string name;
    ShaderData::Type type;
    ShaderData::Stage stage;
    uint32_t set;
    uint32_t binding;
  };
  
  struct ShaderSet
  {
    uint32_t set=0;
    uint32_t size=0;
    std::vector<ShaderBlock> blocks{};
    std::vector<ShaderProperty*> properties{};
    std::vector<ShaderTexture> textures{};
    std::unordered_map<std::string, uint32_t> blockMap{};
    std::unordered_map<std::string, uint32_t> propertyMap{};
    
  public:
    explicit ShaderSet(uint32_t set=0);
    
    uint32_t AddBlock(const ShaderBlock& block);
    
    void AddProperty(const ShaderBlock& block, ShaderProperty* property);
    
    void AddTexture(ShaderTexture texture);
    
    ShaderBlock GetBlockFromProperty(uint32_t propertyID)const;
    ShaderProperty GetProperty(const std::string& name)const;
    ShaderProperty GetProperty(uint32_t id)const;
    ShaderBlock GetBlock(const std::string& name)const;
    ShaderBlock GetBlock(uint32_t id)const;
    [[nodiscard]] const std::vector<ShaderBlock>& GetBlocks()const;
    [[nodiscard]] uint32_t GetSet()const;

  };
  
  
  
  
  
}