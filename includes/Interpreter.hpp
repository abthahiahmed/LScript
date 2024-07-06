#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Types.hpp"
#include "Tokenizer.hpp"
#include "Functions.hpp"
#include "Variables.hpp"
#include "ErrorLog.hpp"
#include "Condition.hpp"
#include "Arithmetic.hpp"
using namespace std;

struct Block{
	bool execute;
	string token;
	int index;
};

class Interpreter
{
private:
	vector<vector<TokenStructure>> tokens;
	stack<Block> blocks;
	stack<bool> conditional_statements;
	Variables variables;
	Functions functions;
	int cursor;
	bool error;
	bool execute;
	string prevLine;
public:
	Interpreter(vector<vector<TokenStructure>> toks);
	Interpreter(vector<vector<TokenStructure>> toks, Variables vars);
	bool checkBlockBegin(int i);
	bool checkBlockEnd(int i);
	void interpreteLine(int word, int line, vector<TokenStructure> tokens);
	void interprete();
	Variables getVariableStore();
};