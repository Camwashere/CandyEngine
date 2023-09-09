#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "../ShaderData.hpp"
#include "ShaderParseObjects.hpp"
#include "CandyPch.hpp"
namespace Candy::Graphics
{
  
  class ShaderSource
  {
  public:
    ShaderMetaData metaData{};
    std::vector<ShaderInjectionConstant> injectionConstants{};
    
    std::string source{};
    
  private:
    //void Tokenize(const std::string& source);
    
  public:
    ShaderSource(ShaderData::Stage shaderStage, std::string  sourceCode);
    
  public:
    //[[nodiscard]] ShaderData::Stage GetStage()const;
    //[[nodiscard]] uint32_t GetVersion()const;
    //[[nodiscard]] std::string ToString()const;
    [[nodiscard]] std::string GetSource()const;
    
  public:
    static SharedPtr<ShaderSource> Create(ShaderData::Stage shaderStage, std::string sourceCode);
    
 

    
    
    
  };
}