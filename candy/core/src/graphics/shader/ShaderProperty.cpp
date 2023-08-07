#include <candy/graphics/shader/ShaderProperty.hpp>

namespace Candy::Graphics
{
  void ShaderPushBlock::AddPushProperty(const ShaderPushProperty& property)
  {
    ShaderPushProperty p = property;
    p.id = properties.size();
    //p.offset = size;
    //p.stage = stage;
    size += p.size;
    properties.push_back(p);
  }
  
  uint32_t ShaderPushBlock::GetID()const
  {
    return id;
  }
  uint32_t ShaderPushBlock::GetSize()const
  {
    return size;
  }
  
  uint32_t ShaderProperty::GlobalOffset()const
  {
    return parentOffset + offset;
  }
  void ShaderBlock::AddProperty(const ShaderProperty& prop)
  {
    ShaderProperty p = prop;
    p.size = ShaderData::TypeSize(p.type);
    p.offset = size;
    size += p.size;
    properties.push_back(p);
  }
  
  
  uint32_t ShaderBlock::GetID()const
  {
    return id;
  }
  ShaderSet::ShaderSet(uint32_t val) : set(val)
  {
  
  }
  
  
  uint32_t ShaderSet::AddBlock(const ShaderBlock& block)
  {
    ShaderBlock b = block;
    b.id = blocks.size();
    b.offset = size;
    blocks.push_back(b);
    blockMap[b.name] = b.id;
    ShaderBlock& ref = blocks.back();
    for (auto& property : ref.properties)
    {
      AddProperty(ref, &property);
    }
    offsets.push_back(size);
    size+=b.size;
    return b.id;
  }
  void ShaderSet::AddProperty(const ShaderBlock& block, ShaderProperty* property)
  {
    property->id = properties.size();
    property->parentID = block.id;
    property->parentOffset = block.offset;
    properties.push_back(property);
    propertyMap[property->name] = property->id;
  
  }
  void ShaderSet::AddTexture(ShaderTexture texture)
  {
    ShaderTexture t = std::move(texture);
    t.id = textures.size();
    textures.push_back(t);
  }

  ShaderBlock ShaderSet::GetBlockFromProperty(uint32_t propertyID)const
  {
    CANDY_CORE_ASSERT(properties.size() > propertyID, "ShaderSet::GetBlockFromProperty: propertyID out of range");
    CANDY_CORE_ASSERT(properties[propertyID] != nullptr, "ShaderSet::GetBlockFromProperty: property is null");
    CANDY_CORE_ASSERT(properties[propertyID]->parentID < blocks.size(), "ShaderSet::GetBlockFromProperty: parentID out of range");
    return blocks[properties[propertyID]->parentID];
  }
  ShaderProperty ShaderSet::GetProperty(uint32_t id)const
  {
    CANDY_CORE_ASSERT(properties.size() > id, "ShaderSet::GetProperty: blockID out of range");
    CANDY_CORE_ASSERT(properties[id] != nullptr, "ShaderSet::GetProperty: property is null");
    return *properties[id];
  }
  ShaderProperty ShaderSet::GetProperty(const std::string& name)const
  {
    CANDY_CORE_ASSERT(propertyMap.find(name) != propertyMap.end(), "ShaderSet::GetProperty: property not found");
    return GetProperty(propertyMap.at(name));
  }
  ShaderBlock ShaderSet::GetBlock(const std::string& name)const
  {
    CANDY_CORE_ASSERT(blockMap.find(name) != blockMap.end(), "ShaderSet::GetBlock: block not found");
    return blocks[blockMap.at(name)];
  }
  ShaderBlock ShaderSet::GetBlock(uint32_t id)const
  {
    return blocks[id];
  }
  const std::vector<ShaderBlock>& ShaderSet::GetBlocks()const
  {
    return blocks;
  }
  
  uint32_t ShaderSet::GetSet()const
  {
    return set;
  }
  
  
  
}