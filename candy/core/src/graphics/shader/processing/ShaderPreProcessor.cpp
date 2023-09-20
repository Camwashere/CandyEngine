#include <candy/graphics/shader/processing/ShaderPreProcessor.hpp>
#include <fstream>
#include <cstring>
#include <iostream>


namespace Candy::Graphics
{
  
  ShaderPreProcessor::ShaderPreProcessor(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    std::string sourceCode = ReadFile(path);
    InitializeSources(sourceCode);
    
    
  }
  
  ShaderPreProcessor::ShaderPreProcessor(std::initializer_list<std::filesystem::path> paths)
  {
    std::string sourceCode = ConsolidateFiles(paths);
    InitializeSources(sourceCode);
  }
  void ShaderPreProcessor::InitializeSources(const std::string& sourceCode)
  {
    std::unordered_map<ShaderData::Stage, std::string> shaderSources = PrepareSources(sourceCode);
    for(const auto& [stage, source] : shaderSources)
    {
      sources.insert({stage, ShaderSource::Create(stage, source)});
    }
  }
  
  
  std::unordered_map<ShaderData::Stage, std::string> ShaderPreProcessor::PrepareSources(const std::string& source)
  {
    std::unordered_map<ShaderData::Stage, std::string> shaderSources;
    
    const char* typeToken = "#stage";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
    while (pos != std::string::npos)
    {
      size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
      CANDY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
      
      
      size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
      std::string type = source.substr(begin, eol - begin);
      CANDY_CORE_ASSERT(ShaderData::StringToStage(type) != ShaderData::Stage::None, "Invalid shader type specified");
     
      
      size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
      CANDY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
      pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
      
      shaderSources[ShaderData::StringToStage(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }
    
    return shaderSources;
    
    
  }
  
  std::string ShaderPreProcessor::ConsolidateFiles(std::initializer_list<std::filesystem::path> paths)
  {
    
    std::string result;
    for (auto& path : paths)
    {
      result += '\n' + ReadFile(path);
    }
    return result;
  }
  std::string ShaderPreProcessor::ReadFile(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
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
        CANDY_CORE_ERROR("Could not read from file: '{}'", path.string());
       
      }
    }
    else
    {
      CANDY_CORE_ERROR("Could not open file '{}'", path.string());
    }
    
    return result;
  }
  
  ShaderSource& ShaderPreProcessor::GetSource(ShaderData::Stage stage)
  {
    return *sources[stage];
  }
  std::unordered_map<ShaderData::Stage, std::string> ShaderPreProcessor::GetSourceStrings()
  {
    std::unordered_map<ShaderData::Stage, std::string> result;
    for(const auto& [stage, source] : sources)
    {
      result.insert({stage, source->GetSource()});
    }
    return result;
  }
  UniquePtr<ShaderPreProcessor> ShaderPreProcessor::Create(const std::filesystem::path& path)
  {
    return CreateUniquePtr<ShaderPreProcessor>(path);
  }
  UniquePtr<ShaderPreProcessor> ShaderPreProcessor::Create(std::initializer_list<std::filesystem::path> paths)
  {
    return CreateUniquePtr<ShaderPreProcessor>(paths);
  }
}