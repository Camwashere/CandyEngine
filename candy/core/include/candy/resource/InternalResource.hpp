#pragma once
#include <filesystem>
#include "ResourceType.hpp"
#include <vector>
namespace Candy
{
  class InternalResource
  {
  protected:
    const uint32_t id;
    const ResourceType type;
    std::filesystem::path path;
    
    
    
  public:
    explicit InternalResource(uint32_t id, ResourceType type, std::filesystem::path  path);
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] ResourceType GetType()const;
    [[nodiscard]] const std::filesystem::path& GetPath()const;
    
    
    
  };
}