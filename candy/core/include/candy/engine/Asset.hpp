#pragma once
#include <cstdint>
#include <filesystem>
namespace Candy
{
  struct AssetData
  {
    std::filesystem::path path;
    std::string name;
    
  };
  class Asset
  {
  private:
    uint32_t id;
    
  public:
    [[nodiscard]] uint32_t GetID()const{return id;}
  };
}