
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "GLSLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by GLSLParser.
 */
class  GLSLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GLSLParser.
   */
    virtual std::any visitStartShader(GLSLParser::StartShaderContext *context) = 0;

    virtual std::any visitPreprocessor_directive(GLSLParser::Preprocessor_directiveContext *context) = 0;

    virtual std::any visitPush_constant_block(GLSLParser::Push_constant_blockContext *context) = 0;

    virtual std::any visitShader_uniform_block(GLSLParser::Shader_uniform_blockContext *context) = 0;

    virtual std::any visitShader_uniform_single(GLSLParser::Shader_uniform_singleContext *context) = 0;

    virtual std::any visitShader_io_variable(GLSLParser::Shader_io_variableContext *context) = 0;

    virtual std::any visitShader_struct_declaration(GLSLParser::Shader_struct_declarationContext *context) = 0;

    virtual std::any visitShader_io_specifiers(GLSLParser::Shader_io_specifiersContext *context) = 0;

    virtual std::any visitStruct_type_name(GLSLParser::Struct_type_nameContext *context) = 0;

    virtual std::any visitShader_uniform_object(GLSLParser::Shader_uniform_objectContext *context) = 0;

    virtual std::any visitPush_constant_object(GLSLParser::Push_constant_objectContext *context) = 0;

    virtual std::any visitDirective_name(GLSLParser::Directive_nameContext *context) = 0;

    virtual std::any visitDirective_value(GLSLParser::Directive_valueContext *context) = 0;

    virtual std::any visitStruct_variable_declaration(GLSLParser::Struct_variable_declarationContext *context) = 0;

    virtual std::any visitStruct_primitive_declaration(GLSLParser::Struct_primitive_declarationContext *context) = 0;

    virtual std::any visitFunction_declaration(GLSLParser::Function_declarationContext *context) = 0;

    virtual std::any visitFunction_name(GLSLParser::Function_nameContext *context) = 0;

    virtual std::any visitFunction_return_type(GLSLParser::Function_return_typeContext *context) = 0;

    virtual std::any visitFunction_parameters(GLSLParser::Function_parametersContext *context) = 0;

    virtual std::any visitFunction_parameter(GLSLParser::Function_parameterContext *context) = 0;

    virtual std::any visitFunction_body(GLSLParser::Function_bodyContext *context) = 0;

    virtual std::any visitLayout_declaration(GLSLParser::Layout_declarationContext *context) = 0;

    virtual std::any visitLayout_qualifiers(GLSLParser::Layout_qualifiersContext *context) = 0;

    virtual std::any visitLayout_qualifier(GLSLParser::Layout_qualifierContext *context) = 0;

    virtual std::any visitLayout_qualifier_value(GLSLParser::Layout_qualifier_valueContext *context) = 0;

    virtual std::any visitLayout_qualifier_type(GLSLParser::Layout_qualifier_typeContext *context) = 0;

    virtual std::any visitLayout_std_qualifier(GLSLParser::Layout_std_qualifierContext *context) = 0;

    virtual std::any visitArray_specifier(GLSLParser::Array_specifierContext *context) = 0;

    virtual std::any visitVariable_type(GLSLParser::Variable_typeContext *context) = 0;

    virtual std::any visitPrimitive_type(GLSLParser::Primitive_typeContext *context) = 0;


};

