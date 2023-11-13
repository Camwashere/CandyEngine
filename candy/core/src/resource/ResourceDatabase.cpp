#include <candy/resource/ResourceDatabase.hpp>
#include <fstream>
#include <CandyPch.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>

#include <c4/format.hpp>
namespace Candy
{
  ResourceDatabase::ResourceDatabase(const std::filesystem::path& rootDirectory)
  {
    databaseFilePath = rootDirectory / "rdb.yml";
    
    
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