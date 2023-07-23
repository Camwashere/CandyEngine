grammar GLSL;

startShader: (preprocessor_directive  (push_constant_block | shader_uniform_block+ | shader_uniform_single+ | shader_io_variable+ | shader_struct_declaration+ | function_declaration+)*);

preprocessor_directive: HASH directive_name directive_value;

push_constant_block: LAYOUT LEFT_PAREN 'push_constant' RIGHT_PAREN UNIFORM IDENTIFIER LEFT_BRACE (struct_variable_declaration)+ RIGHT_BRACE push_constant_object SEMICOLON;

shader_uniform_block: layout_declaration UNIFORM IDENTIFIER LEFT_BRACE (struct_variable_declaration+) RIGHT_BRACE (shader_uniform_object?) SEMICOLON;

shader_uniform_single: layout_declaration UNIFORM variable_type shader_uniform_object SEMICOLON;


shader_io_variable: layout_declaration shader_io_specifiers variable_type IDENTIFIER SEMICOLON;

shader_struct_declaration: STRUCT struct_type_name LEFT_BRACE (struct_variable_declaration+) RIGHT_BRACE SEMICOLON;

shader_io_specifiers: (IN | OUT) (FLAT?);

struct_type_name: IDENTIFIER;

shader_uniform_object: IDENTIFIER array_specifier?;

push_constant_object: IDENTIFIER;

directive_name: IDENTIFIER;

directive_value: (INTCONSTANT | FLOATCONSTANT | STRING_LITERAL | IDENTIFIER)*;

struct_variable_declaration: variable_type IDENTIFIER SEMICOLON;

struct_primitive_declaration: primitive_type IDENTIFIER SEMICOLON;

function_declaration: function_return_type function_name LEFT_PAREN function_parameters? RIGHT_PAREN function_body;

function_name: MAIN | IDENTIFIER;

function_return_type: variable_type;

function_parameters: function_parameter (COMMA function_parameter)*;

function_parameter: variable_type IDENTIFIER;

function_body: LEFT_BRACE .*? RIGHT_BRACE;

layout_declaration: LAYOUT LEFT_PAREN layout_qualifiers RIGHT_PAREN;

layout_qualifiers: layout_qualifier (COMMA layout_qualifier)*;

layout_qualifier: (layout_qualifier_type (EQUAL layout_qualifier_value)?);

layout_qualifier_value: (INTCONSTANT);

layout_qualifier_type: (layout_std_qualifier | LOCATION | COMPONENT | BINDING | INDEX | OFFSET | IDENTIFIER);

layout_std_qualifier: STD INTCONSTANT;

array_specifier: LEFT_BRACKET INTCONSTANT RIGHT_BRACKET;

variable_type: (primitive_type | struct_type_name);

primitive_type: VOID | FLOAT | VEC2 | VEC3 | VEC4 | INT | IVEC2 | IVEC3 | DOUBLE | DVEC2 | DVEC3 | DVEC4
| UINT | UVEC2 | UVEC3 | UVEC4 | BOOL | BVEC2 | BVEC3 | BVEC4 | MAT2X2 | MAT2X3 | MAT2X4 | MAT3X2 | MAT3X3 | MAT3X4 | MAT4X2 | MAT4X3 | MAT4X4
| DMAT2X2 | DMAT2X3 | DMAT2X4 | DMAT3X2 | DMAT3X3 | DMAT3X4 | DMAT4X2 | DMAT4X3 | DMAT4X4
| SAMPLER1D | SAMPLER1DARRAY | SAMPLER1DSHADOW | SAMPLER1DARRAYSHADOW | SAMPLER2D | SAMPLER2DARRAY | SAMPLER2DSHADOW | SAMPLER2DARRAYSHADOW
| SAMPLERCUBE | SAMPLERCUBEARRAY | SAMPLERCUBESHADOW | SAMPLERCUBEARRAYSHADOW | SAMPLERBUFFER | SAMPLER2DRECT | SAMPLER2DRECTSHADOW
| ISAMPLER1D | ISAMPLER1DARRAY | ISAMPLER2D | ISAMPLER2DARRAY | ISAMPLERCUBE | ISAMPLERCUBEARRAY | ISAMPLERBUFFER | ISAMPLER2DRECT
| USAMPLER1D | USAMPLER1DARRAY | USAMPLER2D | USAMPLER2DARRAY | USAMPLERCUBE | USAMPLERCUBEARRAY | USAMPLERBUFFER | USAMPLER2DRECT;

LAYOUT  : 'layout';
LOCATION : 'location';
COMPONENT: 'component';
MAIN  : 'main';
BINDING: 'binding';
INDEX: 'index';
STD: 'std';
OFFSET: 'offset';


STRING_LITERAL : '"' (ESC | ~[\\"])* '"';

fragment ESC : '\\' [btnr"\\];

HASH: '#';

NEWLINE: [\r\n]+->skip;

SPACE: [ ]+->skip;

TAB: [\t]+ ->skip;

LINE_COMMENT: '//' ~[\r\n]* -> skip;

BLOCK_COMMENT: '/*' .*? '*/' -> skip;

SEMICOLON: ';';

COMMA: ',';

EQUAL: '=';

LEFT_PAREN: '(';

RIGHT_PAREN: ')';

LEFT_BRACKET: '[';

RIGHT_BRACKET: ']';

LEFT_BRACE: '{';

RIGHT_BRACE: '}';

DOT: '.';

PLUS: '+';

MINUS: '-';

STAR: '*';

SLASH: '/';

PERCENT: '%';

INC_OP : '++';

DEC_OP : '--';

LEFT_ANGLE : '<';

RIGHT_ANGLE : '>';

LEFT_ANGLE_EQUAL : '<=';

RIGHT_ANGLE_EQUAL : '>=';

VERTICAL_BAR : '|';

CARET : '^';

AMPERSAND : '&';

OR_OP : '||';

XOR_OP : '^^';

AND_OP : '&&';

EQUAL_EQUAL : '==';

BANG_EQUAL : '!=';

LEFT_OP : '<<';

RIGHT_OP : '>>';

QUESTION : '?';

COLON : ':';

BANG : '!';

TILDE : '~';

MUL_ASSIGN : '*=';

DIV_ASSIGN : '/=';

MOD_ASSIGN : '%=';

ADD_ASSIGN : '+=';

SUB_ASSIGN : '-=';

LEFT_ASSIGN : '<<=';

RIGHT_ASSIGN : '>>=';

AND_ASSIGN : '&=';

XOR_ASSIGN : '^=';

OR_ASSIGN : '|=';

VOID : 'void';
FLOATCONSTANT : [0-9]*'.'[0-9]+([eE][+-]?[0-9]+)?;
INTCONSTANT  : '0' | [1-9][0-9]*;
UINTCONSTANT  : [1-9][0-9]*'u';
BOOLCONSTANT  : 'true' | 'false';
FLOAT  : 'float';
DOUBLE  : 'double';
INT  : 'int';
UINT  : 'uint';
BOOL  : 'bool';
VEC2  : 'vec2';
VEC3  : 'vec3';
VEC4  : 'vec4';
DVEC2  : 'dvec2';
DVEC3  : 'dvec3';
DVEC4  : 'dvec4';
BVEC2  : 'bvec2';
BVEC3  : 'bvec3';
BVEC4  : 'bvec4';
IVEC2  : 'ivec2';
IVEC3  : 'ivec3';
IVEC4  : 'ivec4';
UVEC2  : 'uvec2';
UVEC3  : 'uvec3';
UVEC4  : 'uvec4';
MAT2X2  : 'mat2x2' | 'mat2';
MAT2X3  : 'mat2x3';
MAT2X4  : 'mat2x4';
MAT3X2  : 'mat3x2';
MAT3X3  : 'mat3x3' | 'mat3';
MAT3X4  : 'mat3x4';
MAT4X2  : 'mat4x2';
MAT4X3  : 'mat4x3';
MAT4X4  : 'mat4x4' | 'mat4';
DMAT2X2  : 'dmat2x2' | 'dmat2';
DMAT2X3  : 'dmat2x3';
DMAT2X4  : 'dmat2x4';
DMAT3X2  : 'dmat3x2';
DMAT3X3  : 'dmat3x3' | 'dmat3';
DMAT3X4  : 'dmat3x4';
DMAT4X2  : 'dmat4x2';
DMAT4X3  : 'dmat4x3';
DMAT4X4  : 'dmat4x4' | 'dmat4';
SAMPLER1D  : 'sampler1D';
SAMPLER1DARRAY  : 'sampler1DArray';
SAMPLER1DSHADOW  : 'sampler1DShadow';
SAMPLER1DARRAYSHADOW  : 'sampler1DArrayShadow';
SAMPLER2D  : 'sampler2D';
SAMPLER2DARRAY  : 'sampler2DArray';
SAMPLER2DSHADOW  : 'sampler2DShadow';
SAMPLER2DARRAYSHADOW  : 'sampler2DArrayShadow';
SAMPLERCUBE  : 'samplerCube';
SAMPLERCUBEARRAY  : 'samplerCubeArray';
SAMPLERCUBESHADOW  : 'samplerCubeShadow';
SAMPLERCUBEARRAYSHADOW  : 'samplerCubeArrayShadow';
SAMPLERBUFFER  : 'samplerBuffer';
SAMPLER2DRECT  : 'sampler2DRect';
SAMPLER2DRECTSHADOW  : 'sampler2DRectShadow';
ISAMPLER1D  : 'isampler1D';
ISAMPLER1DARRAY  : 'isampler1DArray';
ISAMPLER2D  : 'isampler2D';
ISAMPLER2DARRAY  : 'isampler2DArray';
ISAMPLERCUBE  : 'isamplerCube';
ISAMPLERCUBEARRAY  : 'isamplerCubeArray';
ISAMPLERBUFFER  : 'isamplerBuffer';
ISAMPLER2DRECT  : 'isampler2DRect';
USAMPLER1D  : 'usampler1D';
USAMPLER1DARRAY  : 'usampler1DArray';
USAMPLER2D  : 'usampler2D';
USAMPLER2DARRAY  : 'usampler2DArray';
USAMPLERCUBE  : 'usamplerCube';
USAMPLERCUBEARRAY  : 'usamplerCubeArray';
USAMPLERBUFFER  : 'usamplerBuffer';
USAMPLER2DRECT  : 'usampler2DRect';
STRUCT  : 'struct';
RETURN  : 'return';
CONTINUE  : 'continue';
DISCARD  : 'discard';
IF  : 'if';
ELSE  : 'else';
SWITCH  : 'switch';
CASE  : 'case';
DEFAULT  : 'default';
WHILE  : 'while';
DO  : 'do';
FOR  : 'for';
BREAK  : 'break';
CONST  : 'const';
UNIFORM  : 'uniform';
BUFFER  : 'buffer';
SHARED  : 'shared';
COHERENT  : 'coherent';
VOLATILE  : 'volatile';
RESTRICT  : 'restrict';
READONLY  : 'readonly';
WRITEONLY  : 'writeonly';
PRECISION  : 'precision';
IN  : 'in';
OUT  : 'out';
INOUT  : 'inout';
INVARIANT  : 'invariant';
CENTROID  : 'centroid';
PATCH  : 'patch';
SAMPLE  : 'sample';
ATOMIC_UINT  : 'atomic_uint';
NOPERAND  : 'noperspective';
FLAT  : 'flat';
SMOOTH  : 'smooth';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;

