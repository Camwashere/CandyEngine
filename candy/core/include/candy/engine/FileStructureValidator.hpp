#pragma once
#include <vector>
#include <string>
#include <filesystem>
namespace Candy::FileSystem
{
  
  
  struct DirectoryNode
  {
  private:
    std::filesystem::path path;
    
  public:
    bool optional;
    bool allowEmptyChildren;
    std::string name;
    DirectoryNode* parent = nullptr;
    std::vector<DirectoryNode> children;
    
  public:
    DirectoryNode(const std::filesystem::path& path);
    DirectoryNode(DirectoryNode& parent, const std::string& name);
    
  public:
  
  };
  
  struct DirectoryValidator
  {
  private:
    DirectoryNode root;
    
  public:
    DirectoryValidator(const std::filesystem::path& rootPath);
    
    
  };
  
  
  
}