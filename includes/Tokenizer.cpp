#include "Tokenizer.hpp"
Tokenizer::Tokenizer(){
    tokens = {};
	line = 1;
}
void Tokenizer::tokenize(string code){
    
	vector<TokenStructure> tokenOfLine = {};
	
	int l = code.length();
	
	for (int i = 0; i < l; i++){
		// Numbers
		if (!isspace(code[i])){
			int word = i;
			if (isdigit(code[i])){
				string tmp = "";
				int point = 0;
				while(i < l && (isdigit(code[i]) || code[i] == '.') && point < 2){
					tmp += code[i];
					if (code[i] == '.') point++;
					i++;
				}
				i--;
				tokenOfLine.push_back({TokenType::NUMBER, "", stof(tmp), word, line});
			
			}
			// ==========================================
			// Identifiers
			else if (isalpha(code[i])){
				string tmp = "";
				while(i < l && (isalpha(code[i]) || isdigit(code[i]) || code[i] == '_') ){
					tmp += code[i];
					i++;
				}
				i--;
				// Reserved Keywords
				if (tmp == "if"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "else"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "while"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "for"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "Integer"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "Boolean"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "String"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "Array"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "variable"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "Floating"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "File"){
					tokenOfLine.push_back({TokenType::DATA_TYPE, tmp, 0, word, line});
				}
				else if (tmp == "Function"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "return"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "class"){
					tokenOfLine.push_back({TokenType::KEYWORD, tmp, 0, word, line});
				}
				else if (tmp == "False"){
					tokenOfLine.push_back({TokenType::BOOLEAN, tmp, 0, word, line});
				}
				else if (tmp == "True"){
					tokenOfLine.push_back({TokenType::BOOLEAN, tmp, 0, word, line});
				}
				// Otherwise it identifier;
				else{
					tokenOfLine.push_back({TokenType::IDENTIFIER, tmp, 0, word, line});
				}
			}
			// ==========================================
			// Operators
			
			else if (code[i] == '='){
				if (code[i + 1] == '='){
					i++;
					tokenOfLine.push_back({TokenType::RELATIONAL, "==", 0, word, line});
				}else{
					tokenOfLine.push_back({TokenType::ASSIGN, "=", 0, word, line});
				}
			}
			else if (code[i] == '+'){
				tokenOfLine.push_back({TokenType::OPERATOR, "+", 0, word, line});
			}
			else if (code[i] == '-'){
				if (isdigit(code[i + 1])){
					string tmp = "-";
					i++;
					int point = 0;
					while(i < l && (isdigit(code[i]) || code[i] == '.') && point < 2){
						tmp += code[i];
						if (code[i] == '.') point++;
						i++;
					}
					i--;

					tokenOfLine.push_back({TokenType::NUMBER, "", stof(tmp), word, line});
					
				}else{
					tokenOfLine.push_back({TokenType::OPERATOR, "-", 0, word, line});
				}
			}
			else if (code[i] == '*'){
				tokenOfLine.push_back({TokenType::OPERATOR, "*", 0, word, line});
			}
			else if (code[i] == '/'){
				tokenOfLine.push_back({TokenType::OPERATOR, "/", 0, word, line});
			}	
			else if (code[i] == '%'){
				tokenOfLine.push_back({TokenType::OPERATOR, "%", 0, word, line});
			}
			
			else if (code[i] == '>'){
				if (code[i + 1] == '='){
					i++;
					tokenOfLine.push_back({TokenType::RELATIONAL, ">=", 0, word, line});
				}else{
					tokenOfLine.push_back({TokenType::RELATIONAL, ">", 0, word, line});
				}
			}
			else if (code[i] == '<'){
				if (code[i + 1] == '='){
					i++;
					tokenOfLine.push_back({TokenType::RELATIONAL, "<=", 0, word, line});
				}else{
					tokenOfLine.push_back({TokenType::RELATIONAL, "<", 0, word, line});
				}
			}
			// ==========================================

			// Brackets
			else if (code[i] == '{'){
				tokenOfLine.push_back({TokenType::BRACE_BEGIN, "{", 0, word, line});
			}	
			else if (code[i] == '}'){
				tokenOfLine.push_back({TokenType::BRACE_END, "}", 0, word, line});
			}	
			else if (code[i] == '('){
				tokenOfLine.push_back({TokenType::ROUND_BEGIN, "(", 0, word, line});
			}
			else if (code[i] == ')'){
				tokenOfLine.push_back({TokenType::ROUND_END, ")", 0, word, line});
			}	
			else if (code[i] == '['){
				tokenOfLine.push_back({TokenType::SQUARE_BEGIN, "[", 0, word, line});
			}
			else if (code[i] == ']'){
				tokenOfLine.push_back({TokenType::SQUARE_END, "]", 0, word, line});
			}
			// ==========================================
			else if (code[i] == ','){
				tokenOfLine.push_back({TokenType::SEPERATOR, ",", 0, word, line});
			}
			else if (code[i] == ';'){
				tokenOfLine.push_back({TokenType::LINE_END, ";", 0, word, line});
			}	
			// String
			else if (code[i] == '"'){
				string tmp = "";
				i++;
				while(i < l && code[i] != '"'){
					tmp += code[i];
					i++;
				}
				tokenOfLine.push_back({TokenType::STRING, tmp, 0, word, line});
			}	
			
			// ======================================
		}
	}
	
	if ((int)tokenOfLine.size() > 0 && tokenOfLine[tokenOfLine.size() - 1].type != TokenType::LINE_END && tokenOfLine[tokenOfLine.size() - 1].type != TokenType::BRACE_BEGIN){
		int word = l - 1;
		tokenOfLine.push_back({TokenType::LINE_END, ";", 0, word, line});
	}
	
	if ((int)tokenOfLine.size() > 0) tokens.push_back(tokenOfLine);
	line++;
}

vector<vector<TokenStructure>> Tokenizer::getTokens(){
    return tokens;
}

void Tokenizer::showTokens(){
	
	for (auto line : tokens){
		for (auto i : line){
			cout<<"Type : "<<type_to_string(i.type)<<endl;
		}
	}
	
}
