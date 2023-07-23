
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  GLSLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, LAYOUT = 2, LOCATION = 3, COMPONENT = 4, MAIN = 5, BINDING = 6, 
    INDEX = 7, STD = 8, OFFSET = 9, STRING_LITERAL = 10, HASH = 11, NEWLINE = 12, 
    SPACE = 13, TAB = 14, LINE_COMMENT = 15, BLOCK_COMMENT = 16, SEMICOLON = 17, 
    COMMA = 18, EQUAL = 19, LEFT_PAREN = 20, RIGHT_PAREN = 21, LEFT_BRACKET = 22, 
    RIGHT_BRACKET = 23, LEFT_BRACE = 24, RIGHT_BRACE = 25, DOT = 26, PLUS = 27, 
    MINUS = 28, STAR = 29, SLASH = 30, PERCENT = 31, INC_OP = 32, DEC_OP = 33, 
    LEFT_ANGLE = 34, RIGHT_ANGLE = 35, LEFT_ANGLE_EQUAL = 36, RIGHT_ANGLE_EQUAL = 37, 
    VERTICAL_BAR = 38, CARET = 39, AMPERSAND = 40, OR_OP = 41, XOR_OP = 42, 
    AND_OP = 43, EQUAL_EQUAL = 44, BANG_EQUAL = 45, LEFT_OP = 46, RIGHT_OP = 47, 
    QUESTION = 48, COLON = 49, BANG = 50, TILDE = 51, MUL_ASSIGN = 52, DIV_ASSIGN = 53, 
    MOD_ASSIGN = 54, ADD_ASSIGN = 55, SUB_ASSIGN = 56, LEFT_ASSIGN = 57, 
    RIGHT_ASSIGN = 58, AND_ASSIGN = 59, XOR_ASSIGN = 60, OR_ASSIGN = 61, 
    VOID = 62, FLOATCONSTANT = 63, INTCONSTANT = 64, UINTCONSTANT = 65, 
    BOOLCONSTANT = 66, FLOAT = 67, DOUBLE = 68, INT = 69, UINT = 70, BOOL = 71, 
    VEC2 = 72, VEC3 = 73, VEC4 = 74, DVEC2 = 75, DVEC3 = 76, DVEC4 = 77, 
    BVEC2 = 78, BVEC3 = 79, BVEC4 = 80, IVEC2 = 81, IVEC3 = 82, IVEC4 = 83, 
    UVEC2 = 84, UVEC3 = 85, UVEC4 = 86, MAT2X2 = 87, MAT2X3 = 88, MAT2X4 = 89, 
    MAT3X2 = 90, MAT3X3 = 91, MAT3X4 = 92, MAT4X2 = 93, MAT4X3 = 94, MAT4X4 = 95, 
    DMAT2X2 = 96, DMAT2X3 = 97, DMAT2X4 = 98, DMAT3X2 = 99, DMAT3X3 = 100, 
    DMAT3X4 = 101, DMAT4X2 = 102, DMAT4X3 = 103, DMAT4X4 = 104, SAMPLER1D = 105, 
    SAMPLER1DARRAY = 106, SAMPLER1DSHADOW = 107, SAMPLER1DARRAYSHADOW = 108, 
    SAMPLER2D = 109, SAMPLER2DARRAY = 110, SAMPLER2DSHADOW = 111, SAMPLER2DARRAYSHADOW = 112, 
    SAMPLERCUBE = 113, SAMPLERCUBEARRAY = 114, SAMPLERCUBESHADOW = 115, 
    SAMPLERCUBEARRAYSHADOW = 116, SAMPLERBUFFER = 117, SAMPLER2DRECT = 118, 
    SAMPLER2DRECTSHADOW = 119, ISAMPLER1D = 120, ISAMPLER1DARRAY = 121, 
    ISAMPLER2D = 122, ISAMPLER2DARRAY = 123, ISAMPLERCUBE = 124, ISAMPLERCUBEARRAY = 125, 
    ISAMPLERBUFFER = 126, ISAMPLER2DRECT = 127, USAMPLER1D = 128, USAMPLER1DARRAY = 129, 
    USAMPLER2D = 130, USAMPLER2DARRAY = 131, USAMPLERCUBE = 132, USAMPLERCUBEARRAY = 133, 
    USAMPLERBUFFER = 134, USAMPLER2DRECT = 135, STRUCT = 136, RETURN = 137, 
    CONTINUE = 138, DISCARD = 139, IF = 140, ELSE = 141, SWITCH = 142, CASE = 143, 
    DEFAULT = 144, WHILE = 145, DO = 146, FOR = 147, BREAK = 148, CONST = 149, 
    UNIFORM = 150, BUFFER = 151, SHARED = 152, COHERENT = 153, VOLATILE = 154, 
    RESTRICT = 155, READONLY = 156, WRITEONLY = 157, PRECISION = 158, IN = 159, 
    OUT = 160, INOUT = 161, INVARIANT = 162, CENTROID = 163, PATCH = 164, 
    SAMPLE = 165, ATOMIC_UINT = 166, NOPERAND = 167, FLAT = 168, SMOOTH = 169, 
    IDENTIFIER = 170
  };

  enum {
    RuleStartShader = 0, RulePreprocessor_directive = 1, RulePush_constant_block = 2, 
    RuleShader_uniform_block = 3, RuleShader_uniform_single = 4, RuleShader_io_variable = 5, 
    RuleShader_struct_declaration = 6, RuleShader_io_specifiers = 7, RuleStruct_type_name = 8, 
    RuleShader_uniform_object = 9, RulePush_constant_object = 10, RuleDirective_name = 11, 
    RuleDirective_value = 12, RuleStruct_variable_declaration = 13, RuleStruct_primitive_declaration = 14, 
    RuleFunction_declaration = 15, RuleFunction_name = 16, RuleFunction_return_type = 17, 
    RuleFunction_parameters = 18, RuleFunction_parameter = 19, RuleFunction_body = 20, 
    RuleLayout_declaration = 21, RuleLayout_qualifiers = 22, RuleLayout_qualifier = 23, 
    RuleLayout_qualifier_value = 24, RuleLayout_qualifier_type = 25, RuleLayout_std_qualifier = 26, 
    RuleArray_specifier = 27, RuleVariable_type = 28, RulePrimitive_type = 29
  };

  explicit GLSLParser(antlr4::TokenStream *input);

  GLSLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~GLSLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StartShaderContext;
  class Preprocessor_directiveContext;
  class Push_constant_blockContext;
  class Shader_uniform_blockContext;
  class Shader_uniform_singleContext;
  class Shader_io_variableContext;
  class Shader_struct_declarationContext;
  class Shader_io_specifiersContext;
  class Struct_type_nameContext;
  class Shader_uniform_objectContext;
  class Push_constant_objectContext;
  class Directive_nameContext;
  class Directive_valueContext;
  class Struct_variable_declarationContext;
  class Struct_primitive_declarationContext;
  class Function_declarationContext;
  class Function_nameContext;
  class Function_return_typeContext;
  class Function_parametersContext;
  class Function_parameterContext;
  class Function_bodyContext;
  class Layout_declarationContext;
  class Layout_qualifiersContext;
  class Layout_qualifierContext;
  class Layout_qualifier_valueContext;
  class Layout_qualifier_typeContext;
  class Layout_std_qualifierContext;
  class Array_specifierContext;
  class Variable_typeContext;
  class Primitive_typeContext; 

  class  StartShaderContext : public antlr4::ParserRuleContext {
  public:
    StartShaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Preprocessor_directiveContext *preprocessor_directive();
    std::vector<Push_constant_blockContext *> push_constant_block();
    Push_constant_blockContext* push_constant_block(size_t i);
    std::vector<Shader_uniform_blockContext *> shader_uniform_block();
    Shader_uniform_blockContext* shader_uniform_block(size_t i);
    std::vector<Shader_uniform_singleContext *> shader_uniform_single();
    Shader_uniform_singleContext* shader_uniform_single(size_t i);
    std::vector<Shader_io_variableContext *> shader_io_variable();
    Shader_io_variableContext* shader_io_variable(size_t i);
    std::vector<Shader_struct_declarationContext *> shader_struct_declaration();
    Shader_struct_declarationContext* shader_struct_declaration(size_t i);
    std::vector<Function_declarationContext *> function_declaration();
    Function_declarationContext* function_declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartShaderContext* startShader();

  class  Preprocessor_directiveContext : public antlr4::ParserRuleContext {
  public:
    Preprocessor_directiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASH();
    Directive_nameContext *directive_name();
    Directive_valueContext *directive_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Preprocessor_directiveContext* preprocessor_directive();

  class  Push_constant_blockContext : public antlr4::ParserRuleContext {
  public:
    Push_constant_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LAYOUT();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    antlr4::tree::TerminalNode *UNIFORM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    Push_constant_objectContext *push_constant_object();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<Struct_variable_declarationContext *> struct_variable_declaration();
    Struct_variable_declarationContext* struct_variable_declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Push_constant_blockContext* push_constant_block();

  class  Shader_uniform_blockContext : public antlr4::ParserRuleContext {
  public:
    Shader_uniform_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Layout_declarationContext *layout_declaration();
    antlr4::tree::TerminalNode *UNIFORM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<Struct_variable_declarationContext *> struct_variable_declaration();
    Struct_variable_declarationContext* struct_variable_declaration(size_t i);
    Shader_uniform_objectContext *shader_uniform_object();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_uniform_blockContext* shader_uniform_block();

  class  Shader_uniform_singleContext : public antlr4::ParserRuleContext {
  public:
    Shader_uniform_singleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Layout_declarationContext *layout_declaration();
    antlr4::tree::TerminalNode *UNIFORM();
    Variable_typeContext *variable_type();
    Shader_uniform_objectContext *shader_uniform_object();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_uniform_singleContext* shader_uniform_single();

  class  Shader_io_variableContext : public antlr4::ParserRuleContext {
  public:
    Shader_io_variableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Layout_declarationContext *layout_declaration();
    Shader_io_specifiersContext *shader_io_specifiers();
    Variable_typeContext *variable_type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_io_variableContext* shader_io_variable();

  class  Shader_struct_declarationContext : public antlr4::ParserRuleContext {
  public:
    Shader_struct_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    Struct_type_nameContext *struct_type_name();
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<Struct_variable_declarationContext *> struct_variable_declaration();
    Struct_variable_declarationContext* struct_variable_declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_struct_declarationContext* shader_struct_declaration();

  class  Shader_io_specifiersContext : public antlr4::ParserRuleContext {
  public:
    Shader_io_specifiersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *FLAT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_io_specifiersContext* shader_io_specifiers();

  class  Struct_type_nameContext : public antlr4::ParserRuleContext {
  public:
    Struct_type_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_type_nameContext* struct_type_name();

  class  Shader_uniform_objectContext : public antlr4::ParserRuleContext {
  public:
    Shader_uniform_objectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    Array_specifierContext *array_specifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_uniform_objectContext* shader_uniform_object();

  class  Push_constant_objectContext : public antlr4::ParserRuleContext {
  public:
    Push_constant_objectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Push_constant_objectContext* push_constant_object();

  class  Directive_nameContext : public antlr4::ParserRuleContext {
  public:
    Directive_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Directive_nameContext* directive_name();

  class  Directive_valueContext : public antlr4::ParserRuleContext {
  public:
    Directive_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INTCONSTANT();
    antlr4::tree::TerminalNode* INTCONSTANT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> FLOATCONSTANT();
    antlr4::tree::TerminalNode* FLOATCONSTANT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Directive_valueContext* directive_value();

  class  Struct_variable_declarationContext : public antlr4::ParserRuleContext {
  public:
    Struct_variable_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_typeContext *variable_type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_variable_declarationContext* struct_variable_declaration();

  class  Struct_primitive_declarationContext : public antlr4::ParserRuleContext {
  public:
    Struct_primitive_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primitive_typeContext *primitive_type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_primitive_declarationContext* struct_primitive_declaration();

  class  Function_declarationContext : public antlr4::ParserRuleContext {
  public:
    Function_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_return_typeContext *function_return_type();
    Function_nameContext *function_name();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    Function_bodyContext *function_body();
    Function_parametersContext *function_parameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_declarationContext* function_declaration();

  class  Function_nameContext : public antlr4::ParserRuleContext {
  public:
    Function_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MAIN();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_nameContext* function_name();

  class  Function_return_typeContext : public antlr4::ParserRuleContext {
  public:
    Function_return_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_typeContext *variable_type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_return_typeContext* function_return_type();

  class  Function_parametersContext : public antlr4::ParserRuleContext {
  public:
    Function_parametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Function_parameterContext *> function_parameter();
    Function_parameterContext* function_parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_parametersContext* function_parameters();

  class  Function_parameterContext : public antlr4::ParserRuleContext {
  public:
    Function_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_typeContext *variable_type();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_parameterContext* function_parameter();

  class  Function_bodyContext : public antlr4::ParserRuleContext {
  public:
    Function_bodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_bodyContext* function_body();

  class  Layout_declarationContext : public antlr4::ParserRuleContext {
  public:
    Layout_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LAYOUT();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    Layout_qualifiersContext *layout_qualifiers();
    antlr4::tree::TerminalNode *RIGHT_PAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_declarationContext* layout_declaration();

  class  Layout_qualifiersContext : public antlr4::ParserRuleContext {
  public:
    Layout_qualifiersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Layout_qualifierContext *> layout_qualifier();
    Layout_qualifierContext* layout_qualifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_qualifiersContext* layout_qualifiers();

  class  Layout_qualifierContext : public antlr4::ParserRuleContext {
  public:
    Layout_qualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Layout_qualifier_typeContext *layout_qualifier_type();
    antlr4::tree::TerminalNode *EQUAL();
    Layout_qualifier_valueContext *layout_qualifier_value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_qualifierContext* layout_qualifier();

  class  Layout_qualifier_valueContext : public antlr4::ParserRuleContext {
  public:
    Layout_qualifier_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTCONSTANT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_qualifier_valueContext* layout_qualifier_value();

  class  Layout_qualifier_typeContext : public antlr4::ParserRuleContext {
  public:
    Layout_qualifier_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Layout_std_qualifierContext *layout_std_qualifier();
    antlr4::tree::TerminalNode *LOCATION();
    antlr4::tree::TerminalNode *COMPONENT();
    antlr4::tree::TerminalNode *BINDING();
    antlr4::tree::TerminalNode *INDEX();
    antlr4::tree::TerminalNode *OFFSET();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_qualifier_typeContext* layout_qualifier_type();

  class  Layout_std_qualifierContext : public antlr4::ParserRuleContext {
  public:
    Layout_std_qualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STD();
    antlr4::tree::TerminalNode *INTCONSTANT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Layout_std_qualifierContext* layout_std_qualifier();

  class  Array_specifierContext : public antlr4::ParserRuleContext {
  public:
    Array_specifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_BRACKET();
    antlr4::tree::TerminalNode *INTCONSTANT();
    antlr4::tree::TerminalNode *RIGHT_BRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Array_specifierContext* array_specifier();

  class  Variable_typeContext : public antlr4::ParserRuleContext {
  public:
    Variable_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Primitive_typeContext *primitive_type();
    Struct_type_nameContext *struct_type_name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_typeContext* variable_type();

  class  Primitive_typeContext : public antlr4::ParserRuleContext {
  public:
    Primitive_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *VEC2();
    antlr4::tree::TerminalNode *VEC3();
    antlr4::tree::TerminalNode *VEC4();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *IVEC2();
    antlr4::tree::TerminalNode *IVEC3();
    antlr4::tree::TerminalNode *DOUBLE();
    antlr4::tree::TerminalNode *DVEC2();
    antlr4::tree::TerminalNode *DVEC3();
    antlr4::tree::TerminalNode *DVEC4();
    antlr4::tree::TerminalNode *UINT();
    antlr4::tree::TerminalNode *UVEC2();
    antlr4::tree::TerminalNode *UVEC3();
    antlr4::tree::TerminalNode *UVEC4();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *BVEC2();
    antlr4::tree::TerminalNode *BVEC3();
    antlr4::tree::TerminalNode *BVEC4();
    antlr4::tree::TerminalNode *MAT2X2();
    antlr4::tree::TerminalNode *MAT2X3();
    antlr4::tree::TerminalNode *MAT2X4();
    antlr4::tree::TerminalNode *MAT3X2();
    antlr4::tree::TerminalNode *MAT3X3();
    antlr4::tree::TerminalNode *MAT3X4();
    antlr4::tree::TerminalNode *MAT4X2();
    antlr4::tree::TerminalNode *MAT4X3();
    antlr4::tree::TerminalNode *MAT4X4();
    antlr4::tree::TerminalNode *DMAT2X2();
    antlr4::tree::TerminalNode *DMAT2X3();
    antlr4::tree::TerminalNode *DMAT2X4();
    antlr4::tree::TerminalNode *DMAT3X2();
    antlr4::tree::TerminalNode *DMAT3X3();
    antlr4::tree::TerminalNode *DMAT3X4();
    antlr4::tree::TerminalNode *DMAT4X2();
    antlr4::tree::TerminalNode *DMAT4X3();
    antlr4::tree::TerminalNode *DMAT4X4();
    antlr4::tree::TerminalNode *SAMPLER1D();
    antlr4::tree::TerminalNode *SAMPLER1DARRAY();
    antlr4::tree::TerminalNode *SAMPLER1DSHADOW();
    antlr4::tree::TerminalNode *SAMPLER1DARRAYSHADOW();
    antlr4::tree::TerminalNode *SAMPLER2D();
    antlr4::tree::TerminalNode *SAMPLER2DARRAY();
    antlr4::tree::TerminalNode *SAMPLER2DSHADOW();
    antlr4::tree::TerminalNode *SAMPLER2DARRAYSHADOW();
    antlr4::tree::TerminalNode *SAMPLERCUBE();
    antlr4::tree::TerminalNode *SAMPLERCUBEARRAY();
    antlr4::tree::TerminalNode *SAMPLERCUBESHADOW();
    antlr4::tree::TerminalNode *SAMPLERCUBEARRAYSHADOW();
    antlr4::tree::TerminalNode *SAMPLERBUFFER();
    antlr4::tree::TerminalNode *SAMPLER2DRECT();
    antlr4::tree::TerminalNode *SAMPLER2DRECTSHADOW();
    antlr4::tree::TerminalNode *ISAMPLER1D();
    antlr4::tree::TerminalNode *ISAMPLER1DARRAY();
    antlr4::tree::TerminalNode *ISAMPLER2D();
    antlr4::tree::TerminalNode *ISAMPLER2DARRAY();
    antlr4::tree::TerminalNode *ISAMPLERCUBE();
    antlr4::tree::TerminalNode *ISAMPLERCUBEARRAY();
    antlr4::tree::TerminalNode *ISAMPLERBUFFER();
    antlr4::tree::TerminalNode *ISAMPLER2DRECT();
    antlr4::tree::TerminalNode *USAMPLER1D();
    antlr4::tree::TerminalNode *USAMPLER1DARRAY();
    antlr4::tree::TerminalNode *USAMPLER2D();
    antlr4::tree::TerminalNode *USAMPLER2DARRAY();
    antlr4::tree::TerminalNode *USAMPLERCUBE();
    antlr4::tree::TerminalNode *USAMPLERCUBEARRAY();
    antlr4::tree::TerminalNode *USAMPLERBUFFER();
    antlr4::tree::TerminalNode *USAMPLER2DRECT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Primitive_typeContext* primitive_type();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

