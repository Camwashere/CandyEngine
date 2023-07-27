#pragma once
#include "CandyPch.hpp"
#include <unordered_map>
#include <string>
#include <filesystem>
#include "ShaderSource.hpp"


namespace Candy::Graphics
{
  
  class ShaderPreProcessor
  {
  
  private:
    std::unordered_map<ShaderData::Stage, SharedPtr<ShaderSource>> sources{};
    
    
  private:
    static std::string ReadFile(const std::filesystem::path& path);
    static std::string ConsolidateFiles(std::initializer_list<std::filesystem::path> paths);
    static std::unordered_map<ShaderData::Stage, std::string> PrepareSources(const std::string& source);
    
  private:
    void InitializeSources(const std::string& sourceCode);
  public:
    explicit ShaderPreProcessor(const std::filesystem::path& path);
    ShaderPreProcessor(std::initializer_list<std::filesystem::path> paths);
    
  public:
    ShaderSource& GetSource(ShaderData::Stage stage);
    std::unordered_map<ShaderData::Stage, std::string> GetSourceStrings();
    
  public:
    static UniquePtr<ShaderPreProcessor> Create(const std::filesystem::path& path);
    static UniquePtr<ShaderPreProcessor> Create(std::initializer_list<std::filesystem::path> paths);
  };
}