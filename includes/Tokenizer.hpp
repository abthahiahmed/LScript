#pragma once

#include <iostream>
#include <vector>
#include "Types.hpp"

using namespace std;

struct TokenStructure{
    TokenType type;
	string str_value; // For alpha constant
	float num_value; // float constant
	int word;
    int line;
};

class Tokenizer
{
private:
    
    vector<vector<TokenStructure>> tokens;
	int line;
public:

    Tokenizer();
    void tokenize(string code);
    vector<vector<TokenStructure>> getTokens();
	void showTokens();
};

