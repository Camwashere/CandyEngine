
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  GLSLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, LAYOUT = 2, LOCATION = 3, COMPONENT = 4, MAIN = 5, BINDING = 6, 
    INDEX = 7, SET = 8, STD = 9, OFFSET = 10, STRING_LITERAL = 11, HASH = 12, 
    NEWLINE = 13, SPACE = 14, TAB = 15, LINE_COMMENT = 16, BLOCK_COMMENT = 17, 
    SEMICOLON = 18, COMMA = 19, EQUAL = 20, LEFT_PAREN = 21, RIGHT_PAREN = 22, 
    LEFT_BRACKET = 23, RIGHT_BRACKET = 24, LEFT_BRACE = 25, RIGHT_BRACE = 26, 
    DOT = 27, PLUS = 28, MINUS = 29, STAR = 30, SLASH = 31, PERCENT = 32, 
    INC_OP = 33, DEC_OP = 34, LEFT_ANGLE = 35, RIGHT_ANGLE = 36, LEFT_ANGLE_EQUAL = 37, 
    RIGHT_ANGLE_EQUAL = 38, VERTICAL_BAR = 39, CARET = 40, AMPERSAND = 41, 
    OR_OP = 42, XOR_OP = 43, AND_OP = 44, EQUAL_EQUAL = 45, BANG_EQUAL = 46, 
    LEFT_OP = 47, RIGHT_OP = 48, QUESTION = 49, COLON = 50, BANG = 51, TILDE = 52, 
    MUL_ASSIGN = 53, DIV_ASSIGN = 54, MOD_ASSIGN = 55, ADD_ASSIGN = 56, 
    SUB_ASSIGN = 57, LEFT_ASSIGN = 58, RIGHT_ASSIGN = 59, AND_ASSIGN = 60, 
    XOR_ASSIGN = 61, OR_ASSIGN = 62, VOID = 63, FLOATCONSTANT = 64, INTCONSTANT = 65, 
    UINTCONSTANT = 66, BOOLCONSTANT = 67, FLOAT = 68, DOUBLE = 69, INT = 70, 
    UINT = 71, BOOL = 72, VEC2 = 73, VEC3 = 74, VEC4 = 75, DVEC2 = 76, DVEC3 = 77, 
    DVEC4 = 78, BVEC2 = 79, BVEC3 = 80, BVEC4 = 81, IVEC2 = 82, IVEC3 = 83, 
    IVEC4 = 84, UVEC2 = 85, UVEC3 = 86, UVEC4 = 87, MAT2X2 = 88, MAT2X3 = 89, 
    MAT2X4 = 90, MAT3X2 = 91, MAT3X3 = 92, MAT3X4 = 93, MAT4X2 = 94, MAT4X3 = 95, 
    MAT4X4 = 96, DMAT2X2 = 97, DMAT2X3 = 98, DMAT2X4 = 99, DMAT3X2 = 100, 
    DMAT3X3 = 101, DMAT3X4 = 102, DMAT4X2 = 103, DMAT4X3 = 104, DMAT4X4 = 105, 
    SAMPLER1D = 106, SAMPLER1DARRAY = 107, SAMPLER1DSHADOW = 108, SAMPLER1DARRAYSHADOW = 109, 
    SAMPLER2D = 110, SAMPLER2DARRAY = 111, SAMPLER2DSHADOW = 112, SAMPLER2DARRAYSHADOW = 113, 
    SAMPLERCUBE = 114, SAMPLERCUBEARRAY = 115, SAMPLERCUBESHADOW = 116, 
    SAMPLERCUBEARRAYSHADOW = 117, SAMPLERBUFFER = 118, SAMPLER2DRECT = 119, 
    SAMPLER2DRECTSHADOW = 120, ISAMPLER1D = 121, ISAMPLER1DARRAY = 122, 
    ISAMPLER2D = 123, ISAMPLER2DARRAY = 124, ISAMPLERCUBE = 125, ISAMPLERCUBEARRAY = 126, 
    ISAMPLERBUFFER = 127, ISAMPLER2DRECT = 128, USAMPLER1D = 129, USAMPLER1DARRAY = 130, 
    USAMPLER2D = 131, USAMPLER2DARRAY = 132, USAMPLERCUBE = 133, USAMPLERCUBEARRAY = 134, 
    USAMPLERBUFFER = 135, USAMPLER2DRECT = 136, STRUCT = 137, RETURN = 138, 
    CONTINUE = 139, DISCARD = 140, IF = 141, ELSE = 142, SWITCH = 143, CASE = 144, 
    DEFAULT = 145, WHILE = 146, DO = 147, FOR = 148, BREAK = 149, CONST = 150, 
    UNIFORM = 151, BUFFER = 152, SHARED = 153, COHERENT = 154, VOLATILE = 155, 
    RESTRICT = 156, READONLY = 157, WRITEONLY = 158, PRECISION = 159, IN = 160, 
    OUT = 161, INOUT = 162, INVARIANT = 163, CENTROID = 164, PATCH = 165, 
    SAMPLE = 166, ATOMIC_UINT = 167, NOPERAND = 168, FLAT = 169, SMOOTH = 170, 
    IDENTIFIER = 171
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
    antlr4::tree::TerminalNode *SET();
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

