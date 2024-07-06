#pragma once
#include <iostream>
#include "Tokenizer.hpp"
#include "Variables.hpp"
#include "ErrorLog.hpp"
using namespace std;

extern string checkCondition(string a, string b, string r);
extern string checkCondition(int a, int b, string r);
extern string checkCondition(float a, float b, string r);
extern string checkCondition(int word, int line, vector<TokenStructure> tokens, int& i, Variables vars);