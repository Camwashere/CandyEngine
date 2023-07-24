#include <candy/graphics/shader/processing/ShaderSource.hpp>
#include <iostream>
#include <utility>
#include <cctype>
#include "antlr4-runtime.h"
#include "grammer/GLSLLexer.h"
#include "grammer/GLSLParser.h"
#include "grammer/GLSLBaseListener.h"
namespace Candy::Graphics
{
  class SourceListener : public GLSLBaseListener
  {
  private:
    ShaderSource* source;
  
  private:
    static std::vector<LayoutQualifier> GetLayoutQualifiers(GLSLParser::Layout_qualifiersContext* ctx)
    {
      std::vector<LayoutQualifier> qualifiers{};
      if (! ctx)
      {
        return qualifiers;
      }
      for (auto qualifier : ctx->layout_qualifier())
      {
        LayoutQualifier layoutQualifier;
        layoutQualifier.name = qualifier->layout_qualifier_type()->getText();
        if (qualifier->layout_qualifier_value())
        {
          layoutQualifier.value = qualifier->layout_qualifier_value()->getText();
        }
        qualifiers.push_back(layoutQualifier);
      }
      return qualifiers;
    }
  
  public:
    explicit SourceListener(ShaderSource* source) : source(source)
    {
    
    }
  
  public:
    void enterPreprocessor_directive(GLSLParser::Preprocessor_directiveContext *ctx) override
    {
      std::string name = ctx->directive_name()->getText();
      if (name == "version")
      {
        std::string valueStr = ctx->directive_value()->getText();
        source->metaData.version = std::stoi(valueStr);
      }
      else if (name == "include")
      {
        std::string valueStr = ctx->directive_value()->getText();
        source->metaData.includes.push_back(valueStr);
        
      }
      else if (name == "define")
      {
        std::string valueStr = ctx->directive_value()->getText();
        source->metaData.defines.push_back(valueStr);
      }
    }
    void enterPush_constant_block(GLSLParser::Push_constant_blockContext *ctx) override
    {
      source->pushConstantBlock.blockName = ctx->IDENTIFIER()->getText();
      source->pushConstantBlock.objectName = ctx->push_constant_object()->getText();
      
      for (auto var : ctx->struct_variable_declaration())
      {
        ShaderData::Type dataType = ShaderData::StringToType(var->variable_type()->getText());
        std::string variableName = var->IDENTIFIER()->getText();
        ShaderVariable shaderVar = {dataType, variableName};
        
        source->pushConstantBlock.variables.push_back(shaderVar);
      }
      
    }
    
    void enterShader_struct_declaration(GLSLParser::Shader_struct_declarationContext * ctx) override
    {
      ShaderStruct shaderStruct{};
      
      shaderStruct.name = ctx->struct_type_name()->getText();
      auto vars = ctx->struct_variable_declaration();
      for (auto var : vars)
      {
        ShaderData::Type dataType = ShaderData::StringToType(var->variable_type()->getText());
        std::string variableName = var->IDENTIFIER()->getText();
        ShaderVariable shaderVar = {dataType, variableName};
        
        shaderStruct.variables.push_back(shaderVar);
      }
      
      source->structs.push_back(shaderStruct);
      
    }
    
    void enterShader_uniform_block(GLSLParser::Shader_uniform_blockContext * ctx) override
    {
      ShaderBlock uniformBlock{};
      
      uniformBlock.blockName = ctx->IDENTIFIER()->getText();
      if (ctx->shader_uniform_object())
      {
        uniformBlock.objectName = ctx->shader_uniform_object()->getText();
      }
      
      
      
      if (ctx->layout_declaration())
      {
        uniformBlock.layout = ShaderObjectLayout(GetLayoutQualifiers(ctx->layout_declaration()->layout_qualifiers()));
        std::vector<LayoutQualifier> qualifiers = GetLayoutQualifiers(ctx->layout_declaration()->layout_qualifiers());
      }
      
      for (auto var : ctx->struct_variable_declaration())
      {
        ShaderData::Type dataType = ShaderData::StringToType(var->variable_type()->getText());
        std::string variableName = var->IDENTIFIER()->getText();
        ShaderVariable shaderVar = {dataType, variableName};
        
        uniformBlock.variables.push_back(shaderVar);
      }
      
      source->uniformBlocks.push_back(uniformBlock);
    }
    
    void enterShader_uniform_single(GLSLParser::Shader_uniform_singleContext * ctx) override
    {
      ShaderUniformSingle uniformSingle;
      uniformSingle.type = ShaderData::StringToType(ctx->variable_type()->getText());
      uniformSingle.name = ctx->shader_uniform_object()->getText();
      
      if (ctx->layout_declaration())
      {
        uniformSingle.layout = ShaderObjectLayout(GetLayoutQualifiers(ctx->layout_declaration()->layout_qualifiers()));
        
      }
      
      
      source->uniformSingles.push_back(uniformSingle);
    }
    
    
    void enterShader_io_variable(GLSLParser::Shader_io_variableContext * ctx) override
    {
      ShaderIOVariable ioVar{};
      ioVar.isInput = ctx->shader_io_specifiers()->IN();
      
      
      if (ctx->layout_declaration())
      {
        ioVar.layout = ShaderObjectLayout(GetLayoutQualifiers(ctx->layout_declaration()->layout_qualifiers()));
      }
      std::string variableType = ctx->variable_type()->getText();
      std::string variableName = ctx->IDENTIFIER()->getText();
      ShaderData::Type dataType = ShaderData::StringToType(variableType);
      ioVar.variable.name = variableName;
      ioVar.variable.type = dataType;
      //std::cout << ioVar.ToString() << std::endl;
      if (ioVar.IsInput())
      {
        source->inputVariables.push_back(ioVar);
      }
      else
      {
        source->outputVariables.push_back(ioVar);
      }
      
    }
    
    void enterFunction_declaration(GLSLParser::Function_declarationContext * ctx) override
    {
      ShaderFunction function;
      function.name = ctx->function_name()->getText();
      function.returnType = ShaderData::StringToType(ctx->function_return_type()->getText());
      
      
      if (ctx->function_parameters())
      {
        
        for (auto param : ctx->function_parameters()->function_parameter())
        {
          std::string parameterType = param->variable_type()->getText();
          std::string parameterName = param->IDENTIFIER()->getText();
          ShaderData::Type dataType = ShaderData::StringToType(parameterType);
          ShaderVariable shaderVar = {dataType, parameterName};
          function.parameters.push_back(shaderVar);
        }
        
        
      }
      
      source->functions.push_back(function);
      
    }
    
  };
  ShaderSource::ShaderSource(ShaderData::Stage shaderStage, std::string sourceCode) : metaData{shaderStage}, source(std::move(sourceCode))
  {
    //std::cout << "Starting: " << ShaderData::StageToString(shaderStage) << std::endl;
    Tokenize(source);
    
  }
  
  void ShaderSource::Tokenize(const std::string& sourceCode)
  {
    
    std::string_view sourceView(sourceCode);
    
    antlr4::ANTLRInputStream input(sourceView);
    GLSLLexer lexer(&input);
    
    antlr4::CommonTokenStream tokens(&lexer);
    GLSLParser parser(&tokens);
    GLSLParser::StartShaderContext* tree = parser.startShader();
    antlr4::tree::ParseTreeWalker walker;
    SourceListener sourceListener(this);
    walker.walk(&sourceListener, tree);
    
    std::cout << "Tokenizing source!" << std::endl;
    
    std::cout << ToString() << std::endl;
    
    
    
  }
  ShaderData::Stage ShaderSource::GetStage()const
  {
    return metaData.stage;
  }
  uint32_t ShaderSource::GetVersion()const
  {
    return metaData.version;
  }
  std::string ShaderSource::ToString()const
  {
    
    std::string str =  metaData.ToString();
    str += "\nPush Constant Block: " + pushConstantBlock.ToString() + "\n";
    str += "\nUniform Singles\n";
    for (const auto& uniformSingle : uniformSingles)
    {
      str += uniformSingle.ToString() + "\n";
    }
    str += "\nUniform Blocks\n";
    for (const auto& uniformBlock : uniformBlocks)
    {
      str+= uniformBlock.ToString() + "\n";
    }
    str += "\nInput Variables\n";
    for (const auto& inputVar : inputVariables)
    {
      
      str += inputVar.ToString() + "\n";
    }
    str += "\nOutput Variables\n";
    for (const auto& outputVar : outputVariables)
    {
      str += outputVar.ToString() + "\n";
    }
    str += "\nFunctions\n";
    for (const auto& function : functions)
    {
      str += function.ToString() + "\n";
    }
    
    return str;
    
  }
  
  std::string ShaderSource::GetSource()const
  {
    return source;
  }
  
  
  
  
  SharedPtr<ShaderSource> ShaderSource::Create(ShaderData::Stage shaderStage, std::string sourceCode)
  {
    return CreateSharedPtr<ShaderSource>(shaderStage, std::move(sourceCode));
  }
  
  
  
  
  
  
  
}