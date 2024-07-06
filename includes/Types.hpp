#pragma once

enum TokenType{
	IDENTIFIER = 0,
	NUMBER,
	SEPERATOR,
	DATA_TYPE,
	KEYWORD,
	RELATIONAL,
	OPERATOR,
	ASSIGN,
	BRACE_BEGIN,
	BRACE_END,
	ROUND_BEGIN,
	ROUND_END,
	SQUARE_BEGIN,
	SQUARE_END,
	LINE_END,
	STRING,
	BOOLEAN,
	NONE,
};

enum VariableType{
	V_INTEGER = 0,
	V_STRING,
	V_FLOATING,
	V_BOOLEAN,
	V_ARRAY,
};


extern const char *TokenTypeString[20];
extern const char *VariableTypeString[5];
extern const char *type_to_string(int type);
extern const char *vtype_to_string(int type);