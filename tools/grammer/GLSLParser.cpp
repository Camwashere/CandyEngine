
// Generated from C:/Users/perso/CLionProjects/CandyEngine/tools/grammer\GLSL.g4 by ANTLR 4.12.0


#include "GLSLListener.h"
#include "GLSLVisitor.h"

#include "GLSLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct GLSLParserStaticData final {
  GLSLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GLSLParserStaticData(const GLSLParserStaticData&) = delete;
  GLSLParserStaticData(GLSLParserStaticData&&) = delete;
  GLSLParserStaticData& operator=(const GLSLParserStaticData&) = delete;
  GLSLParserStaticData& operator=(GLSLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag glslParserOnceFlag;
GLSLParserStaticData *glslParserStaticData = nullptr;

void glslParserInitialize() {
  assert(glslParserStaticData == nullptr);
  auto staticData = std::make_unique<GLSLParserStaticData>(
    std::vector<std::string>{
      "startShader", "preprocessor_directive", "push_constant_block", "shader_uniform_block", 
      "shader_uniform_single", "shader_io_variable", "shader_struct_declaration", 
      "shader_io_specifiers", "struct_type_name", "shader_uniform_object", 
      "push_constant_object", "directive_name", "directive_value", "struct_variable_declaration", 
      "struct_primitive_declaration", "function_declaration", "function_name", 
      "function_return_type", "function_parameters", "function_parameter", 
      "function_body", "layout_declaration", "layout_qualifiers", "layout_qualifier", 
      "layout_qualifier_value", "layout_qualifier_type", "layout_std_qualifier", 
      "array_specifier", "variable_type", "primitive_type"
    },
    std::vector<std::string>{
      "", "'push_constant'", "'layout'", "'location'", "'component'", "'main'", 
      "'binding'", "'index'", "'set'", "'std'", "'offset'", "", "'#'", "", 
      "", "", "", "", "';'", "','", "'='", "'('", "')'", "'['", "']'", "'{'", 
      "'}'", "'.'", "'+'", "'-'", "'*'", "'/'", "'%'", "'++'", "'--'", "'<'", 
      "'>'", "'<='", "'>='", "'|'", "'^'", "'&'", "'||'", "'^^'", "'&&'", 
      "'=='", "'!='", "'<<'", "'>>'", "'\\u003F'", "':'", "'!'", "'~'", 
      "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'&='", 
      "'^='", "'|='", "'void'", "", "", "", "", "'float'", "'double'", "'int'", 
      "'uint'", "'bool'", "'vec2'", "'vec3'", "'vec4'", "'dvec2'", "'dvec3'", 
      "'dvec4'", "'bvec2'", "'bvec3'", "'bvec4'", "'ivec2'", "'ivec3'", 
      "'ivec4'", "'uvec2'", "'uvec3'", "'uvec4'", "", "'mat2x3'", "'mat2x4'", 
      "'mat3x2'", "", "'mat3x4'", "'mat4x2'", "'mat4x3'", "", "", "'dmat2x3'", 
      "'dmat2x4'", "'dmat3x2'", "", "'dmat3x4'", "'dmat4x2'", "'dmat4x3'", 
      "", "'sampler1D'", "'sampler1DArray'", "'sampler1DShadow'", "'sampler1DArrayShadow'", 
      "'sampler2D'", "'sampler2DArray'", "'sampler2DShadow'", "'sampler2DArrayShadow'", 
      "'samplerCube'", "'samplerCubeArray'", "'samplerCubeShadow'", "'samplerCubeArrayShadow'", 
      "'samplerBuffer'", "'sampler2DRect'", "'sampler2DRectShadow'", "'isampler1D'", 
      "'isampler1DArray'", "'isampler2D'", "'isampler2DArray'", "'isamplerCube'", 
      "'isamplerCubeArray'", "'isamplerBuffer'", "'isampler2DRect'", "'usampler1D'", 
      "'usampler1DArray'", "'usampler2D'", "'usampler2DArray'", "'usamplerCube'", 
      "'usamplerCubeArray'", "'usamplerBuffer'", "'usampler2DRect'", "'struct'", 
      "'return'", "'continue'", "'discard'", "'if'", "'else'", "'switch'", 
      "'case'", "'default'", "'while'", "'do'", "'for'", "'break'", "'const'", 
      "'uniform'", "'buffer'", "'shared'", "'coherent'", "'volatile'", "'restrict'", 
      "'readonly'", "'writeonly'", "'precision'", "'in'", "'out'", "'inout'", 
      "'invariant'", "'centroid'", "'patch'", "'sample'", "'atomic_uint'", 
      "'noperspective'", "'flat'", "'smooth'"
    },
    std::vector<std::string>{
      "", "", "LAYOUT", "LOCATION", "COMPONENT", "MAIN", "BINDING", "INDEX", 
      "SET", "STD", "OFFSET", "STRING_LITERAL", "HASH", "NEWLINE", "SPACE", 
      "TAB", "LINE_COMMENT", "BLOCK_COMMENT", "SEMICOLON", "COMMA", "EQUAL", 
      "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE", 
      "RIGHT_BRACE", "DOT", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", 
      "INC_OP", "DEC_OP", "LEFT_ANGLE", "RIGHT_ANGLE", "LEFT_ANGLE_EQUAL", 
      "RIGHT_ANGLE_EQUAL", "VERTICAL_BAR", "CARET", "AMPERSAND", "OR_OP", 
      "XOR_OP", "AND_OP", "EQUAL_EQUAL", "BANG_EQUAL", "LEFT_OP", "RIGHT_OP", 
      "QUESTION", "COLON", "BANG", "TILDE", "MUL_ASSIGN", "DIV_ASSIGN", 
      "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", 
      "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "VOID", "FLOATCONSTANT", 
      "INTCONSTANT", "UINTCONSTANT", "BOOLCONSTANT", "FLOAT", "DOUBLE", 
      "INT", "UINT", "BOOL", "VEC2", "VEC3", "VEC4", "DVEC2", "DVEC3", "DVEC4", 
      "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "UVEC2", "UVEC3", 
      "UVEC4", "MAT2X2", "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4", 
      "MAT4X2", "MAT4X3", "MAT4X4", "DMAT2X2", "DMAT2X3", "DMAT2X4", "DMAT3X2", 
      "DMAT3X3", "DMAT3X4", "DMAT4X2", "DMAT4X3", "DMAT4X4", "SAMPLER1D", 
      "SAMPLER1DARRAY", "SAMPLER1DSHADOW", "SAMPLER1DARRAYSHADOW", "SAMPLER2D", 
      "SAMPLER2DARRAY", "SAMPLER2DSHADOW", "SAMPLER2DARRAYSHADOW", "SAMPLERCUBE", 
      "SAMPLERCUBEARRAY", "SAMPLERCUBESHADOW", "SAMPLERCUBEARRAYSHADOW", 
      "SAMPLERBUFFER", "SAMPLER2DRECT", "SAMPLER2DRECTSHADOW", "ISAMPLER1D", 
      "ISAMPLER1DARRAY", "ISAMPLER2D", "ISAMPLER2DARRAY", "ISAMPLERCUBE", 
      "ISAMPLERCUBEARRAY", "ISAMPLERBUFFER", "ISAMPLER2DRECT", "USAMPLER1D", 
      "USAMPLER1DARRAY", "USAMPLER2D", "USAMPLER2DARRAY", "USAMPLERCUBE", 
      "USAMPLERCUBEARRAY", "USAMPLERBUFFER", "USAMPLER2DRECT", "STRUCT", 
      "RETURN", "CONTINUE", "DISCARD", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", 
      "WHILE", "DO", "FOR", "BREAK", "CONST", "UNIFORM", "BUFFER", "SHARED", 
      "COHERENT", "VOLATILE", "RESTRICT", "READONLY", "WRITEONLY", "PRECISION", 
      "IN", "OUT", "INOUT", "INVARIANT", "CENTROID", "PATCH", "SAMPLE", 
      "ATOMIC_UINT", "NOPERAND", "FLAT", "SMOOTH", "IDENTIFIER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,171,255,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,1,0,1,0,1,0,4,0,64,8,0,11,0,12,0,65,1,0,4,0,69,8,0,11,0,
  	12,0,70,1,0,4,0,74,8,0,11,0,12,0,75,1,0,4,0,79,8,0,11,0,12,0,80,1,0,4,
  	0,84,8,0,11,0,12,0,85,5,0,88,8,0,10,0,12,0,91,9,0,1,1,1,1,1,1,1,1,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,4,2,105,8,2,11,2,12,2,106,1,2,1,2,1,2,1,2,
  	1,3,1,3,1,3,1,3,1,3,4,3,118,8,3,11,3,12,3,119,1,3,1,3,3,3,124,8,3,1,3,
  	1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,4,
  	6,144,8,6,11,6,12,6,145,1,6,1,6,1,6,1,7,1,7,3,7,153,8,7,1,8,1,8,1,9,1,
  	9,3,9,159,8,9,1,10,1,10,1,11,1,11,1,12,5,12,166,8,12,10,12,12,12,169,
  	9,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,3,15,
  	183,8,15,1,15,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,5,18,195,8,
  	18,10,18,12,18,198,9,18,1,19,1,19,1,19,1,20,1,20,5,20,205,8,20,10,20,
  	12,20,208,9,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,5,22,
  	220,8,22,10,22,12,22,223,9,22,1,23,1,23,1,23,3,23,228,8,23,1,24,1,24,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,240,8,25,1,26,1,26,1,26,
  	1,27,1,27,1,27,1,27,1,28,1,28,3,28,251,8,28,1,29,1,29,1,29,1,206,0,30,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,
  	50,52,54,56,58,0,4,1,0,160,161,3,0,11,11,64,65,171,171,2,0,5,5,171,171,
  	3,0,63,63,68,83,85,136,255,0,60,1,0,0,0,2,92,1,0,0,0,4,96,1,0,0,0,6,112,
  	1,0,0,0,8,127,1,0,0,0,10,133,1,0,0,0,12,139,1,0,0,0,14,150,1,0,0,0,16,
  	154,1,0,0,0,18,156,1,0,0,0,20,160,1,0,0,0,22,162,1,0,0,0,24,167,1,0,0,
  	0,26,170,1,0,0,0,28,174,1,0,0,0,30,178,1,0,0,0,32,187,1,0,0,0,34,189,
  	1,0,0,0,36,191,1,0,0,0,38,199,1,0,0,0,40,202,1,0,0,0,42,211,1,0,0,0,44,
  	216,1,0,0,0,46,224,1,0,0,0,48,229,1,0,0,0,50,239,1,0,0,0,52,241,1,0,0,
  	0,54,244,1,0,0,0,56,250,1,0,0,0,58,252,1,0,0,0,60,89,3,2,1,0,61,88,3,
  	4,2,0,62,64,3,6,3,0,63,62,1,0,0,0,64,65,1,0,0,0,65,63,1,0,0,0,65,66,1,
  	0,0,0,66,88,1,0,0,0,67,69,3,8,4,0,68,67,1,0,0,0,69,70,1,0,0,0,70,68,1,
  	0,0,0,70,71,1,0,0,0,71,88,1,0,0,0,72,74,3,10,5,0,73,72,1,0,0,0,74,75,
  	1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,76,88,1,0,0,0,77,79,3,12,6,0,78,77,
  	1,0,0,0,79,80,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,88,1,0,0,0,82,84,
  	3,30,15,0,83,82,1,0,0,0,84,85,1,0,0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,
  	88,1,0,0,0,87,61,1,0,0,0,87,63,1,0,0,0,87,68,1,0,0,0,87,73,1,0,0,0,87,
  	78,1,0,0,0,87,83,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,
  	1,1,0,0,0,91,89,1,0,0,0,92,93,5,12,0,0,93,94,3,22,11,0,94,95,3,24,12,
  	0,95,3,1,0,0,0,96,97,5,2,0,0,97,98,5,21,0,0,98,99,5,1,0,0,99,100,5,22,
  	0,0,100,101,5,151,0,0,101,102,5,171,0,0,102,104,5,25,0,0,103,105,3,26,
  	13,0,104,103,1,0,0,0,105,106,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,0,
  	107,108,1,0,0,0,108,109,5,26,0,0,109,110,3,20,10,0,110,111,5,18,0,0,111,
  	5,1,0,0,0,112,113,3,42,21,0,113,114,5,151,0,0,114,115,5,171,0,0,115,117,
  	5,25,0,0,116,118,3,26,13,0,117,116,1,0,0,0,118,119,1,0,0,0,119,117,1,
  	0,0,0,119,120,1,0,0,0,120,121,1,0,0,0,121,123,5,26,0,0,122,124,3,18,9,
  	0,123,122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,125,126,5,18,0,0,126,
  	7,1,0,0,0,127,128,3,42,21,0,128,129,5,151,0,0,129,130,3,56,28,0,130,131,
  	3,18,9,0,131,132,5,18,0,0,132,9,1,0,0,0,133,134,3,42,21,0,134,135,3,14,
  	7,0,135,136,3,56,28,0,136,137,5,171,0,0,137,138,5,18,0,0,138,11,1,0,0,
  	0,139,140,5,137,0,0,140,141,3,16,8,0,141,143,5,25,0,0,142,144,3,26,13,
  	0,143,142,1,0,0,0,144,145,1,0,0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,
  	147,1,0,0,0,147,148,5,26,0,0,148,149,5,18,0,0,149,13,1,0,0,0,150,152,
  	7,0,0,0,151,153,5,169,0,0,152,151,1,0,0,0,152,153,1,0,0,0,153,15,1,0,
  	0,0,154,155,5,171,0,0,155,17,1,0,0,0,156,158,5,171,0,0,157,159,3,54,27,
  	0,158,157,1,0,0,0,158,159,1,0,0,0,159,19,1,0,0,0,160,161,5,171,0,0,161,
  	21,1,0,0,0,162,163,5,171,0,0,163,23,1,0,0,0,164,166,7,1,0,0,165,164,1,
  	0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,168,1,0,0,0,168,25,1,0,0,0,
  	169,167,1,0,0,0,170,171,3,56,28,0,171,172,5,171,0,0,172,173,5,18,0,0,
  	173,27,1,0,0,0,174,175,3,58,29,0,175,176,5,171,0,0,176,177,5,18,0,0,177,
  	29,1,0,0,0,178,179,3,34,17,0,179,180,3,32,16,0,180,182,5,21,0,0,181,183,
  	3,36,18,0,182,181,1,0,0,0,182,183,1,0,0,0,183,184,1,0,0,0,184,185,5,22,
  	0,0,185,186,3,40,20,0,186,31,1,0,0,0,187,188,7,2,0,0,188,33,1,0,0,0,189,
  	190,3,56,28,0,190,35,1,0,0,0,191,196,3,38,19,0,192,193,5,19,0,0,193,195,
  	3,38,19,0,194,192,1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,
  	0,0,197,37,1,0,0,0,198,196,1,0,0,0,199,200,3,56,28,0,200,201,5,171,0,
  	0,201,39,1,0,0,0,202,206,5,25,0,0,203,205,9,0,0,0,204,203,1,0,0,0,205,
  	208,1,0,0,0,206,207,1,0,0,0,206,204,1,0,0,0,207,209,1,0,0,0,208,206,1,
  	0,0,0,209,210,5,26,0,0,210,41,1,0,0,0,211,212,5,2,0,0,212,213,5,21,0,
  	0,213,214,3,44,22,0,214,215,5,22,0,0,215,43,1,0,0,0,216,221,3,46,23,0,
  	217,218,5,19,0,0,218,220,3,46,23,0,219,217,1,0,0,0,220,223,1,0,0,0,221,
  	219,1,0,0,0,221,222,1,0,0,0,222,45,1,0,0,0,223,221,1,0,0,0,224,227,3,
  	50,25,0,225,226,5,20,0,0,226,228,3,48,24,0,227,225,1,0,0,0,227,228,1,
  	0,0,0,228,47,1,0,0,0,229,230,5,65,0,0,230,49,1,0,0,0,231,240,3,52,26,
  	0,232,240,5,3,0,0,233,240,5,4,0,0,234,240,5,6,0,0,235,240,5,8,0,0,236,
  	240,5,7,0,0,237,240,5,10,0,0,238,240,5,171,0,0,239,231,1,0,0,0,239,232,
  	1,0,0,0,239,233,1,0,0,0,239,234,1,0,0,0,239,235,1,0,0,0,239,236,1,0,0,
  	0,239,237,1,0,0,0,239,238,1,0,0,0,240,51,1,0,0,0,241,242,5,9,0,0,242,
  	243,5,65,0,0,243,53,1,0,0,0,244,245,5,23,0,0,245,246,5,65,0,0,246,247,
  	5,24,0,0,247,55,1,0,0,0,248,251,3,58,29,0,249,251,3,16,8,0,250,248,1,
  	0,0,0,250,249,1,0,0,0,251,57,1,0,0,0,252,253,7,3,0,0,253,59,1,0,0,0,21,
  	65,70,75,80,85,87,89,106,119,123,145,152,158,167,182,196,206,221,227,
  	239,250
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  glslParserStaticData = staticData.release();
}

}

GLSLParser::GLSLParser(TokenStream *input) : GLSLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

GLSLParser::GLSLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  GLSLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *glslParserStaticData->atn, glslParserStaticData->decisionToDFA, glslParserStaticData->sharedContextCache, options);
}

GLSLParser::~GLSLParser() {
  delete _interpreter;
}

const atn::ATN& GLSLParser::getATN() const {
  return *glslParserStaticData->atn;
}

std::string GLSLParser::getGrammarFileName() const {
  return "GLSL.g4";
}

const std::vector<std::string>& GLSLParser::getRuleNames() const {
  return glslParserStaticData->ruleNames;
}

const dfa::Vocabulary& GLSLParser::getVocabulary() const {
  return glslParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GLSLParser::getSerializedATN() const {
  return glslParserStaticData->serializedATN;
}


//----------------- StartShaderContext ------------------------------------------------------------------

GLSLParser::StartShaderContext::StartShaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Preprocessor_directiveContext* GLSLParser::StartShaderContext::preprocessor_directive() {
  return getRuleContext<GLSLParser::Preprocessor_directiveContext>(0);
}

std::vector<GLSLParser::Push_constant_blockContext *> GLSLParser::StartShaderContext::push_constant_block() {
  return getRuleContexts<GLSLParser::Push_constant_blockContext>();
}

GLSLParser::Push_constant_blockContext* GLSLParser::StartShaderContext::push_constant_block(size_t i) {
  return getRuleContext<GLSLParser::Push_constant_blockContext>(i);
}

std::vector<GLSLParser::Shader_uniform_blockContext *> GLSLParser::StartShaderContext::shader_uniform_block() {
  return getRuleContexts<GLSLParser::Shader_uniform_blockContext>();
}

GLSLParser::Shader_uniform_blockContext* GLSLParser::StartShaderContext::shader_uniform_block(size_t i) {
  return getRuleContext<GLSLParser::Shader_uniform_blockContext>(i);
}

std::vector<GLSLParser::Shader_uniform_singleContext *> GLSLParser::StartShaderContext::shader_uniform_single() {
  return getRuleContexts<GLSLParser::Shader_uniform_singleContext>();
}

GLSLParser::Shader_uniform_singleContext* GLSLParser::StartShaderContext::shader_uniform_single(size_t i) {
  return getRuleContext<GLSLParser::Shader_uniform_singleContext>(i);
}

std::vector<GLSLParser::Shader_io_variableContext *> GLSLParser::StartShaderContext::shader_io_variable() {
  return getRuleContexts<GLSLParser::Shader_io_variableContext>();
}

GLSLParser::Shader_io_variableContext* GLSLParser::StartShaderContext::shader_io_variable(size_t i) {
  return getRuleContext<GLSLParser::Shader_io_variableContext>(i);
}

std::vector<GLSLParser::Shader_struct_declarationContext *> GLSLParser::StartShaderContext::shader_struct_declaration() {
  return getRuleContexts<GLSLParser::Shader_struct_declarationContext>();
}

GLSLParser::Shader_struct_declarationContext* GLSLParser::StartShaderContext::shader_struct_declaration(size_t i) {
  return getRuleContext<GLSLParser::Shader_struct_declarationContext>(i);
}

std::vector<GLSLParser::Function_declarationContext *> GLSLParser::StartShaderContext::function_declaration() {
  return getRuleContexts<GLSLParser::Function_declarationContext>();
}

GLSLParser::Function_declarationContext* GLSLParser::StartShaderContext::function_declaration(size_t i) {
  return getRuleContext<GLSLParser::Function_declarationContext>(i);
}


size_t GLSLParser::StartShaderContext::getRuleIndex() const {
  return GLSLParser::RuleStartShader;
}

void GLSLParser::StartShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartShader(this);
}

void GLSLParser::StartShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartShader(this);
}


std::any GLSLParser::StartShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitStartShader(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::StartShaderContext* GLSLParser::startShader() {
  StartShaderContext *_localctx = _tracker.createInstance<StartShaderContext>(_ctx, getState());
  enterRule(_localctx, 0, GLSLParser::RuleStartShader);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(60);
    preprocessor_directive();
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GLSLParser::LAYOUT

    || _la == GLSLParser::VOID || ((((_la - 68) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 68)) & -65537) != 0) || ((((_la - 132) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 132)) & 549755813951) != 0)) {
      setState(87);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(61);
        push_constant_block();
        break;
      }

      case 2: {
        setState(63); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(62);
                  shader_uniform_block();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(65); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case 3: {
        setState(68); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(67);
                  shader_uniform_single();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(70); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case 4: {
        setState(73); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(72);
                  shader_io_variable();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(75); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case 5: {
        setState(78); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(77);
                  shader_struct_declaration();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(80); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case 6: {
        setState(83); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(82);
                  function_declaration();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(85); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      default:
        break;
      }
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Preprocessor_directiveContext ------------------------------------------------------------------

GLSLParser::Preprocessor_directiveContext::Preprocessor_directiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Preprocessor_directiveContext::HASH() {
  return getToken(GLSLParser::HASH, 0);
}

GLSLParser::Directive_nameContext* GLSLParser::Preprocessor_directiveContext::directive_name() {
  return getRuleContext<GLSLParser::Directive_nameContext>(0);
}

GLSLParser::Directive_valueContext* GLSLParser::Preprocessor_directiveContext::directive_value() {
  return getRuleContext<GLSLParser::Directive_valueContext>(0);
}


size_t GLSLParser::Preprocessor_directiveContext::getRuleIndex() const {
  return GLSLParser::RulePreprocessor_directive;
}

void GLSLParser::Preprocessor_directiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreprocessor_directive(this);
}

void GLSLParser::Preprocessor_directiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreprocessor_directive(this);
}


std::any GLSLParser::Preprocessor_directiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitPreprocessor_directive(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Preprocessor_directiveContext* GLSLParser::preprocessor_directive() {
  Preprocessor_directiveContext *_localctx = _tracker.createInstance<Preprocessor_directiveContext>(_ctx, getState());
  enterRule(_localctx, 2, GLSLParser::RulePreprocessor_directive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(GLSLParser::HASH);
    setState(93);
    directive_name();
    setState(94);
    directive_value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Push_constant_blockContext ------------------------------------------------------------------

GLSLParser::Push_constant_blockContext::Push_constant_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::LAYOUT() {
  return getToken(GLSLParser::LAYOUT, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::LEFT_PAREN() {
  return getToken(GLSLParser::LEFT_PAREN, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::RIGHT_PAREN() {
  return getToken(GLSLParser::RIGHT_PAREN, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::UNIFORM() {
  return getToken(GLSLParser::UNIFORM, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::LEFT_BRACE() {
  return getToken(GLSLParser::LEFT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::RIGHT_BRACE() {
  return getToken(GLSLParser::RIGHT_BRACE, 0);
}

GLSLParser::Push_constant_objectContext* GLSLParser::Push_constant_blockContext::push_constant_object() {
  return getRuleContext<GLSLParser::Push_constant_objectContext>(0);
}

tree::TerminalNode* GLSLParser::Push_constant_blockContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}

std::vector<GLSLParser::Struct_variable_declarationContext *> GLSLParser::Push_constant_blockContext::struct_variable_declaration() {
  return getRuleContexts<GLSLParser::Struct_variable_declarationContext>();
}

GLSLParser::Struct_variable_declarationContext* GLSLParser::Push_constant_blockContext::struct_variable_declaration(size_t i) {
  return getRuleContext<GLSLParser::Struct_variable_declarationContext>(i);
}


size_t GLSLParser::Push_constant_blockContext::getRuleIndex() const {
  return GLSLParser::RulePush_constant_block;
}

void GLSLParser::Push_constant_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPush_constant_block(this);
}

void GLSLParser::Push_constant_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPush_constant_block(this);
}


std::any GLSLParser::Push_constant_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitPush_constant_block(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Push_constant_blockContext* GLSLParser::push_constant_block() {
  Push_constant_blockContext *_localctx = _tracker.createInstance<Push_constant_blockContext>(_ctx, getState());
  enterRule(_localctx, 4, GLSLParser::RulePush_constant_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(GLSLParser::LAYOUT);
    setState(97);
    match(GLSLParser::LEFT_PAREN);
    setState(98);
    match(GLSLParser::T__0);
    setState(99);
    match(GLSLParser::RIGHT_PAREN);
    setState(100);
    match(GLSLParser::UNIFORM);
    setState(101);
    match(GLSLParser::IDENTIFIER);
    setState(102);
    match(GLSLParser::LEFT_BRACE);
    setState(104); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(103);
      struct_variable_declaration();
      setState(106); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & -2097183) != 0) || ((((_la - 127) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 127)) & 17592186045439) != 0));
    setState(108);
    match(GLSLParser::RIGHT_BRACE);
    setState(109);
    push_constant_object();
    setState(110);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_uniform_blockContext ------------------------------------------------------------------

GLSLParser::Shader_uniform_blockContext::Shader_uniform_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Layout_declarationContext* GLSLParser::Shader_uniform_blockContext::layout_declaration() {
  return getRuleContext<GLSLParser::Layout_declarationContext>(0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_blockContext::UNIFORM() {
  return getToken(GLSLParser::UNIFORM, 0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_blockContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_blockContext::LEFT_BRACE() {
  return getToken(GLSLParser::LEFT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_blockContext::RIGHT_BRACE() {
  return getToken(GLSLParser::RIGHT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_blockContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}

std::vector<GLSLParser::Struct_variable_declarationContext *> GLSLParser::Shader_uniform_blockContext::struct_variable_declaration() {
  return getRuleContexts<GLSLParser::Struct_variable_declarationContext>();
}

GLSLParser::Struct_variable_declarationContext* GLSLParser::Shader_uniform_blockContext::struct_variable_declaration(size_t i) {
  return getRuleContext<GLSLParser::Struct_variable_declarationContext>(i);
}

GLSLParser::Shader_uniform_objectContext* GLSLParser::Shader_uniform_blockContext::shader_uniform_object() {
  return getRuleContext<GLSLParser::Shader_uniform_objectContext>(0);
}


size_t GLSLParser::Shader_uniform_blockContext::getRuleIndex() const {
  return GLSLParser::RuleShader_uniform_block;
}

void GLSLParser::Shader_uniform_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_uniform_block(this);
}

void GLSLParser::Shader_uniform_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_uniform_block(this);
}


std::any GLSLParser::Shader_uniform_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_uniform_block(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_uniform_blockContext* GLSLParser::shader_uniform_block() {
  Shader_uniform_blockContext *_localctx = _tracker.createInstance<Shader_uniform_blockContext>(_ctx, getState());
  enterRule(_localctx, 6, GLSLParser::RuleShader_uniform_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    layout_declaration();
    setState(113);
    match(GLSLParser::UNIFORM);
    setState(114);
    match(GLSLParser::IDENTIFIER);
    setState(115);
    match(GLSLParser::LEFT_BRACE);

    setState(117); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(116);
      struct_variable_declaration();
      setState(119); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & -2097183) != 0) || ((((_la - 127) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 127)) & 17592186045439) != 0));
    setState(121);
    match(GLSLParser::RIGHT_BRACE);

    setState(123);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GLSLParser::IDENTIFIER) {
      setState(122);
      shader_uniform_object();
    }
    setState(125);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_uniform_singleContext ------------------------------------------------------------------

GLSLParser::Shader_uniform_singleContext::Shader_uniform_singleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Layout_declarationContext* GLSLParser::Shader_uniform_singleContext::layout_declaration() {
  return getRuleContext<GLSLParser::Layout_declarationContext>(0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_singleContext::UNIFORM() {
  return getToken(GLSLParser::UNIFORM, 0);
}

GLSLParser::Variable_typeContext* GLSLParser::Shader_uniform_singleContext::variable_type() {
  return getRuleContext<GLSLParser::Variable_typeContext>(0);
}

GLSLParser::Shader_uniform_objectContext* GLSLParser::Shader_uniform_singleContext::shader_uniform_object() {
  return getRuleContext<GLSLParser::Shader_uniform_objectContext>(0);
}

tree::TerminalNode* GLSLParser::Shader_uniform_singleContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}


size_t GLSLParser::Shader_uniform_singleContext::getRuleIndex() const {
  return GLSLParser::RuleShader_uniform_single;
}

void GLSLParser::Shader_uniform_singleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_uniform_single(this);
}

void GLSLParser::Shader_uniform_singleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_uniform_single(this);
}


std::any GLSLParser::Shader_uniform_singleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_uniform_single(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_uniform_singleContext* GLSLParser::shader_uniform_single() {
  Shader_uniform_singleContext *_localctx = _tracker.createInstance<Shader_uniform_singleContext>(_ctx, getState());
  enterRule(_localctx, 8, GLSLParser::RuleShader_uniform_single);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    layout_declaration();
    setState(128);
    match(GLSLParser::UNIFORM);
    setState(129);
    variable_type();
    setState(130);
    shader_uniform_object();
    setState(131);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_io_variableContext ------------------------------------------------------------------

GLSLParser::Shader_io_variableContext::Shader_io_variableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Layout_declarationContext* GLSLParser::Shader_io_variableContext::layout_declaration() {
  return getRuleContext<GLSLParser::Layout_declarationContext>(0);
}

GLSLParser::Shader_io_specifiersContext* GLSLParser::Shader_io_variableContext::shader_io_specifiers() {
  return getRuleContext<GLSLParser::Shader_io_specifiersContext>(0);
}

GLSLParser::Variable_typeContext* GLSLParser::Shader_io_variableContext::variable_type() {
  return getRuleContext<GLSLParser::Variable_typeContext>(0);
}

tree::TerminalNode* GLSLParser::Shader_io_variableContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

tree::TerminalNode* GLSLParser::Shader_io_variableContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}


size_t GLSLParser::Shader_io_variableContext::getRuleIndex() const {
  return GLSLParser::RuleShader_io_variable;
}

void GLSLParser::Shader_io_variableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_io_variable(this);
}

void GLSLParser::Shader_io_variableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_io_variable(this);
}


std::any GLSLParser::Shader_io_variableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_io_variable(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_io_variableContext* GLSLParser::shader_io_variable() {
  Shader_io_variableContext *_localctx = _tracker.createInstance<Shader_io_variableContext>(_ctx, getState());
  enterRule(_localctx, 10, GLSLParser::RuleShader_io_variable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    layout_declaration();
    setState(134);
    shader_io_specifiers();
    setState(135);
    variable_type();
    setState(136);
    match(GLSLParser::IDENTIFIER);
    setState(137);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_struct_declarationContext ------------------------------------------------------------------

GLSLParser::Shader_struct_declarationContext::Shader_struct_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Shader_struct_declarationContext::STRUCT() {
  return getToken(GLSLParser::STRUCT, 0);
}

GLSLParser::Struct_type_nameContext* GLSLParser::Shader_struct_declarationContext::struct_type_name() {
  return getRuleContext<GLSLParser::Struct_type_nameContext>(0);
}

tree::TerminalNode* GLSLParser::Shader_struct_declarationContext::LEFT_BRACE() {
  return getToken(GLSLParser::LEFT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Shader_struct_declarationContext::RIGHT_BRACE() {
  return getToken(GLSLParser::RIGHT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Shader_struct_declarationContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}

std::vector<GLSLParser::Struct_variable_declarationContext *> GLSLParser::Shader_struct_declarationContext::struct_variable_declaration() {
  return getRuleContexts<GLSLParser::Struct_variable_declarationContext>();
}

GLSLParser::Struct_variable_declarationContext* GLSLParser::Shader_struct_declarationContext::struct_variable_declaration(size_t i) {
  return getRuleContext<GLSLParser::Struct_variable_declarationContext>(i);
}


size_t GLSLParser::Shader_struct_declarationContext::getRuleIndex() const {
  return GLSLParser::RuleShader_struct_declaration;
}

void GLSLParser::Shader_struct_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_struct_declaration(this);
}

void GLSLParser::Shader_struct_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_struct_declaration(this);
}


std::any GLSLParser::Shader_struct_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_struct_declaration(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_struct_declarationContext* GLSLParser::shader_struct_declaration() {
  Shader_struct_declarationContext *_localctx = _tracker.createInstance<Shader_struct_declarationContext>(_ctx, getState());
  enterRule(_localctx, 12, GLSLParser::RuleShader_struct_declaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(GLSLParser::STRUCT);
    setState(140);
    struct_type_name();
    setState(141);
    match(GLSLParser::LEFT_BRACE);

    setState(143); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(142);
      struct_variable_declaration();
      setState(145); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & -2097183) != 0) || ((((_la - 127) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 127)) & 17592186045439) != 0));
    setState(147);
    match(GLSLParser::RIGHT_BRACE);
    setState(148);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_io_specifiersContext ------------------------------------------------------------------

GLSLParser::Shader_io_specifiersContext::Shader_io_specifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Shader_io_specifiersContext::IN() {
  return getToken(GLSLParser::IN, 0);
}

tree::TerminalNode* GLSLParser::Shader_io_specifiersContext::OUT() {
  return getToken(GLSLParser::OUT, 0);
}

tree::TerminalNode* GLSLParser::Shader_io_specifiersContext::FLAT() {
  return getToken(GLSLParser::FLAT, 0);
}


size_t GLSLParser::Shader_io_specifiersContext::getRuleIndex() const {
  return GLSLParser::RuleShader_io_specifiers;
}

void GLSLParser::Shader_io_specifiersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_io_specifiers(this);
}

void GLSLParser::Shader_io_specifiersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_io_specifiers(this);
}


std::any GLSLParser::Shader_io_specifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_io_specifiers(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_io_specifiersContext* GLSLParser::shader_io_specifiers() {
  Shader_io_specifiersContext *_localctx = _tracker.createInstance<Shader_io_specifiersContext>(_ctx, getState());
  enterRule(_localctx, 14, GLSLParser::RuleShader_io_specifiers);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    _la = _input->LA(1);
    if (!(_la == GLSLParser::IN

    || _la == GLSLParser::OUT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }

    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GLSLParser::FLAT) {
      setState(151);
      match(GLSLParser::FLAT);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_type_nameContext ------------------------------------------------------------------

GLSLParser::Struct_type_nameContext::Struct_type_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Struct_type_nameContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Struct_type_nameContext::getRuleIndex() const {
  return GLSLParser::RuleStruct_type_name;
}

void GLSLParser::Struct_type_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_type_name(this);
}

void GLSLParser::Struct_type_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_type_name(this);
}


std::any GLSLParser::Struct_type_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitStruct_type_name(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Struct_type_nameContext* GLSLParser::struct_type_name() {
  Struct_type_nameContext *_localctx = _tracker.createInstance<Struct_type_nameContext>(_ctx, getState());
  enterRule(_localctx, 16, GLSLParser::RuleStruct_type_name);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(GLSLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_uniform_objectContext ------------------------------------------------------------------

GLSLParser::Shader_uniform_objectContext::Shader_uniform_objectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Shader_uniform_objectContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

GLSLParser::Array_specifierContext* GLSLParser::Shader_uniform_objectContext::array_specifier() {
  return getRuleContext<GLSLParser::Array_specifierContext>(0);
}


size_t GLSLParser::Shader_uniform_objectContext::getRuleIndex() const {
  return GLSLParser::RuleShader_uniform_object;
}

void GLSLParser::Shader_uniform_objectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_uniform_object(this);
}

void GLSLParser::Shader_uniform_objectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_uniform_object(this);
}


std::any GLSLParser::Shader_uniform_objectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitShader_uniform_object(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Shader_uniform_objectContext* GLSLParser::shader_uniform_object() {
  Shader_uniform_objectContext *_localctx = _tracker.createInstance<Shader_uniform_objectContext>(_ctx, getState());
  enterRule(_localctx, 18, GLSLParser::RuleShader_uniform_object);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(GLSLParser::IDENTIFIER);
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GLSLParser::LEFT_BRACKET) {
      setState(157);
      array_specifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Push_constant_objectContext ------------------------------------------------------------------

GLSLParser::Push_constant_objectContext::Push_constant_objectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Push_constant_objectContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Push_constant_objectContext::getRuleIndex() const {
  return GLSLParser::RulePush_constant_object;
}

void GLSLParser::Push_constant_objectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPush_constant_object(this);
}

void GLSLParser::Push_constant_objectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPush_constant_object(this);
}


std::any GLSLParser::Push_constant_objectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitPush_constant_object(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Push_constant_objectContext* GLSLParser::push_constant_object() {
  Push_constant_objectContext *_localctx = _tracker.createInstance<Push_constant_objectContext>(_ctx, getState());
  enterRule(_localctx, 20, GLSLParser::RulePush_constant_object);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(GLSLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Directive_nameContext ------------------------------------------------------------------

GLSLParser::Directive_nameContext::Directive_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Directive_nameContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Directive_nameContext::getRuleIndex() const {
  return GLSLParser::RuleDirective_name;
}

void GLSLParser::Directive_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirective_name(this);
}

void GLSLParser::Directive_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirective_name(this);
}


std::any GLSLParser::Directive_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitDirective_name(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Directive_nameContext* GLSLParser::directive_name() {
  Directive_nameContext *_localctx = _tracker.createInstance<Directive_nameContext>(_ctx, getState());
  enterRule(_localctx, 22, GLSLParser::RuleDirective_name);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(GLSLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Directive_valueContext ------------------------------------------------------------------

GLSLParser::Directive_valueContext::Directive_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> GLSLParser::Directive_valueContext::INTCONSTANT() {
  return getTokens(GLSLParser::INTCONSTANT);
}

tree::TerminalNode* GLSLParser::Directive_valueContext::INTCONSTANT(size_t i) {
  return getToken(GLSLParser::INTCONSTANT, i);
}

std::vector<tree::TerminalNode *> GLSLParser::Directive_valueContext::FLOATCONSTANT() {
  return getTokens(GLSLParser::FLOATCONSTANT);
}

tree::TerminalNode* GLSLParser::Directive_valueContext::FLOATCONSTANT(size_t i) {
  return getToken(GLSLParser::FLOATCONSTANT, i);
}

std::vector<tree::TerminalNode *> GLSLParser::Directive_valueContext::STRING_LITERAL() {
  return getTokens(GLSLParser::STRING_LITERAL);
}

tree::TerminalNode* GLSLParser::Directive_valueContext::STRING_LITERAL(size_t i) {
  return getToken(GLSLParser::STRING_LITERAL, i);
}

std::vector<tree::TerminalNode *> GLSLParser::Directive_valueContext::IDENTIFIER() {
  return getTokens(GLSLParser::IDENTIFIER);
}

tree::TerminalNode* GLSLParser::Directive_valueContext::IDENTIFIER(size_t i) {
  return getToken(GLSLParser::IDENTIFIER, i);
}


size_t GLSLParser::Directive_valueContext::getRuleIndex() const {
  return GLSLParser::RuleDirective_value;
}

void GLSLParser::Directive_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirective_value(this);
}

void GLSLParser::Directive_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirective_value(this);
}


std::any GLSLParser::Directive_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitDirective_value(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Directive_valueContext* GLSLParser::directive_value() {
  Directive_valueContext *_localctx = _tracker.createInstance<Directive_valueContext>(_ctx, getState());
  enterRule(_localctx, 24, GLSLParser::RuleDirective_value);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(167);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(164);
        _la = _input->LA(1);
        if (!(((((_la - 11) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 11)) & 27021597764222977) != 0) || _la == GLSLParser::IDENTIFIER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(169);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_variable_declarationContext ------------------------------------------------------------------

GLSLParser::Struct_variable_declarationContext::Struct_variable_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Variable_typeContext* GLSLParser::Struct_variable_declarationContext::variable_type() {
  return getRuleContext<GLSLParser::Variable_typeContext>(0);
}

tree::TerminalNode* GLSLParser::Struct_variable_declarationContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

tree::TerminalNode* GLSLParser::Struct_variable_declarationContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}


size_t GLSLParser::Struct_variable_declarationContext::getRuleIndex() const {
  return GLSLParser::RuleStruct_variable_declaration;
}

void GLSLParser::Struct_variable_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_variable_declaration(this);
}

void GLSLParser::Struct_variable_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_variable_declaration(this);
}


std::any GLSLParser::Struct_variable_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitStruct_variable_declaration(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Struct_variable_declarationContext* GLSLParser::struct_variable_declaration() {
  Struct_variable_declarationContext *_localctx = _tracker.createInstance<Struct_variable_declarationContext>(_ctx, getState());
  enterRule(_localctx, 26, GLSLParser::RuleStruct_variable_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    variable_type();
    setState(171);
    match(GLSLParser::IDENTIFIER);
    setState(172);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Struct_primitive_declarationContext ------------------------------------------------------------------

GLSLParser::Struct_primitive_declarationContext::Struct_primitive_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Primitive_typeContext* GLSLParser::Struct_primitive_declarationContext::primitive_type() {
  return getRuleContext<GLSLParser::Primitive_typeContext>(0);
}

tree::TerminalNode* GLSLParser::Struct_primitive_declarationContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}

tree::TerminalNode* GLSLParser::Struct_primitive_declarationContext::SEMICOLON() {
  return getToken(GLSLParser::SEMICOLON, 0);
}


size_t GLSLParser::Struct_primitive_declarationContext::getRuleIndex() const {
  return GLSLParser::RuleStruct_primitive_declaration;
}

void GLSLParser::Struct_primitive_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStruct_primitive_declaration(this);
}

void GLSLParser::Struct_primitive_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStruct_primitive_declaration(this);
}


std::any GLSLParser::Struct_primitive_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitStruct_primitive_declaration(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Struct_primitive_declarationContext* GLSLParser::struct_primitive_declaration() {
  Struct_primitive_declarationContext *_localctx = _tracker.createInstance<Struct_primitive_declarationContext>(_ctx, getState());
  enterRule(_localctx, 28, GLSLParser::RuleStruct_primitive_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    primitive_type();
    setState(175);
    match(GLSLParser::IDENTIFIER);
    setState(176);
    match(GLSLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_declarationContext ------------------------------------------------------------------

GLSLParser::Function_declarationContext::Function_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Function_return_typeContext* GLSLParser::Function_declarationContext::function_return_type() {
  return getRuleContext<GLSLParser::Function_return_typeContext>(0);
}

GLSLParser::Function_nameContext* GLSLParser::Function_declarationContext::function_name() {
  return getRuleContext<GLSLParser::Function_nameContext>(0);
}

tree::TerminalNode* GLSLParser::Function_declarationContext::LEFT_PAREN() {
  return getToken(GLSLParser::LEFT_PAREN, 0);
}

tree::TerminalNode* GLSLParser::Function_declarationContext::RIGHT_PAREN() {
  return getToken(GLSLParser::RIGHT_PAREN, 0);
}

GLSLParser::Function_bodyContext* GLSLParser::Function_declarationContext::function_body() {
  return getRuleContext<GLSLParser::Function_bodyContext>(0);
}

GLSLParser::Function_parametersContext* GLSLParser::Function_declarationContext::function_parameters() {
  return getRuleContext<GLSLParser::Function_parametersContext>(0);
}


size_t GLSLParser::Function_declarationContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_declaration;
}

void GLSLParser::Function_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_declaration(this);
}

void GLSLParser::Function_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_declaration(this);
}


std::any GLSLParser::Function_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_declaration(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_declarationContext* GLSLParser::function_declaration() {
  Function_declarationContext *_localctx = _tracker.createInstance<Function_declarationContext>(_ctx, getState());
  enterRule(_localctx, 30, GLSLParser::RuleFunction_declaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    function_return_type();
    setState(179);
    function_name();
    setState(180);
    match(GLSLParser::LEFT_PAREN);
    setState(182);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & -2097183) != 0) || ((((_la - 127) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 127)) & 17592186045439) != 0)) {
      setState(181);
      function_parameters();
    }
    setState(184);
    match(GLSLParser::RIGHT_PAREN);
    setState(185);
    function_body();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_nameContext ------------------------------------------------------------------

GLSLParser::Function_nameContext::Function_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Function_nameContext::MAIN() {
  return getToken(GLSLParser::MAIN, 0);
}

tree::TerminalNode* GLSLParser::Function_nameContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Function_nameContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_name;
}

void GLSLParser::Function_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_name(this);
}

void GLSLParser::Function_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_name(this);
}


std::any GLSLParser::Function_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_name(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_nameContext* GLSLParser::function_name() {
  Function_nameContext *_localctx = _tracker.createInstance<Function_nameContext>(_ctx, getState());
  enterRule(_localctx, 32, GLSLParser::RuleFunction_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    _la = _input->LA(1);
    if (!(_la == GLSLParser::MAIN || _la == GLSLParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_return_typeContext ------------------------------------------------------------------

GLSLParser::Function_return_typeContext::Function_return_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Variable_typeContext* GLSLParser::Function_return_typeContext::variable_type() {
  return getRuleContext<GLSLParser::Variable_typeContext>(0);
}


size_t GLSLParser::Function_return_typeContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_return_type;
}

void GLSLParser::Function_return_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_return_type(this);
}

void GLSLParser::Function_return_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_return_type(this);
}


std::any GLSLParser::Function_return_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_return_type(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_return_typeContext* GLSLParser::function_return_type() {
  Function_return_typeContext *_localctx = _tracker.createInstance<Function_return_typeContext>(_ctx, getState());
  enterRule(_localctx, 34, GLSLParser::RuleFunction_return_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    variable_type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_parametersContext ------------------------------------------------------------------

GLSLParser::Function_parametersContext::Function_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GLSLParser::Function_parameterContext *> GLSLParser::Function_parametersContext::function_parameter() {
  return getRuleContexts<GLSLParser::Function_parameterContext>();
}

GLSLParser::Function_parameterContext* GLSLParser::Function_parametersContext::function_parameter(size_t i) {
  return getRuleContext<GLSLParser::Function_parameterContext>(i);
}

std::vector<tree::TerminalNode *> GLSLParser::Function_parametersContext::COMMA() {
  return getTokens(GLSLParser::COMMA);
}

tree::TerminalNode* GLSLParser::Function_parametersContext::COMMA(size_t i) {
  return getToken(GLSLParser::COMMA, i);
}


size_t GLSLParser::Function_parametersContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_parameters;
}

void GLSLParser::Function_parametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_parameters(this);
}

void GLSLParser::Function_parametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_parameters(this);
}


std::any GLSLParser::Function_parametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_parameters(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_parametersContext* GLSLParser::function_parameters() {
  Function_parametersContext *_localctx = _tracker.createInstance<Function_parametersContext>(_ctx, getState());
  enterRule(_localctx, 36, GLSLParser::RuleFunction_parameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    function_parameter();
    setState(196);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GLSLParser::COMMA) {
      setState(192);
      match(GLSLParser::COMMA);
      setState(193);
      function_parameter();
      setState(198);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_parameterContext ------------------------------------------------------------------

GLSLParser::Function_parameterContext::Function_parameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Variable_typeContext* GLSLParser::Function_parameterContext::variable_type() {
  return getRuleContext<GLSLParser::Variable_typeContext>(0);
}

tree::TerminalNode* GLSLParser::Function_parameterContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Function_parameterContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_parameter;
}

void GLSLParser::Function_parameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_parameter(this);
}

void GLSLParser::Function_parameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_parameter(this);
}


std::any GLSLParser::Function_parameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_parameter(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_parameterContext* GLSLParser::function_parameter() {
  Function_parameterContext *_localctx = _tracker.createInstance<Function_parameterContext>(_ctx, getState());
  enterRule(_localctx, 38, GLSLParser::RuleFunction_parameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    variable_type();
    setState(200);
    match(GLSLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_bodyContext ------------------------------------------------------------------

GLSLParser::Function_bodyContext::Function_bodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Function_bodyContext::LEFT_BRACE() {
  return getToken(GLSLParser::LEFT_BRACE, 0);
}

tree::TerminalNode* GLSLParser::Function_bodyContext::RIGHT_BRACE() {
  return getToken(GLSLParser::RIGHT_BRACE, 0);
}


size_t GLSLParser::Function_bodyContext::getRuleIndex() const {
  return GLSLParser::RuleFunction_body;
}

void GLSLParser::Function_bodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_body(this);
}

void GLSLParser::Function_bodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_body(this);
}


std::any GLSLParser::Function_bodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitFunction_body(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Function_bodyContext* GLSLParser::function_body() {
  Function_bodyContext *_localctx = _tracker.createInstance<Function_bodyContext>(_ctx, getState());
  enterRule(_localctx, 40, GLSLParser::RuleFunction_body);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(202);
    match(GLSLParser::LEFT_BRACE);
    setState(206);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(203);
        matchWildcard(); 
      }
      setState(208);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(209);
    match(GLSLParser::RIGHT_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_declarationContext ------------------------------------------------------------------

GLSLParser::Layout_declarationContext::Layout_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Layout_declarationContext::LAYOUT() {
  return getToken(GLSLParser::LAYOUT, 0);
}

tree::TerminalNode* GLSLParser::Layout_declarationContext::LEFT_PAREN() {
  return getToken(GLSLParser::LEFT_PAREN, 0);
}

GLSLParser::Layout_qualifiersContext* GLSLParser::Layout_declarationContext::layout_qualifiers() {
  return getRuleContext<GLSLParser::Layout_qualifiersContext>(0);
}

tree::TerminalNode* GLSLParser::Layout_declarationContext::RIGHT_PAREN() {
  return getToken(GLSLParser::RIGHT_PAREN, 0);
}


size_t GLSLParser::Layout_declarationContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_declaration;
}

void GLSLParser::Layout_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_declaration(this);
}

void GLSLParser::Layout_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_declaration(this);
}


std::any GLSLParser::Layout_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_declaration(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_declarationContext* GLSLParser::layout_declaration() {
  Layout_declarationContext *_localctx = _tracker.createInstance<Layout_declarationContext>(_ctx, getState());
  enterRule(_localctx, 42, GLSLParser::RuleLayout_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(GLSLParser::LAYOUT);
    setState(212);
    match(GLSLParser::LEFT_PAREN);
    setState(213);
    layout_qualifiers();
    setState(214);
    match(GLSLParser::RIGHT_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_qualifiersContext ------------------------------------------------------------------

GLSLParser::Layout_qualifiersContext::Layout_qualifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<GLSLParser::Layout_qualifierContext *> GLSLParser::Layout_qualifiersContext::layout_qualifier() {
  return getRuleContexts<GLSLParser::Layout_qualifierContext>();
}

GLSLParser::Layout_qualifierContext* GLSLParser::Layout_qualifiersContext::layout_qualifier(size_t i) {
  return getRuleContext<GLSLParser::Layout_qualifierContext>(i);
}

std::vector<tree::TerminalNode *> GLSLParser::Layout_qualifiersContext::COMMA() {
  return getTokens(GLSLParser::COMMA);
}

tree::TerminalNode* GLSLParser::Layout_qualifiersContext::COMMA(size_t i) {
  return getToken(GLSLParser::COMMA, i);
}


size_t GLSLParser::Layout_qualifiersContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_qualifiers;
}

void GLSLParser::Layout_qualifiersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_qualifiers(this);
}

void GLSLParser::Layout_qualifiersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_qualifiers(this);
}


std::any GLSLParser::Layout_qualifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_qualifiers(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_qualifiersContext* GLSLParser::layout_qualifiers() {
  Layout_qualifiersContext *_localctx = _tracker.createInstance<Layout_qualifiersContext>(_ctx, getState());
  enterRule(_localctx, 44, GLSLParser::RuleLayout_qualifiers);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    layout_qualifier();
    setState(221);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GLSLParser::COMMA) {
      setState(217);
      match(GLSLParser::COMMA);
      setState(218);
      layout_qualifier();
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_qualifierContext ------------------------------------------------------------------

GLSLParser::Layout_qualifierContext::Layout_qualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Layout_qualifier_typeContext* GLSLParser::Layout_qualifierContext::layout_qualifier_type() {
  return getRuleContext<GLSLParser::Layout_qualifier_typeContext>(0);
}

tree::TerminalNode* GLSLParser::Layout_qualifierContext::EQUAL() {
  return getToken(GLSLParser::EQUAL, 0);
}

GLSLParser::Layout_qualifier_valueContext* GLSLParser::Layout_qualifierContext::layout_qualifier_value() {
  return getRuleContext<GLSLParser::Layout_qualifier_valueContext>(0);
}


size_t GLSLParser::Layout_qualifierContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_qualifier;
}

void GLSLParser::Layout_qualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_qualifier(this);
}

void GLSLParser::Layout_qualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_qualifier(this);
}


std::any GLSLParser::Layout_qualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_qualifier(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_qualifierContext* GLSLParser::layout_qualifier() {
  Layout_qualifierContext *_localctx = _tracker.createInstance<Layout_qualifierContext>(_ctx, getState());
  enterRule(_localctx, 46, GLSLParser::RuleLayout_qualifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(224);
    layout_qualifier_type();
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GLSLParser::EQUAL) {
      setState(225);
      match(GLSLParser::EQUAL);
      setState(226);
      layout_qualifier_value();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_qualifier_valueContext ------------------------------------------------------------------

GLSLParser::Layout_qualifier_valueContext::Layout_qualifier_valueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Layout_qualifier_valueContext::INTCONSTANT() {
  return getToken(GLSLParser::INTCONSTANT, 0);
}


size_t GLSLParser::Layout_qualifier_valueContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_qualifier_value;
}

void GLSLParser::Layout_qualifier_valueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_qualifier_value(this);
}

void GLSLParser::Layout_qualifier_valueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_qualifier_value(this);
}


std::any GLSLParser::Layout_qualifier_valueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_qualifier_value(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_qualifier_valueContext* GLSLParser::layout_qualifier_value() {
  Layout_qualifier_valueContext *_localctx = _tracker.createInstance<Layout_qualifier_valueContext>(_ctx, getState());
  enterRule(_localctx, 48, GLSLParser::RuleLayout_qualifier_value);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    match(GLSLParser::INTCONSTANT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_qualifier_typeContext ------------------------------------------------------------------

GLSLParser::Layout_qualifier_typeContext::Layout_qualifier_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Layout_std_qualifierContext* GLSLParser::Layout_qualifier_typeContext::layout_std_qualifier() {
  return getRuleContext<GLSLParser::Layout_std_qualifierContext>(0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::LOCATION() {
  return getToken(GLSLParser::LOCATION, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::COMPONENT() {
  return getToken(GLSLParser::COMPONENT, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::BINDING() {
  return getToken(GLSLParser::BINDING, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::SET() {
  return getToken(GLSLParser::SET, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::INDEX() {
  return getToken(GLSLParser::INDEX, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::OFFSET() {
  return getToken(GLSLParser::OFFSET, 0);
}

tree::TerminalNode* GLSLParser::Layout_qualifier_typeContext::IDENTIFIER() {
  return getToken(GLSLParser::IDENTIFIER, 0);
}


size_t GLSLParser::Layout_qualifier_typeContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_qualifier_type;
}

void GLSLParser::Layout_qualifier_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_qualifier_type(this);
}

void GLSLParser::Layout_qualifier_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_qualifier_type(this);
}


std::any GLSLParser::Layout_qualifier_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_qualifier_type(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_qualifier_typeContext* GLSLParser::layout_qualifier_type() {
  Layout_qualifier_typeContext *_localctx = _tracker.createInstance<Layout_qualifier_typeContext>(_ctx, getState());
  enterRule(_localctx, 50, GLSLParser::RuleLayout_qualifier_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GLSLParser::STD: {
        setState(231);
        layout_std_qualifier();
        break;
      }

      case GLSLParser::LOCATION: {
        setState(232);
        match(GLSLParser::LOCATION);
        break;
      }

      case GLSLParser::COMPONENT: {
        setState(233);
        match(GLSLParser::COMPONENT);
        break;
      }

      case GLSLParser::BINDING: {
        setState(234);
        match(GLSLParser::BINDING);
        break;
      }

      case GLSLParser::SET: {
        setState(235);
        match(GLSLParser::SET);
        break;
      }

      case GLSLParser::INDEX: {
        setState(236);
        match(GLSLParser::INDEX);
        break;
      }

      case GLSLParser::OFFSET: {
        setState(237);
        match(GLSLParser::OFFSET);
        break;
      }

      case GLSLParser::IDENTIFIER: {
        setState(238);
        match(GLSLParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Layout_std_qualifierContext ------------------------------------------------------------------

GLSLParser::Layout_std_qualifierContext::Layout_std_qualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Layout_std_qualifierContext::STD() {
  return getToken(GLSLParser::STD, 0);
}

tree::TerminalNode* GLSLParser::Layout_std_qualifierContext::INTCONSTANT() {
  return getToken(GLSLParser::INTCONSTANT, 0);
}


size_t GLSLParser::Layout_std_qualifierContext::getRuleIndex() const {
  return GLSLParser::RuleLayout_std_qualifier;
}

void GLSLParser::Layout_std_qualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLayout_std_qualifier(this);
}

void GLSLParser::Layout_std_qualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLayout_std_qualifier(this);
}


std::any GLSLParser::Layout_std_qualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitLayout_std_qualifier(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Layout_std_qualifierContext* GLSLParser::layout_std_qualifier() {
  Layout_std_qualifierContext *_localctx = _tracker.createInstance<Layout_std_qualifierContext>(_ctx, getState());
  enterRule(_localctx, 52, GLSLParser::RuleLayout_std_qualifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(GLSLParser::STD);
    setState(242);
    match(GLSLParser::INTCONSTANT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_specifierContext ------------------------------------------------------------------

GLSLParser::Array_specifierContext::Array_specifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Array_specifierContext::LEFT_BRACKET() {
  return getToken(GLSLParser::LEFT_BRACKET, 0);
}

tree::TerminalNode* GLSLParser::Array_specifierContext::INTCONSTANT() {
  return getToken(GLSLParser::INTCONSTANT, 0);
}

tree::TerminalNode* GLSLParser::Array_specifierContext::RIGHT_BRACKET() {
  return getToken(GLSLParser::RIGHT_BRACKET, 0);
}


size_t GLSLParser::Array_specifierContext::getRuleIndex() const {
  return GLSLParser::RuleArray_specifier;
}

void GLSLParser::Array_specifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray_specifier(this);
}

void GLSLParser::Array_specifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray_specifier(this);
}


std::any GLSLParser::Array_specifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitArray_specifier(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Array_specifierContext* GLSLParser::array_specifier() {
  Array_specifierContext *_localctx = _tracker.createInstance<Array_specifierContext>(_ctx, getState());
  enterRule(_localctx, 54, GLSLParser::RuleArray_specifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(GLSLParser::LEFT_BRACKET);
    setState(245);
    match(GLSLParser::INTCONSTANT);
    setState(246);
    match(GLSLParser::RIGHT_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_typeContext ------------------------------------------------------------------

GLSLParser::Variable_typeContext::Variable_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GLSLParser::Primitive_typeContext* GLSLParser::Variable_typeContext::primitive_type() {
  return getRuleContext<GLSLParser::Primitive_typeContext>(0);
}

GLSLParser::Struct_type_nameContext* GLSLParser::Variable_typeContext::struct_type_name() {
  return getRuleContext<GLSLParser::Struct_type_nameContext>(0);
}


size_t GLSLParser::Variable_typeContext::getRuleIndex() const {
  return GLSLParser::RuleVariable_type;
}

void GLSLParser::Variable_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_type(this);
}

void GLSLParser::Variable_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_type(this);
}


std::any GLSLParser::Variable_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitVariable_type(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Variable_typeContext* GLSLParser::variable_type() {
  Variable_typeContext *_localctx = _tracker.createInstance<Variable_typeContext>(_ctx, getState());
  enterRule(_localctx, 56, GLSLParser::RuleVariable_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GLSLParser::VOID:
      case GLSLParser::FLOAT:
      case GLSLParser::DOUBLE:
      case GLSLParser::INT:
      case GLSLParser::UINT:
      case GLSLParser::BOOL:
      case GLSLParser::VEC2:
      case GLSLParser::VEC3:
      case GLSLParser::VEC4:
      case GLSLParser::DVEC2:
      case GLSLParser::DVEC3:
      case GLSLParser::DVEC4:
      case GLSLParser::BVEC2:
      case GLSLParser::BVEC3:
      case GLSLParser::BVEC4:
      case GLSLParser::IVEC2:
      case GLSLParser::IVEC3:
      case GLSLParser::UVEC2:
      case GLSLParser::UVEC3:
      case GLSLParser::UVEC4:
      case GLSLParser::MAT2X2:
      case GLSLParser::MAT2X3:
      case GLSLParser::MAT2X4:
      case GLSLParser::MAT3X2:
      case GLSLParser::MAT3X3:
      case GLSLParser::MAT3X4:
      case GLSLParser::MAT4X2:
      case GLSLParser::MAT4X3:
      case GLSLParser::MAT4X4:
      case GLSLParser::DMAT2X2:
      case GLSLParser::DMAT2X3:
      case GLSLParser::DMAT2X4:
      case GLSLParser::DMAT3X2:
      case GLSLParser::DMAT3X3:
      case GLSLParser::DMAT3X4:
      case GLSLParser::DMAT4X2:
      case GLSLParser::DMAT4X3:
      case GLSLParser::DMAT4X4:
      case GLSLParser::SAMPLER1D:
      case GLSLParser::SAMPLER1DARRAY:
      case GLSLParser::SAMPLER1DSHADOW:
      case GLSLParser::SAMPLER1DARRAYSHADOW:
      case GLSLParser::SAMPLER2D:
      case GLSLParser::SAMPLER2DARRAY:
      case GLSLParser::SAMPLER2DSHADOW:
      case GLSLParser::SAMPLER2DARRAYSHADOW:
      case GLSLParser::SAMPLERCUBE:
      case GLSLParser::SAMPLERCUBEARRAY:
      case GLSLParser::SAMPLERCUBESHADOW:
      case GLSLParser::SAMPLERCUBEARRAYSHADOW:
      case GLSLParser::SAMPLERBUFFER:
      case GLSLParser::SAMPLER2DRECT:
      case GLSLParser::SAMPLER2DRECTSHADOW:
      case GLSLParser::ISAMPLER1D:
      case GLSLParser::ISAMPLER1DARRAY:
      case GLSLParser::ISAMPLER2D:
      case GLSLParser::ISAMPLER2DARRAY:
      case GLSLParser::ISAMPLERCUBE:
      case GLSLParser::ISAMPLERCUBEARRAY:
      case GLSLParser::ISAMPLERBUFFER:
      case GLSLParser::ISAMPLER2DRECT:
      case GLSLParser::USAMPLER1D:
      case GLSLParser::USAMPLER1DARRAY:
      case GLSLParser::USAMPLER2D:
      case GLSLParser::USAMPLER2DARRAY:
      case GLSLParser::USAMPLERCUBE:
      case GLSLParser::USAMPLERCUBEARRAY:
      case GLSLParser::USAMPLERBUFFER:
      case GLSLParser::USAMPLER2DRECT: {
        setState(248);
        primitive_type();
        break;
      }

      case GLSLParser::IDENTIFIER: {
        setState(249);
        struct_type_name();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Primitive_typeContext ------------------------------------------------------------------

GLSLParser::Primitive_typeContext::Primitive_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::VOID() {
  return getToken(GLSLParser::VOID, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::FLOAT() {
  return getToken(GLSLParser::FLOAT, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::VEC2() {
  return getToken(GLSLParser::VEC2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::VEC3() {
  return getToken(GLSLParser::VEC3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::VEC4() {
  return getToken(GLSLParser::VEC4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::INT() {
  return getToken(GLSLParser::INT, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::IVEC2() {
  return getToken(GLSLParser::IVEC2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::IVEC3() {
  return getToken(GLSLParser::IVEC3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DOUBLE() {
  return getToken(GLSLParser::DOUBLE, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DVEC2() {
  return getToken(GLSLParser::DVEC2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DVEC3() {
  return getToken(GLSLParser::DVEC3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DVEC4() {
  return getToken(GLSLParser::DVEC4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::UINT() {
  return getToken(GLSLParser::UINT, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::UVEC2() {
  return getToken(GLSLParser::UVEC2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::UVEC3() {
  return getToken(GLSLParser::UVEC3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::UVEC4() {
  return getToken(GLSLParser::UVEC4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::BOOL() {
  return getToken(GLSLParser::BOOL, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::BVEC2() {
  return getToken(GLSLParser::BVEC2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::BVEC3() {
  return getToken(GLSLParser::BVEC3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::BVEC4() {
  return getToken(GLSLParser::BVEC4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT2X2() {
  return getToken(GLSLParser::MAT2X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT2X3() {
  return getToken(GLSLParser::MAT2X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT2X4() {
  return getToken(GLSLParser::MAT2X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT3X2() {
  return getToken(GLSLParser::MAT3X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT3X3() {
  return getToken(GLSLParser::MAT3X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT3X4() {
  return getToken(GLSLParser::MAT3X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT4X2() {
  return getToken(GLSLParser::MAT4X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT4X3() {
  return getToken(GLSLParser::MAT4X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::MAT4X4() {
  return getToken(GLSLParser::MAT4X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT2X2() {
  return getToken(GLSLParser::DMAT2X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT2X3() {
  return getToken(GLSLParser::DMAT2X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT2X4() {
  return getToken(GLSLParser::DMAT2X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT3X2() {
  return getToken(GLSLParser::DMAT3X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT3X3() {
  return getToken(GLSLParser::DMAT3X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT3X4() {
  return getToken(GLSLParser::DMAT3X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT4X2() {
  return getToken(GLSLParser::DMAT4X2, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT4X3() {
  return getToken(GLSLParser::DMAT4X3, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::DMAT4X4() {
  return getToken(GLSLParser::DMAT4X4, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER1D() {
  return getToken(GLSLParser::SAMPLER1D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER1DARRAY() {
  return getToken(GLSLParser::SAMPLER1DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER1DSHADOW() {
  return getToken(GLSLParser::SAMPLER1DSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER1DARRAYSHADOW() {
  return getToken(GLSLParser::SAMPLER1DARRAYSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2D() {
  return getToken(GLSLParser::SAMPLER2D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2DARRAY() {
  return getToken(GLSLParser::SAMPLER2DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2DSHADOW() {
  return getToken(GLSLParser::SAMPLER2DSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2DARRAYSHADOW() {
  return getToken(GLSLParser::SAMPLER2DARRAYSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLERCUBE() {
  return getToken(GLSLParser::SAMPLERCUBE, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLERCUBEARRAY() {
  return getToken(GLSLParser::SAMPLERCUBEARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLERCUBESHADOW() {
  return getToken(GLSLParser::SAMPLERCUBESHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLERCUBEARRAYSHADOW() {
  return getToken(GLSLParser::SAMPLERCUBEARRAYSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLERBUFFER() {
  return getToken(GLSLParser::SAMPLERBUFFER, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2DRECT() {
  return getToken(GLSLParser::SAMPLER2DRECT, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::SAMPLER2DRECTSHADOW() {
  return getToken(GLSLParser::SAMPLER2DRECTSHADOW, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLER1D() {
  return getToken(GLSLParser::ISAMPLER1D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLER1DARRAY() {
  return getToken(GLSLParser::ISAMPLER1DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLER2D() {
  return getToken(GLSLParser::ISAMPLER2D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLER2DARRAY() {
  return getToken(GLSLParser::ISAMPLER2DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLERCUBE() {
  return getToken(GLSLParser::ISAMPLERCUBE, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLERCUBEARRAY() {
  return getToken(GLSLParser::ISAMPLERCUBEARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLERBUFFER() {
  return getToken(GLSLParser::ISAMPLERBUFFER, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::ISAMPLER2DRECT() {
  return getToken(GLSLParser::ISAMPLER2DRECT, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLER1D() {
  return getToken(GLSLParser::USAMPLER1D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLER1DARRAY() {
  return getToken(GLSLParser::USAMPLER1DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLER2D() {
  return getToken(GLSLParser::USAMPLER2D, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLER2DARRAY() {
  return getToken(GLSLParser::USAMPLER2DARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLERCUBE() {
  return getToken(GLSLParser::USAMPLERCUBE, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLERCUBEARRAY() {
  return getToken(GLSLParser::USAMPLERCUBEARRAY, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLERBUFFER() {
  return getToken(GLSLParser::USAMPLERBUFFER, 0);
}

tree::TerminalNode* GLSLParser::Primitive_typeContext::USAMPLER2DRECT() {
  return getToken(GLSLParser::USAMPLER2DRECT, 0);
}


size_t GLSLParser::Primitive_typeContext::getRuleIndex() const {
  return GLSLParser::RulePrimitive_type;
}

void GLSLParser::Primitive_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimitive_type(this);
}

void GLSLParser::Primitive_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<GLSLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimitive_type(this);
}


std::any GLSLParser::Primitive_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GLSLVisitor*>(visitor))
    return parserVisitor->visitPrimitive_type(this);
  else
    return visitor->visitChildren(this);
}

GLSLParser::Primitive_typeContext* GLSLParser::primitive_type() {
  Primitive_typeContext *_localctx = _tracker.createInstance<Primitive_typeContext>(_ctx, getState());
  enterRule(_localctx, 58, GLSLParser::RulePrimitive_type);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    _la = _input->LA(1);
    if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & -2097183) != 0) || ((((_la - 127) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 127)) & 1023) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void GLSLParser::initialize() {
  ::antlr4::internal::call_once(glslParserOnceFlag, glslParserInitialize);
}
