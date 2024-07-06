#include "Interpreter.hpp"

Interpreter::Interpreter(vector<vector<TokenStructure>> toks, Variables vars)
{
	tokens = toks;
	variables = vars;
	functions.setVariableStore(vars);
	
	execute = true;
	
	
}
Interpreter::Interpreter(vector<vector<TokenStructure>> toks) : variables(), functions(variables)
{
	tokens = toks;
	execute = true;
	prevLine = "statement";
}

bool Interpreter::checkBlockBegin(int i){
	if (tokens[i][cursor].type == TokenType::BRACE_BEGIN){
		return true;
	}
	return false;
}
bool Interpreter::checkBlockEnd(int i){
	if (tokens[i][cursor].type == TokenType::BRACE_END){
		return true;
	}
	return false;
}

void Interpreter::interpreteLine(int word, int line, vector<TokenStructure> toks){
	
	
	// Variable declare
	if (toks[cursor + 0].type == TokenType::DATA_TYPE && toks[cursor + 1].type == TokenType::IDENTIFIER && toks[cursor + 2].type == TokenType::ASSIGN){
		int i = cursor;
		if (variables.check(word, line, toks[cursor + 1].str_value)) return;
			
		if (toks[cursor + 0].str_value == "Integer" && (toks[cursor + 3].type == TokenType::IDENTIFIER || toks[cursor + 3].type == TokenType::NUMBER || toks[cursor + 3].type == TokenType::ROUND_BEGIN)){
			i += 3;
			int tmp = isolveArithmetic(toks, i, variables, functions, word, line);
						
			Data data = {tmp, "", 0.0};
			variables.add(VariableType::V_INTEGER, toks[cursor + 1].str_value, data);
			return;
		}
		if (toks[cursor + 0].str_value == "Floating" && (toks[cursor + 3].type == TokenType::IDENTIFIER || toks[cursor + 3].type == TokenType::NUMBER || toks[cursor + 3].type == TokenType::ROUND_BEGIN)){

			i += 3;
			float tmp = fsolveArithmetic(toks, i, variables, functions, word, line);
			Data data = {0, "", tmp};
			variables.add(VariableType::V_FLOATING, toks[cursor + 1].str_value, data);
			return;
		
		}
		if (toks[cursor + 0].str_value == "Boolean" && (toks[cursor + 3].type == TokenType::IDENTIFIER || toks[cursor + 3].type == TokenType::BOOLEAN)){

			i += 3;
			string tmp = toks[cursor + 3].str_value;
			
			Data data = {0, "", 0, tmp == "True"};
			
			variables.add(VariableType::V_BOOLEAN, toks[cursor + 1].str_value, data);
			return;
		
		}
		if (toks[cursor + 0].str_value == "String" && (toks[cursor + 3].type == TokenType::STRING || toks[cursor + 3].type == TokenType::IDENTIFIER)){
			string tmp = "";
			i += 3;
			while(toks[i].type != TokenType::LINE_END){
				
				if (toks[i].type == TokenType::STRING){
					tmp += toks[i].str_value;
//					return;
				}
				if (toks[i].type == TokenType::NUMBER){
					tmp += toks[i].num_value;
//					return;
				}
				if (toks[i].type == TokenType::IDENTIFIER && toks[i + 1].type == TokenType::SQUARE_BEGIN){
					int tmp_i = i;
					i += 2;
					
					Variable var;
					unsigned index = isolveArithmetic(toks, i, variables, functions, word, line);
					
					if (variables.get(word, line, toks[tmp_i].str_value, var)){
						
						if (var.type == VariableType::V_ARRAY && var.value_type == VariableType::V_STRING){
							if (index > var.values.size()){
								ErrorLog::OutOfIndex(word, line);
								return;
							}
							tmp += var.values[index].str_data;
						}
					}					
					
				}
				if (toks[i].type == TokenType::IDENTIFIER){
					Variable var;
					if (variables.get(word, line, toks[i].str_value, var)){
						if (var.type == VariableType::V_INTEGER){
							tmp += to_string(var.data.int_data);
						}
						if (var.type == VariableType::V_FLOATING){
							tmp += to_string(var.data.flt_data);
						}
						else if (var.type == VariableType::V_STRING){
							tmp += var.data.str_data;
						}
					}
				}
				i++;
			}
			Data data = {0, tmp, 0.0};
			
			variables.add(VariableType::V_STRING,toks[cursor + 1].str_value, data);
			cursor = i;
			return;
		}
		
		int Error = -1;
		if (toks[cursor + 0].str_value == "String") Error = VariableType::V_STRING;
		else if (toks[cursor + 0].str_value == "Integer") Error = VariableType::V_INTEGER;
		else if (toks[cursor + 0].str_value == "Floating") Error = VariableType::V_FLOATING;
		else if (toks[cursor + 0].str_value == "Boolean") Error = VariableType::V_BOOLEAN;
		ErrorLog::TypeError(toks[cursor + 3].type, Error, word, line);
		return;
	}
	// Variable Declare without assigning
	if (toks[cursor + 0].type == TokenType::DATA_TYPE && toks[cursor + 1].type == TokenType::IDENTIFIER){
		if (variables.check(word, line, toks[cursor + 1].str_value)) return;			
		if (toks[cursor + 0].str_value == "Integer"){
			Data data = {0, "", 0.00};
			variables.add(VariableType::V_INTEGER, toks[cursor + 1].str_value, data);
			return;
		}
		if (toks[cursor + 0].str_value == "Floating"){
			Data data = {0, "", 0.00};
			variables.add(VariableType::V_FLOATING, toks[cursor + 1].str_value, data);
			return;
		}
		if (toks[cursor + 0].str_value == "String"){
			Data data = {0, "", 0.00};
			variables.add(VariableType::V_STRING, toks[cursor + 1].str_value, data);
			return;
		}
		if (toks[cursor + 0].str_value == "Boolean"){
			Data data = {0, "", 0.00, false};
			variables.add(VariableType::V_BOOLEAN, toks[cursor + 1].str_value, data);
			return;
		}
		return;
	}
	// Variable assign
	if (toks[cursor + 0].type == TokenType::IDENTIFIER && toks[cursor + 1].type == TokenType::ASSIGN){
		int i = cursor;
		Variable var;
		int index;
		if (!variables.get(word, line, toks[cursor + 0].str_value, var, index)) return;
		if (var.type == VariableType::V_INTEGER && (toks[cursor + 2].type == TokenType::IDENTIFIER || toks[cursor + 2].type == TokenType::NUMBER || toks[cursor + 2].type == TokenType::ROUND_BEGIN)){
			i += 2;
			var.data.int_data = isolveArithmetic(toks, i, variables, functions, word, line);
			variables.set(index, var);
			return;
		}
		if (var.type == VariableType::V_FLOATING && (toks[cursor + 2].type == TokenType::IDENTIFIER || toks[cursor + 2].type == TokenType::NUMBER || toks[cursor + 2].type == TokenType::ROUND_BEGIN)){
			i += 2;
			var.data.flt_data = fsolveArithmetic(toks, i, variables, functions, word, line);
			variables.set(index, var);
			return;
		}
		if (var.type == VariableType::V_BOOLEAN && toks[cursor + 2].type == TokenType::BOOLEAN){
			i += 2;
			var.data.bl_data = toks[cursor + 2].str_value == "True";
			variables.set(index, var);
			return;
		}
		if (var.type == VariableType::V_STRING && (toks[cursor + 2].type == TokenType::STRING || toks[cursor + 2].type == TokenType::IDENTIFIER)){ 
			
			string tmp = "";
			i += 2;
			while(toks[i].type != TokenType::LINE_END){
				
				if (toks[i].type == TokenType::STRING){
					tmp += toks[i].str_value;
				}
				if (toks[i].type == TokenType::NUMBER){
					tmp += toks[i].num_value;
				}
				if (toks[i].type == TokenType::IDENTIFIER && toks[i + 1].type == TokenType::SQUARE_BEGIN){
					int tmp_i = i;
					i += 2;
					
					Variable var;
					unsigned index = isolveArithmetic(toks, i, variables, functions, word, line);
					
					if (variables.get(word, line, toks[tmp_i].str_value, var)){
						
						if (var.type == VariableType::V_ARRAY && var.value_type == VariableType::V_STRING){
							if (index > var.values.size()){
								ErrorLog::OutOfIndex(word, line);
								return;
							}
							tmp += var.values[index].str_data;
						}
					}					
					
				}
				if (toks[i].type == TokenType::IDENTIFIER){
					Variable var;
					if (variables.get(word, line, toks[i].str_value, var)){
						if (var.type == VariableType::V_INTEGER){
							tmp += to_string(var.data.int_data);
						}
						else if (var.type == VariableType::V_FLOATING){
							tmp += to_string(var.data.flt_data);
						}
						else if (var.type == VariableType::V_STRING){
							tmp += var.data.str_data;
						}
					}
				}
				i++;
			}
			var.data.str_data = tmp;
			variables.set(index, var);
			return;
		}
		
		int Error = -1;
		if (var.type == VariableType::V_STRING) Error = VariableType::V_STRING;
		if (var.type == VariableType::V_INTEGER) Error = VariableType::V_INTEGER;
		if (var.type == VariableType::V_FLOATING) Error = VariableType::V_FLOATING;
		if (var.type == VariableType::V_BOOLEAN) Error = VariableType::V_BOOLEAN;
		ErrorLog::TypeError(toks[cursor + 2].type, Error, word, line);
		
		return;
	}	
	
	// Array
	
	if (toks[cursor].type == TokenType::DATA_TYPE && toks[cursor + 1].type == TokenType::ROUND_BEGIN && toks[cursor + 2].type == TokenType::DATA_TYPE){
		
		if (toks[cursor + 5].type == TokenType::LINE_END){
			if (toks[cursor + 2].str_value == "Integer"){
				Data data = {0, "", 0.00};
				variables.add(VariableType::V_ARRAY, VariableType::V_INTEGER, toks[cursor + 4].str_value, data);
				return;
			}
			if (toks[cursor + 2].str_value == "Floating"){
				Data data = {0, "", 0.00};
				variables.add(VariableType::V_ARRAY, VariableType::V_FLOATING, toks[cursor + 4].str_value, data);
				return;
			}
			if (toks[cursor + 2].str_value == "String"){
				Data data = {0, "", 0.00};
				variables.add(VariableType::V_ARRAY, VariableType::V_STRING, toks[cursor + 4].str_value, data);
				return;
			}
			return;
		}
			
		if (toks[cursor + 2].str_value == "Integer"){
			Data data = {0, "", 0.00};
			vector<Data> values = {};
			int i = 7;
			while(toks[i].type != TokenType::SQUARE_END){
			
				if (toks[i].type == TokenType::NUMBER){
					Data d;
					d.int_data = (int)toks[i].num_value;
					values.push_back(d);
				}else{
					
				}
				i++;
			}
			variables.add(VariableType::V_ARRAY, VariableType::V_INTEGER, toks[cursor + 4].str_value, values);
			return;
		}
		if (toks[cursor + 2].str_value == "Floating"){
			Data data = {0, "", 0.00};
			vector<Data> values = {};
			int i = 7;
			while(toks[i].type != TokenType::SQUARE_END){
			
				if (toks[i].type == TokenType::NUMBER){
					Data d;
					d.flt_data = (float)toks[i].num_value;
					values.push_back(d);
				}else{
					
				}
				i++;
			}
			variables.add(VariableType::V_ARRAY, VariableType::V_FLOATING, toks[cursor + 4].str_value, values);
			return;
		}
		if (toks[cursor + 2].str_value == "String"){
			Data data = {0, "", 0.00};
			vector<Data> values = {};
			int i = 7;
			while(toks[i].type != TokenType::SQUARE_END){
			
				if (toks[i].type == TokenType::STRING){
					Data d;
					d.str_data = toks[i].str_value;
					values.push_back(d);
				}else{
					
				}
				i++;
			}
			variables.add(VariableType::V_ARRAY, VariableType::V_STRING, toks[cursor + 4].str_value, values);
			return;
		}
		return;
	}
	
	
	// Functions
	if (toks[cursor].type == TokenType::IDENTIFIER && toks[cursor + 1].type == TokenType::ROUND_BEGIN){
		// Updating variable storage for functions;
		
		if (toks[cursor].str_value == "print"){
			functions.print(word, line, toks, cursor);
			return;
		}
		if (toks[cursor].str_value == "print_line"){
			functions.print(word, line, toks, cursor);
			cout<<endl;
			return;
		}
		if (toks[cursor].str_value == "input"){
			functions.input(word, line, toks, variables, cursor);
			return;
		}
		if (toks[cursor].str_value == "input_line"){
			functions.input_line(word, line, toks, variables, cursor);
			return;
		}
		if (toks[cursor].str_value == "showVarTable"){
			variables.showVarTable();
			return;
		}
		if (toks[cursor].str_value == "exit"){
			functions.exit_();
			return;
		}
		if (toks[cursor].str_value == "about"){
			functions.about_();
			return;
		}
		ErrorLog::Undefined(toks[cursor].str_value, word, line);
				
		return;
	}
	
	// Keywords
	if (toks[cursor].type == TokenType::KEYWORD){
		// Conditional Statement
		if (toks[cursor].str_value == "if"){
			int i = 2;
			string result = "False";
			while(toks[cursor + i].type != TokenType::ROUND_END){
				
				result = checkCondition(word, line, toks, i, variables);
				i++;
			}
			if (result == "False") execute = false;
			conditional_statements.push(execute);
			
			cursor = i + 1;
			prevLine = "condition";
			return;
		}
		if (toks[cursor].str_value == "else" && toks[cursor + 1].str_value == "if"){
			if (conditional_statements.empty()) return; 
			
			int i = 3;
			string result = "False";
			while(toks[cursor + i].type != TokenType::ROUND_END){
				
				result = checkCondition(word, line, toks, i, variables);
				i++;
			}
			if (result == "False") execute = false;
			if (!conditional_statements.top()) conditional_statements.top() = execute;
			cursor = i + 1;
			prevLine = "condition";
		}
		if (toks[cursor].str_value == "else"){
			if (conditional_statements.empty()) return; 
			execute = !conditional_statements.top();
			if (!conditional_statements.empty()) conditional_statements.pop();
			cursor += 1;
			return;
		}
		if (toks[cursor].str_value == "while"){
			int i = 2;
			string result = "False";
			while(toks[cursor + i].type != TokenType::ROUND_END){
				result = checkCondition(word, line, toks, i, variables);
				i++;
			}
			if (result == "False") execute = false;
			return;
		}
		
		if (toks[cursor].str_value == "for"){
			
			
			
			string result = "False";
			if (cursor == 0) cursor = 2;
			
			
			result = checkCondition(word, line, toks, cursor, variables);
			
//			cursor += 2;
//			interpreteLine(line, toks);
//			
			if (result == "False") execute = false;
			return;
		}
		
		return;
	}
	
//	if (toks[cursor].type == TokenType::BRACE_BEGIN){
//		blocks.push({execute, "", line - 1});
//		cursor++;
//	}
//	if (!blocks.empty())
//		cout<<blocks.top()<<endl;
	
//		cout<<conditional_statements.size()<<endl;
	
}


void Interpreter::interprete(){
	int l = tokens.size();
	int i = 0;
	while (i < l){
		cursor = 0;
		// Conditional Statement Flow
		if (execute){
			
			interpreteLine(0, tokens[i][0].line, tokens[i]);
			
			
			
			if (tokens[i][0].type != TokenType::BRACE_BEGIN && tokens[i][0].type != TokenType::BRACE_END){
				if (i > 0 && i + 1 < l && tokens[i - 1][0].str_value == "if" && (tokens[i + 1][0].str_value != "else")){
					if (!conditional_statements.empty()) conditional_statements.pop();
				}
				else if (i > 0 && tokens[i - 1][0].str_value == "while"){
					i = i - 2;
				}
				else if (i > 0 && tokens[i - 1][0].str_value == "for"){
					
					cursor = 2;
					while(tokens[i - 1][cursor].type != TokenType::LINE_END) cursor++;
					cursor += 1;
					cout<<tokens[i - 1][cursor].str_value<<endl;
					interpreteLine(0, tokens[i - 1][0].line, tokens[i - 1]);
					
					i = i - 2;
					
				}
			}
			else if (tokens[i][0].type == TokenType::BRACE_BEGIN){
				
				if (tokens[i - 1][0].str_value == "if"){
					blocks.push({execute, tokens[i - 1][0].str_value, i});
				}
				else if (tokens[i - 1][0].str_value == "while"){
					if (!blocks.empty() && blocks.top().index != i - 1){
							blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}else{
						blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}
				}
				else if (tokens[i - 1][0].str_value == "for"){
					if (!blocks.empty() && blocks.top().index != i - 1){
							blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}else{
						blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}
				}
				else{
					blocks.push({execute, "", i});
				}
			}
			else if (!blocks.empty() && tokens[i][0].type == TokenType::BRACE_END){
				
				if (i + 1 < l && tokens[i + 1][0].str_value != "else" && blocks.top().token == "if"){
					if (!blocks.empty()) blocks.pop();
					if (!conditional_statements.empty()) conditional_statements.pop();
					execute = true;
				}
				else if (blocks.top().token == "while"){
					execute = true;
					i = blocks.top().index - 1;
					blocks.pop();
					
//					cout<<"ID : "<<blocks.top().index<<endl;
				}
				else if (blocks.top().token == "for"){
					

					
					execute = true;
					i = blocks.top().index - 1;
					blocks.pop();
					
					cursor = 2;
					while(tokens[i + 1][cursor].type != TokenType::LINE_END) cursor++;
					cursor += 1;
//					cout<<tokens[i - 1][cursor].str_value<<endl;
					interpreteLine(0, tokens[i + 1][0].line, tokens[i + 1]);
//					cout<<"ID : "<<blocks.top().index<<endl;
				}
				else{
					execute = true;
					if (!blocks.empty()) blocks.pop();
				}
			}
			
			
			
		}else{
			if (tokens[i][0].type == TokenType::BRACE_BEGIN){
				
				if (tokens[i - 1][0].str_value == "if"){
					blocks.push({execute, tokens[i - 1][0].str_value, i});
				}
				else if (tokens[i - 1][0].str_value == "while"){
					if (!blocks.empty() && blocks.top().index != i - 1){
							blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}else{
						blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}
				}
				else if (tokens[i - 1][0].str_value == "for"){
					if (!blocks.empty() && blocks.top().index != i - 1){
							blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}else{
						blocks.push({execute, tokens[i - 1][0].str_value, i - 1});
					}
				}
				else{
					blocks.push({execute, "", i});
				}
			}
			else if (!blocks.empty() && tokens[i][0].type == TokenType::BRACE_END){
				
				if (i + 1 < l && tokens[i + 1][0].str_value != "else" && blocks.top().token == "if"){
					if (!blocks.empty()) blocks.pop();
					if (!conditional_statements.empty()) conditional_statements.pop();
					execute = true;
				}
				else if (blocks.top().token == "while"){
					execute = true;
					blocks.pop();
				}
				else if (blocks.top().token == "for"){
					execute = true;
					blocks.pop();
				}
				else{
					execute = true;
					blocks.pop();
				}
			}else{
			
				if (i + 1 < l && tokens[i - 1][0].str_value == "if" && tokens[i + 1][0].str_value != "else"){
					execute = true;
					if (!conditional_statements.empty()) conditional_statements.pop();
				}else{
					execute = true;
				}
				if (i + 1 < l && tokens[i - 1][0].str_value == "else" && tokens[i - 1][1].str_value == "if" && tokens[i + 1][0].str_value != "else"){
					execute = true;
					if (!conditional_statements.empty()) conditional_statements.pop();
				}else{
					execute = true;
				}
			}
			
			if (!blocks.empty()) execute = blocks.top().execute;
		}
		

		functions.setVariableStore(variables);
		i++;
	}
	
//	if (!blocks.empty()) cout<<blocks.top().index<<endl;
	
	if (!blocks.empty()) blocks.pop();
	
}
Variables Interpreter::getVariableStore(){
	return variables;
}



