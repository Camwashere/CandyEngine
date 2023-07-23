#pragma once
#include "../ShaderData.hpp"
#include <candy/utils/IDManager.hpp>
namespace Candy::Graphics
{
  class ShaderParseObject
  {
  private:
    static Utils::IDManager<uint32_t> idManager;
  private:
    const uint32_t id;
    
  public:
    ShaderParseObject();
    ShaderParseObject(const ShaderParseObject& other);
    
    [[nodiscard]] bool IsValid()const;
    [[nodiscard]] uint32_t GetID()const;
  };
  
  struct ShaderMetaData : public ShaderParseObject
  {
  
    ShaderData::Stage stage;
    uint32_t version;
    std::vector<std::string> includes{};
    std::vector<std::string> defines{};
    
    explicit ShaderMetaData(ShaderData::Stage stage=ShaderData::Stage::None, uint32_t version=0) : ShaderParseObject(), stage(stage), version(version)
    {
    
    }
    
    [[nodiscard]] std::string ToString()const
    {
      std::string start = "Stage: " + ShaderData::StageToString(stage) + " Version: " + std::to_string(version) + '\n';
      for (const auto& include : includes)
      {
        start += "#include " + include + '\n';
      }
      for (const auto& define : defines)
      {
        start += "#define " + define + '\n';
      }
      return start;
    }
  };
  
  struct ShaderVariable : public ShaderParseObject
  {
    ShaderData::Type type=ShaderData::Type::None;
    std::string name={};
    ShaderVariable()=default;
    ShaderVariable(ShaderData::Type varType, std::string varName) : ShaderParseObject(), type(varType), name(std::move(varName))
    {
    
    }
    ShaderVariable(const ShaderVariable& other) = default;
    
    [[nodiscard]] std::string ToString() const
    {
      return "Name: " + name + " Type: " + ShaderData::TypeToString(type);
    }
  };
  
  struct ShaderBlock : public ShaderParseObject
  {
    std::string blockName={};
    std::string objectName={};
    int binding=-1;
    std::vector<ShaderVariable> variables{};
    
    ShaderBlock() = default;
    
    [[nodiscard]] std::string ToString()const
    {
      std::string start = "Block Name: " + blockName + " Object Name: " + objectName + " Binding: " + std::to_string(binding);
      for (const auto& var : variables)
      {
        start += '\n' + var.ToString();
      }
      return start;
    }
  };
  
  struct ShaderUniformSingle : public ShaderParseObject
  {
    std::string name{};
    ShaderData::Type type=ShaderData::Type::None;
    int binding=0;
    
    ShaderUniformSingle()=default;
    
    
    
    [[nodiscard]] std::string ToString()const
    {
      return "Name: " + name + " Type: " + ShaderData::TypeToString(type) + " Binding: " + std::to_string(binding);
    }
  };
  
  struct ShaderIOVariable : public ShaderParseObject
  {
    ShaderVariable variable{};
    int location=-1;
    bool isInput=false;
    ShaderIOVariable()=default;
    ShaderIOVariable(const ShaderVariable& var, int loc, bool input) : ShaderParseObject(), variable(var), location(loc), isInput(input)
    {
    
    }
    [[nodiscard]] bool IsInput()const{return isInput;}
    [[nodiscard]] bool IsOutput()const{return !isInput;}
    [[nodiscard]] std::string SpecifierString()const{return isInput ? "in" : "out";}
    
    [[nodiscard]] std::string ToString()const
    {
      return "Location: " + std::to_string(location) + " " + SpecifierString() + " " + variable.ToString();
    }
    
  };
  
  struct ShaderStruct : public ShaderParseObject
  {
    std::string name{};
    std::vector<ShaderVariable> variables{};
    
    ShaderStruct()=default;
    
    [[nodiscard]] std::string ToString()const
    {
      std::string start = "Struct Name: " + name;
      for (const auto& var : variables)
      {
        start += '\n' + var.ToString();
      }
      return start;
    }
  };
  
  struct ShaderFunction : public ShaderParseObject
  {
    ShaderData::Type returnType=ShaderData::Type::None;
    std::string name{};
    std::vector<ShaderVariable> parameters{};
    
    ShaderFunction()=default;
    
    
    [[nodiscard]] bool IsMain()const{return name == "main";}
    [[nodiscard]] size_t ParameterCount()const{return parameters.size();}
    
    [[nodiscard]] std::string ToString()const
    {
      std::string start = "Function Name: " + name + " Return Type: " + ShaderData::TypeToString(returnType);
      for (const auto& param : parameters)
      {
        start += '\n' + param.ToString();
      }
      return start;
    }
  };
}