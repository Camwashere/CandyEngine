
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "GLSLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by GLSLParser.
 */
class  GLSLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStartShader(GLSLParser::StartShaderContext *ctx) = 0;
  virtual void exitStartShader(GLSLParser::StartShaderContext *ctx) = 0;

  virtual void enterPreprocessor_directive(GLSLParser::Preprocessor_directiveContext *ctx) = 0;
  virtual void exitPreprocessor_directive(GLSLParser::Preprocessor_directiveContext *ctx) = 0;

  virtual void enterPush_constant_block(GLSLParser::Push_constant_blockContext *ctx) = 0;
  virtual void exitPush_constant_block(GLSLParser::Push_constant_blockContext *ctx) = 0;

  virtual void enterShader_uniform_block(GLSLParser::Shader_uniform_blockContext *ctx) = 0;
  virtual void exitShader_uniform_block(GLSLParser::Shader_uniform_blockContext *ctx) = 0;

  virtual void enterShader_uniform_single(GLSLParser::Shader_uniform_singleContext *ctx) = 0;
  virtual void exitShader_uniform_single(GLSLParser::Shader_uniform_singleContext *ctx) = 0;

  virtual void enterShader_io_variable(GLSLParser::Shader_io_variableContext *ctx) = 0;
  virtual void exitShader_io_variable(GLSLParser::Shader_io_variableContext *ctx) = 0;

  virtual void enterShader_struct_declaration(GLSLParser::Shader_struct_declarationContext *ctx) = 0;
  virtual void exitShader_struct_declaration(GLSLParser::Shader_struct_declarationContext *ctx) = 0;

  virtual void enterShader_io_specifiers(GLSLParser::Shader_io_specifiersContext *ctx) = 0;
  virtual void exitShader_io_specifiers(GLSLParser::Shader_io_specifiersContext *ctx) = 0;

  virtual void enterStruct_type_name(GLSLParser::Struct_type_nameContext *ctx) = 0;
  virtual void exitStruct_type_name(GLSLParser::Struct_type_nameContext *ctx) = 0;

  virtual void enterShader_uniform_object(GLSLParser::Shader_uniform_objectContext *ctx) = 0;
  virtual void exitShader_uniform_object(GLSLParser::Shader_uniform_objectContext *ctx) = 0;

  virtual void enterPush_constant_object(GLSLParser::Push_constant_objectContext *ctx) = 0;
  virtual void exitPush_constant_object(GLSLParser::Push_constant_objectContext *ctx) = 0;

  virtual void enterDirective_name(GLSLParser::Directive_nameContext *ctx) = 0;
  virtual void exitDirective_name(GLSLParser::Directive_nameContext *ctx) = 0;

  virtual void enterDirective_value(GLSLParser::Directive_valueContext *ctx) = 0;
  virtual void exitDirective_value(GLSLParser::Directive_valueContext *ctx) = 0;

  virtual void enterStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext *ctx) = 0;
  virtual void exitStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext *ctx) = 0;

  virtual void enterStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext *ctx) = 0;
  virtual void exitStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext *ctx) = 0;

  virtual void enterFunction_declaration(GLSLParser::Function_declarationContext *ctx) = 0;
  virtual void exitFunction_declaration(GLSLParser::Function_declarationContext *ctx) = 0;

  virtual void enterFunction_name(GLSLParser::Function_nameContext *ctx) = 0;
  virtual void exitFunction_name(GLSLParser::Function_nameContext *ctx) = 0;

  virtual void enterFunction_return_type(GLSLParser::Function_return_typeContext *ctx) = 0;
  virtual void exitFunction_return_type(GLSLParser::Function_return_typeContext *ctx) = 0;

  virtual void enterFunction_parameters(GLSLParser::Function_parametersContext *ctx) = 0;
  virtual void exitFunction_parameters(GLSLParser::Function_parametersContext *ctx) = 0;

  virtual void enterFunction_parameter(GLSLParser::Function_parameterContext *ctx) = 0;
  virtual void exitFunction_parameter(GLSLParser::Function_parameterContext *ctx) = 0;

  virtual void enterFunction_body(GLSLParser::Function_bodyContext *ctx) = 0;
  virtual void exitFunction_body(GLSLParser::Function_bodyContext *ctx) = 0;

  virtual void enterLayout_declaration(GLSLParser::Layout_declarationContext *ctx) = 0;
  virtual void exitLayout_declaration(GLSLParser::Layout_declarationContext *ctx) = 0;

  virtual void enterLayout_qualifiers(GLSLParser::Layout_qualifiersContext *ctx) = 0;
  virtual void exitLayout_qualifiers(GLSLParser::Layout_qualifiersContext *ctx) = 0;

  virtual void enterLayout_qualifier(GLSLParser::Layout_qualifierContext *ctx) = 0;
  virtual void exitLayout_qualifier(GLSLParser::Layout_qualifierContext *ctx) = 0;

  virtual void enterLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext *ctx) = 0;
  virtual void exitLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext *ctx) = 0;

  virtual void enterLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext *ctx) = 0;
  virtual void exitLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext *ctx) = 0;

  virtual void enterLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext *ctx) = 0;
  virtual void exitLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext *ctx) = 0;

  virtual void enterArray_specifier(GLSLParser::Array_specifierContext *ctx) = 0;
  virtual void exitArray_specifier(GLSLParser::Array_specifierContext *ctx) = 0;

  virtual void enterVariable_type(GLSLParser::Variable_typeContext *ctx) = 0;
  virtual void exitVariable_type(GLSLParser::Variable_typeContext *ctx) = 0;

  virtual void enterPrimitive_type(GLSLParser::Primitive_typeContext *ctx) = 0;
  virtual void exitPrimitive_type(GLSLParser::Primitive_typeContext *ctx) = 0;


};

