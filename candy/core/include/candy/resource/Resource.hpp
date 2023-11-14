#pragma once
#include "ResourceType.hpp"
#include <string>
#include <vector>
#include <unordered_map>
namespace Candy
{
  class Resource
  {
  private:
    const uint32_t id;
    uint32_t refCount;
  
  private:
    static std::vector<std::string> resourceTypeStrings;
    static std::unordered_map<std::string, ResourceType> extensionAssociations;
  public:
    static const std::string& TypeToString(ResourceType type);
    static ResourceType TypeFromExtension(const std::string& extension);
  };
}