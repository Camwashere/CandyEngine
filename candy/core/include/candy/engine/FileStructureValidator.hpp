#pragma once
#include <vector>
#include <string>
#include <filesystem>
namespace Candy::FileSystem
{
  
  
  struct DirectoryValidationNode
  {
  private:
    std::filesystem::path path;
    
  public:
    bool optional;
    bool allowEmptyChildren;
    std::string name;
    std::vector<std::string> childNames;
    
    
    
    
    
  };
  
}