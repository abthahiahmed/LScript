#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include "Types.hpp"
#include "Tokenizer.hpp"
#include "Variables.hpp"
#include "ErrorLog.hpp"


using namespace std;

struct Function{
	int type;
	string name;
	vector<VariableType> parameters; // Parameters
	int location;
};


class Functions
{
private:
	vector<Function> functions = {
		{V_INTEGER, "random", {V_INTEGER, V_INTEGER}, 0},
	};
	Variables variables;
public:
	Functions(Variables v);
	Functions();
	
	
	void print(int word, int line, vector<TokenStructure> tokens, int& cursor);
	void input(int word, int line, vector<TokenStructure> tokens, Variables& vars, int& cursor);
	void input_line(int word, int line, vector<TokenStructure> tokens, Variables& vars, int& cursor);
	int random_i(int word, int line, vector<TokenStructure> tokens, Variables vars, int& cursor);
	
	
	void add();
	void get();
	bool check(int word, int line, string name);
	
	void exit_();
	void about_();
	
	void setVariableStore(Variables v);
	
};

