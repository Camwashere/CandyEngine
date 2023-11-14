#include <candy/resource/ResourceDatabase.hpp>
#include <fstream>
#include <candy/resource/Resource.hpp>
#include <CandyPch.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>


namespace Candy
{
  ResourceDatabase::ResourceDatabase(const std::filesystem::path& rootDirectory)
  {
    databaseFilePath = rootDirectory / "rdb.yml";
    
    
  }
  
  void ResourceDatabase::Build(const std::unordered_map<ResourceType, std::vector<uint32_t>>& resourceMap, const std::unordered_map<uint32_t, InternalResource>& resources)
  {
    
    CANDY_PROFILE_FUNCTION();
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    
    root |= c4::yml::MAP;
    c4::yml::NodeRef resourceTypesNode = root["resourceTypes"];
    resourceTypesNode |= c4::yml::MAP;
    for (const auto& resourceTypes : resourceMap)
    {
      c4::yml::NodeRef typeNode = resourceTypesNode[Resource::TypeToString(resourceTypes.first).c_str()];
      typeNode |= c4::yml::SEQ;
      for (uint32_t id : resourceTypes.second)
      {
        const InternalResource& internalResource = resources.at(id);
        c4::yml::NodeRef resourceNode = typeNode.append_child();
        resourceNode |= c4::yml::MAP;
        resourceNode["id"] << id;
        resourceNode["path"] << internalResource.GetPath().string();
        
      }
    }
    FILE* out = fopen(databaseFilePath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", databaseFilePath.string());
    }
    c4::yml::emit_yaml(tree, out);
  }
  
  bool ResourceDatabase::CreateFile(bool replaceExisting)
  {
    if (!replaceExisting && std::filesystem::exists(databaseFilePath)) {
      return false;
    }
    
    // Create the file
    std::ofstream file(databaseFilePath);
    
    // Check if it was created successfully
    if (!file) {
      return false;
    }
    
    file.close();
    return true;
  }
  bool ResourceDatabase::ValidFile()const
  {
    return std::filesystem::exists(databaseFilePath);
  }
  bool ResourceDatabase::ValidateResource(const InternalResource& resource)
  {
    return false;
  }
  bool ResourceDatabase::RemoveResource(uint32_t id)
  {
    return false;
  }
  bool ResourceDatabase::AddResource(const InternalResource& resource)
  {
    return false;
  }
  bool ResourceDatabase::AddOrReplaceResource(const InternalResource& resource)
  {
    return false;
  }
  bool ResourceDatabase::UpdateResource(const InternalResource& resource)
  {
    return false;
  }
}