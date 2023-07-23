#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include "ShaderSource.hpp"

namespace Candy::Graphics
{
  
  class ShaderProcessor
  {
  
  private:
    std::unordered_map<ShaderData::Stage, std::shared_ptr<ShaderSource>> sources{};
    
  private:
    static std::string ReadFile(const std::filesystem::path& path);
    static std::string ConsolidateFiles(std::initializer_list<std::filesystem::path> paths);
    static std::unordered_map<ShaderData::Stage, std::string> PrepareSources(const std::string& source);
    
  private:
    void InitializeSources(const std::string& sourceCode);
  public:
    explicit ShaderProcessor(const std::filesystem::path& path);
    ShaderProcessor(std::initializer_list<std::filesystem::path> paths);
    
  public:
    std::shared_ptr<ShaderSource> GetSource(ShaderData::Stage stage);
  };
}