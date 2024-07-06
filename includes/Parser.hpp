#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "Tokenizer.hpp"
#include "ErrorLog.hpp"
using namespace std;

class Parser
{
private:
	vector<vector<TokenStructure>> tokens;
	stack<TokenType> braces;
	stack<TokenType> rounds;
	stack<string> conditional_statements;
	int cursor;
	bool success;
	int line;
public:
	Parser(vector<vector<TokenStructure>> toks);
	void check(TokenType type);
	void checkBODMAS();
	void checkExpr();
	void checkRegular();
	void checkForIndex();
	bool parse();
};

