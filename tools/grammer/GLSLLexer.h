
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  GLSLLexer : public antlr4::Lexer {
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

