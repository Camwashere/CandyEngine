#include <candy/graphics/shader/processing/ShaderProcessor.hpp>
#include <fstream>
#include <cstring>
#include <iostream>

#define CANDY_CORE_ASSERT(...)
namespace Candy::Graphics
{
  
  ShaderProcessor::ShaderProcessor(const std::filesystem::path& path)
  {
    std::string sourceCode = ReadFile(path);
    //std::cout << sourceCode << std::endl;
    InitializeSources(sourceCode);
    
    
  }
  
  ShaderProcessor::ShaderProcessor(std::initializer_list<std::filesystem::path> paths)
  {
    std::string sourceCode = ConsolidateFiles(paths);
    InitializeSources(sourceCode);
  }
  void ShaderProcessor::InitializeSources(const std::string& sourceCode)
  {
    std::unordered_map<ShaderData::Stage, std::string> shaderSources = PrepareSources(sourceCode);
    for(const auto& [stage, source] : shaderSources)
    {
      //std::cout << source << std::endl;
      sources.insert({stage, std::make_shared<ShaderSource>(stage, source)});
    }
  }
  
  
  std::unordered_map<ShaderData::Stage, std::string> ShaderProcessor::PrepareSources(const std::string& source)
  {
    std::unordered_map<ShaderData::Stage, std::string> shaderSources;
    
    const char* typeToken = "#stage";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
    while (pos != std::string::npos)
    {
      size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
      if (eol == std::string::npos)
      {
        throw std::runtime_error("Syntax error");
      }
      
      size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
      std::string type = source.substr(begin, eol - begin);
      if (ShaderData::StringToStage(type) == ShaderData::Stage::None)
      {
        throw std::runtime_error("Invalid shader type specified");
      }
     
      
      size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
      if (nextLinePos == std::string::npos)
      {
        throw std::runtime_error("Syntax error");
      }
      pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
      
      shaderSources[ShaderData::StringToStage(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }
    
    return shaderSources;
    
    
  }
  
  std::string ShaderProcessor::ConsolidateFiles(std::initializer_list<std::filesystem::path> paths)
  {
    std::string result;
    for (auto& path : paths)
    {
      result += '\n' + ReadFile(path);
    }
    return result;
  }
  std::string ShaderProcessor::ReadFile(const std::filesystem::path& path)
  {
    std::string result;
    std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
    if (in)
    {
      in.seekg(0, std::ios::end);
      auto size = in.tellg();
      if (size != -1)
      {
        result.resize(size);
        in.seekg(0, std::ios::beg);
        in.read(&result[0], size);
      }
      else
      {
        throw std::runtime_error("Could not read from file '" + path.string() + "'");
       
      }
    }
    else
    {
      throw std::runtime_error("Could not open file '" + path.string() + "'");
    }
    
    return result;
  }
  
  std::shared_ptr<ShaderSource> ShaderProcessor::GetSource(ShaderData::Stage stage)
  {
    return sources[stage];
  }
}