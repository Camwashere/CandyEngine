
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "GLSLListener.h"


/**
 * This class provides an empty implementation of GLSLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  GLSLBaseListener : public GLSLListener {
public:

  virtual void enterStartShader(GLSLParser::StartShaderContext * /*ctx*/) override { }
  virtual void exitStartShader(GLSLParser::StartShaderContext * /*ctx*/) override { }

  virtual void enterPreprocessor_directive(GLSLParser::Preprocessor_directiveContext * /*ctx*/) override { }
  virtual void exitPreprocessor_directive(GLSLParser::Preprocessor_directiveContext * /*ctx*/) override { }

  virtual void enterPush_constant_block(GLSLParser::Push_constant_blockContext * /*ctx*/) override { }
  virtual void exitPush_constant_block(GLSLParser::Push_constant_blockContext * /*ctx*/) override { }

  virtual void enterShader_uniform_block(GLSLParser::Shader_uniform_blockContext * /*ctx*/) override { }
  virtual void exitShader_uniform_block(GLSLParser::Shader_uniform_blockContext * /*ctx*/) override { }

  virtual void enterShader_uniform_single(GLSLParser::Shader_uniform_singleContext * /*ctx*/) override { }
  virtual void exitShader_uniform_single(GLSLParser::Shader_uniform_singleContext * /*ctx*/) override { }

  virtual void enterShader_io_variable(GLSLParser::Shader_io_variableContext * /*ctx*/) override { }
  virtual void exitShader_io_variable(GLSLParser::Shader_io_variableContext * /*ctx*/) override { }

  virtual void enterShader_struct_declaration(GLSLParser::Shader_struct_declarationContext * /*ctx*/) override { }
  virtual void exitShader_struct_declaration(GLSLParser::Shader_struct_declarationContext * /*ctx*/) override { }

  virtual void enterShader_io_specifiers(GLSLParser::Shader_io_specifiersContext * /*ctx*/) override { }
  virtual void exitShader_io_specifiers(GLSLParser::Shader_io_specifiersContext * /*ctx*/) override { }

  virtual void enterStruct_type_name(GLSLParser::Struct_type_nameContext * /*ctx*/) override { }
  virtual void exitStruct_type_name(GLSLParser::Struct_type_nameContext * /*ctx*/) override { }

  virtual void enterShader_uniform_object(GLSLParser::Shader_uniform_objectContext * /*ctx*/) override { }
  virtual void exitShader_uniform_object(GLSLParser::Shader_uniform_objectContext * /*ctx*/) override { }

  virtual void enterPush_constant_object(GLSLParser::Push_constant_objectContext * /*ctx*/) override { }
  virtual void exitPush_constant_object(GLSLParser::Push_constant_objectContext * /*ctx*/) override { }

  virtual void enterDirective_name(GLSLParser::Directive_nameContext * /*ctx*/) override { }
  virtual void exitDirective_name(GLSLParser::Directive_nameContext * /*ctx*/) override { }

  virtual void enterDirective_value(GLSLParser::Directive_valueContext * /*ctx*/) override { }
  virtual void exitDirective_value(GLSLParser::Directive_valueContext * /*ctx*/) override { }

  virtual void enterStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext * /*ctx*/) override { }
  virtual void exitStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext * /*ctx*/) override { }

  virtual void enterStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext * /*ctx*/) override { }
  virtual void exitStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext * /*ctx*/) override { }

  virtual void enterFunction_declaration(GLSLParser::Function_declarationContext * /*ctx*/) override { }
  virtual void exitFunction_declaration(GLSLParser::Function_declarationContext * /*ctx*/) override { }

  virtual void enterFunction_name(GLSLParser::Function_nameContext * /*ctx*/) override { }
  virtual void exitFunction_name(GLSLParser::Function_nameContext * /*ctx*/) override { }

  virtual void enterFunction_return_type(GLSLParser::Function_return_typeContext * /*ctx*/) override { }
  virtual void exitFunction_return_type(GLSLParser::Function_return_typeContext * /*ctx*/) override { }

  virtual void enterFunction_parameters(GLSLParser::Function_parametersContext * /*ctx*/) override { }
  virtual void exitFunction_parameters(GLSLParser::Function_parametersContext * /*ctx*/) override { }

  virtual void enterFunction_parameter(GLSLParser::Function_parameterContext * /*ctx*/) override { }
  virtual void exitFunction_parameter(GLSLParser::Function_parameterContext * /*ctx*/) override { }

  virtual void enterFunction_body(GLSLParser::Function_bodyContext * /*ctx*/) override { }
  virtual void exitFunction_body(GLSLParser::Function_bodyContext * /*ctx*/) override { }

  virtual void enterLayout_declaration(GLSLParser::Layout_declarationContext * /*ctx*/) override { }
  virtual void exitLayout_declaration(GLSLParser::Layout_declarationContext * /*ctx*/) override { }

  virtual void enterLayout_qualifiers(GLSLParser::Layout_qualifiersContext * /*ctx*/) override { }
  virtual void exitLayout_qualifiers(GLSLParser::Layout_qualifiersContext * /*ctx*/) override { }

  virtual void enterLayout_qualifier(GLSLParser::Layout_qualifierContext * /*ctx*/) override { }
  virtual void exitLayout_qualifier(GLSLParser::Layout_qualifierContext * /*ctx*/) override { }

  virtual void enterLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext * /*ctx*/) override { }
  virtual void exitLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext * /*ctx*/) override { }

  virtual void enterLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext * /*ctx*/) override { }
  virtual void exitLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext * /*ctx*/) override { }

  virtual void enterLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext * /*ctx*/) override { }
  virtual void exitLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext * /*ctx*/) override { }

  virtual void enterArray_specifier(GLSLParser::Array_specifierContext * /*ctx*/) override { }
  virtual void exitArray_specifier(GLSLParser::Array_specifierContext * /*ctx*/) override { }

  virtual void enterVariable_type(GLSLParser::Variable_typeContext * /*ctx*/) override { }
  virtual void exitVariable_type(GLSLParser::Variable_typeContext * /*ctx*/) override { }

  virtual void enterPrimitive_type(GLSLParser::Primitive_typeContext * /*ctx*/) override { }
  virtual void exitPrimitive_type(GLSLParser::Primitive_typeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

