#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "../ShaderData.hpp"
#include "ShaderParseObjects.hpp"
namespace Candy::Graphics
{
  
  class ShaderSource
  {
  public:
    ShaderMetaData metaData{};
    ShaderBlock pushConstantBlock{};
    std::vector<ShaderUniformSingle> uniformSingles{};
    std::vector<ShaderBlock> uniformBlocks{};
    std::vector<ShaderIOVariable> inputVariables{};
    std::vector<ShaderIOVariable> outputVariables{};
    std::vector<ShaderFunction> functions{};
    std::vector<ShaderStruct> structs{};
    
    std::string source{};
    
  private:
    void Tokenize(const std::string& source);
    
  public:
    ShaderSource(ShaderData::Stage shaderStage, std::string  sourceCode);
    
  public:
    [[nodiscard]] ShaderData::Stage GetStage()const;
    [[nodiscard]] uint32_t GetVersion()const;
    [[nodiscard]] std::string ToString()const;
    
 

    
    
    
  };
}