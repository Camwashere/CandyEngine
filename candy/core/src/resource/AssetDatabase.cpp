#include <candy/resource/AssetDatabase.hpp>
#include <fstream>
#include "candy/resource/Asset.hpp"
#include <CandyPch.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>


namespace Candy
{
  AssetDatabase::AssetDatabase(const std::filesystem::path& rootDirectory)
  {
    databaseFilePath = rootDirectory / "rdb.yml";
    
    
  }
  
  void AssetDatabase::Build(const std::unordered_map<AssetType, std::vector<uint32_t>>& assetMap, const std::unordered_map<uint32_t, Asset>& assets)
  {
    
    CANDY_PROFILE_FUNCTION();
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    
    root |= c4::yml::MAP;
    c4::yml::NodeRef assetTypesNode = root["AssetTypes"];
    assetTypesNode |= c4::yml::MAP;
    for (const auto& assetTypes : assetMap)
    {
      c4::yml::NodeRef typeNode = assetTypesNode[Asset::TypeToString(assetTypes.first).c_str()];
      typeNode |= c4::yml::SEQ;
      for (uint32_t id : assetTypes.second)
      {
        const Asset& internalAsset = assets.at(id);
        c4::yml::NodeRef assetNode = typeNode.append_child();
        assetNode |= c4::yml::MAP;
        assetNode["id"] << id;
        assetNode["path"] << internalAsset.GetPath().string();
        
      }
    }
    FILE* out = fopen(databaseFilePath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", databaseFilePath.string());
    }
    c4::yml::emit_yaml(tree, out);
  }
  
  bool AssetDatabase::CreateFile(bool replaceExisting)
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
  bool AssetDatabase::ValidFile()const
  {
    return std::filesystem::exists(databaseFilePath);
  }
 
}