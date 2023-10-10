#include <gum/shape/GumShapeData.hpp>

namespace Candy::Gum
{
  
  class GumShapeDataRegistryBase
  {
  
  protected:
    GumIDVector<GumShapeDataInternal> internalShapeData{};
    
  
  
  public:
    GumID RegisterShapeData(const GumShapeDataInternal& shapeData)
    {
      GumID id = internalShapeData.Size();
      internalShapeData.PushBack(shapeData);
      return id;
    }
    
    [[nodiscard]] const GumShapeDataInternal& GetShapeData(GumID shapeDataID) const
    {
      CANDY_CORE_ASSERT(shapeDataID<internalShapeData.Size(), "Invalid gum internal shape data id!");
      return internalShapeData[shapeDataID];
    }
    
  };
  
  
  
  class GumShapeDataRegistryStatic : public GumShapeDataRegistryBase
  {
  private:
    
    Collections::DualMap<std::string, GumID> nameToID;
  public:
    
    GumID RegisterShapeData(const std::string& name, const GumShapeDataInternal& shapeData)
    {
      if (nameToID.ContainsKey(name))
      {
        CANDY_CORE_ERROR(("Cannot register shape data with name: {}, name already exists!", name));
        return GumID::NULL_ID;
      }
      
      GumID id = internalShapeData.Size();
      internalShapeData.PushBack(shapeData);
      nameToID[name] = id;
      return id;
    }
    GumID GetShapeDataID(const std::string& name) const
    {
      auto it = nameToID.FindValue(name);
      if (it != nameToID.end())
      {
        return it->second;
      }
      CANDY_CORE_ERROR("Error, internal gum shape data with name: {} does not exist!", name);
      return GumID::NULL_ID;
    }
    std::string GetShapeName(GumID id)
    {
      auto it = nameToID.FindKey(id);
      if (it != nameToID.endValueToKey())
      {
        return it->second;
      }
      CANDY_CORE_ERROR("Error, internal gum shape data with id: {} does not exist! Cannot find shape name!", id);
      return "";
    }
    const GumShapeDataInternal& GetShapeData(const std::string& name) const
    {
      return GumShapeDataRegistryBase::GetShapeData(GetShapeDataID(name));
    }
  };
  
  struct RegistryData
  {
    GumShapeDataRegistryStatic staticRegistry;
    GumShapeDataRegistryBase dynamicRegistry;
  };
  
  static RegistryData data;
  GumID GumShapeDataRegistry::RegisterShapeData(const GumShapeDataInternal& shapeData)
  {
    return data.dynamicRegistry.RegisterShapeData(shapeData);
  }
 
  GumID GumShapeDataRegistry::RegisterShapeData(const std::string& name, const GumShapeDataInternal& shapeData)
  {
    return data.staticRegistry.RegisterShapeData(name, shapeData);
  }
  GumID GumShapeDataRegistry::GetShapeDataID(const std::string& name)
  {
    return data.staticRegistry.GetShapeDataID(name);
  }
  std::string GumShapeDataRegistry::GetShapeName(GumID shapeDataID)
  {
    return data.staticRegistry.GetShapeName(shapeDataID);
  }
  const GumShapeDataInternal& GumShapeDataRegistry::GetShapeData(GumID shapeDataID)
  {
    return data.dynamicRegistry.GetShapeData(shapeDataID);
  }
  const GumShapeDataInternal& GumShapeDataRegistry::GetShapeData(const std::string& name)
  {
    return data.staticRegistry.GetShapeData(name);
  }
}