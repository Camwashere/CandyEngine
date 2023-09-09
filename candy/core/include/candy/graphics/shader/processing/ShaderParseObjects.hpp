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
  
  struct ShaderInjectionConstant
  {
    ShaderData::Stage stage;
    ShaderData::Type type;
    std::string name;
    std::string value;
  };
  
  /*struct ShaderVariable : public ShaderParseObject
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
  struct LayoutQualifier
  {
    std::string name{};
    std::string value{};
    
    [[nodiscard]] bool HasValue()const{return !value.empty();}
  };
  struct ShaderObjectLayout
  {
    std::string attribute={};
    int location=-1;
    int binding=-1;
    int set=-1;
    [[nodiscard]] bool HasAttribute()const;
    [[nodiscard]] bool HasLocation()const;
    [[nodiscard]] bool HasBinding()const;
    [[nodiscard]] bool HasSet()const;
    ShaderObjectLayout()=default;
    explicit ShaderObjectLayout(const std::vector<LayoutQualifier>& layoutQualifiers);
    
    [[nodiscard]] std::string ToString()const;
  };
  struct ShaderBlockObject : public ShaderParseObject
  {
    std::string blockName={};
    std::string objectName={};
    ShaderObjectLayout layout={};
    std::vector<ShaderVariable> variables{};
    
    ShaderBlockObject() = default;
    
    [[nodiscard]] std::string ToString()const
    {
      std::string start = "Block Name: " + blockName + " Object Name: " + objectName + layout.ToString();
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
    ShaderObjectLayout layout={};
    
    ShaderUniformSingle()=default;
    
    
    
    [[nodiscard]] std::string ToString()const
    {
      return "Name: " + name + " Type: " + ShaderData::TypeToString(type) + layout.ToString();
    }
  };
  
  struct ShaderIOVariable : public ShaderParseObject
  {
    ShaderVariable variable{};
    ShaderObjectLayout layout={};
    bool isInput=false;
    ShaderIOVariable()=default;
    ShaderIOVariable(const ShaderVariable& var, int loc, bool input) : ShaderParseObject(), variable(var), isInput(input)
    {
      layout.location = loc;
      
    }
    [[nodiscard]] bool IsInput()const{return isInput;}
    [[nodiscard]] bool IsOutput()const{return !isInput;}
    [[nodiscard]] std::string SpecifierString()const{return isInput ? "in" : "out";}
    
    [[nodiscard]] std::string ToString()const
    {
      return layout.ToString() + " " + SpecifierString() + " " + variable.ToString();
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
  };*/
}