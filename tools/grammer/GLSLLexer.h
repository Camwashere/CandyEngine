
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  GLSLLexer : public antlr4::Lexer {
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

  explicit GLSLLexer(antlr4::CharStream *input);

  ~GLSLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

