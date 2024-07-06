#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "Tokenizer.hpp"
#include "Variables.hpp"
#include "Functions.hpp"
#include "ErrorLog.hpp"

using namespace std;



extern int calculate(int a, int b, string op);
extern int operatorPriority(char op);
extern int isolveArithmetic(vector<TokenStructure> tokens, int& i, Variables vars, Functions funcs, int word, int line);
extern float fsolveArithmetic(vector<TokenStructure> tokens, int& i, Variables vars, Functions funcs, int word, int line);