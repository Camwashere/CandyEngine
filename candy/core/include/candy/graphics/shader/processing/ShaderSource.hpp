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
    /*ShaderBlockObject pushConstantBlock{};
    std::vector<ShaderUniformSingle> uniformSingles{};
    std::vector<ShaderBlockObject> uniformBlocks{};
    std::vector<ShaderIOVariable> inputVariables{};
    std::vector<ShaderIOVariable> outputVariables{};
    std::vector<ShaderFunction> functions{};
    std::vector<ShaderStruct> structs{};*/
    
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