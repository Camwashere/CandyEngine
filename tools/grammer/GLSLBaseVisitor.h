
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "GLSLVisitor.h"


/**
 * This class provides an empty implementation of GLSLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GLSLBaseVisitor : public GLSLVisitor {
public:

  virtual std::any visitStartShader(GLSLParser::StartShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPreprocessor_directive(GLSLParser::Preprocessor_directiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPush_constant_block(GLSLParser::Push_constant_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_uniform_block(GLSLParser::Shader_uniform_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_uniform_single(GLSLParser::Shader_uniform_singleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_io_variable(GLSLParser::Shader_io_variableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_struct_declaration(GLSLParser::Shader_struct_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_io_specifiers(GLSLParser::Shader_io_specifiersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct_type_name(GLSLParser::Struct_type_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShader_uniform_object(GLSLParser::Shader_uniform_objectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPush_constant_object(GLSLParser::Push_constant_objectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirective_name(GLSLParser::Directive_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirective_value(GLSLParser::Directive_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_declaration(GLSLParser::Function_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_name(GLSLParser::Function_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_return_type(GLSLParser::Function_return_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_parameters(GLSLParser::Function_parametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_parameter(GLSLParser::Function_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_body(GLSLParser::Function_bodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_declaration(GLSLParser::Layout_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_qualifiers(GLSLParser::Layout_qualifiersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_qualifier(GLSLParser::Layout_qualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_specifier(GLSLParser::Array_specifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_type(GLSLParser::Variable_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimitive_type(GLSLParser::Primitive_typeContext *ctx) override {
    return visitChildren(ctx);
  }


};

