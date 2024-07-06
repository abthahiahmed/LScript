#include "Types.hpp"

const char *TokenTypeString[20] = {
	"IDENTIFIER",
	"NUMBER",
	"SEPERATOR",
	"DATA_TYPE",
	"KEYWORD",
	"RELATIONAL",
	"OPERATOR",
	"=",
	"{",
	"}",
	"(",
	")",
	"[",
	"]",
	"LINE_END",
	"STRING",
	"BOOLEAN",
	"NONE"
};

const char *VariableTypeString[5] = {
	"Integer",
	"String",
	"Floating",
	"Boolean",
	"Array"
};
const char *type_to_string(int type){
	return TokenTypeString[type];
};
const char *vtype_to_string(int type){
	return VariableTypeString[type];
};