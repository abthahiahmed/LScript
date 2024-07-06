#include "Functions.hpp"
#include "Condition.hpp"
#include "Arithmetic.hpp"
Functions::Functions(Variables v)
{
	variables = v;
	srand(time(0)); // For random
}
Functions::Functions(){
	srand(time(0)); // For random
}

bool Functions::check(int word, int line, string name){
	
	int l = functions.size();
	int i = 0;
	while(i < l){
		if (functions[i].name == name){
			cout<<"[!] Variable '"<<name<<"' could not be redeclared at line "<<line<<endl;
			return true;
		}
		i++;
	}
	return false;
}



void Functions::setVariableStore(Variables v){
	variables = v;
}
void Functions::print(int word, int line, vector<TokenStructure> tokens, int& cursor)
{
	
	int i = cursor + 2;
	string tmp = "";
	while (tokens[i].type != TokenType::LINE_END){
		
		if (tokens[i + 1].type != TokenType::RELATIONAL){
			if (tokens[i].type == TokenType::STRING) cout<<tokens[i].str_value;
			else if (tokens[i].type == TokenType::NUMBER){
				cout<<isolveArithmetic(tokens, i, variables, *this, word, line);
			}
			else if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 1].type == TokenType::ROUND_BEGIN){
				
				if (tokens[i].str_value == "random"){
					cout<<random_i(word, line, tokens, variables, i);
				}
				
			}
			else if (tokens[i].type == TokenType::IDENTIFIER){
				Variable var;
				if (!variables.get(word, line, tokens[i].str_value, var)) exit(1);
				if (var.type == VariableType::V_INTEGER){
					cout<<var.data.int_data;
				}
				else if (var.type == VariableType::V_FLOATING){
					cout<<var.data.flt_data;
				}
				else if (var.type == VariableType::V_STRING){
					cout<<var.data.str_data;
				}
				else if (var.type == VariableType::V_ARRAY && tokens[i + 1].type == TokenType::SQUARE_BEGIN){
					i += 2;
					if (!var.values.empty()){
						
						unsigned index = isolveArithmetic(tokens, i, variables, *this, word, line);
						if (index > var.values.size()){
							ErrorLog::OutOfIndex(word, line);
							return;
						}
						int value_type = var.value_type;
						if (value_type == VariableType::V_STRING){
							cout<<var.values[index].str_data;
						}
						if (value_type == VariableType::V_INTEGER){
							cout<<var.values[index].int_data;
						}
						if (value_type == VariableType::V_FLOATING){
							cout<<var.values[index].flt_data;
						}
						
					}
				}
				else if (var.type == VariableType::V_ARRAY){
					cout<<"[";
					if (!var.values.empty()){
						int value_type = var.value_type;
						if (value_type == VariableType::V_STRING){
							for (unsigned i = 0; i < var.values.size(); i++){
								
								cout<<var.values[i].str_data;
								if (i < var.values.size() - 1) cout<<",";
							}
						}
						if (value_type == VariableType::V_INTEGER){
							for (unsigned i = 0; i < var.values.size(); i++){
								
								cout<<var.values[i].int_data;
								if (i < var.values.size() - 1) cout<<",";
							}
						}
						if (value_type == VariableType::V_FLOATING){
							for (unsigned i = 0; i < var.values.size(); i++){
								
								cout<<var.values[i].flt_data;
								if (i < var.values.size() - 1) cout<<",";
							}
						}
						
					}
					
					cout<<"]";
				}
			}
		}else{
			cout<<checkCondition(word, line, tokens, i, variables);
		}
		
		i++;
	}
	cursor = i + 1;
	
}

void Functions::input(int word, int line, vector<TokenStructure> tokens, Variables& vars, int& cursor)
{
	
	int i = cursor + 2;
	
	string input = "";
	
	while (tokens[i].type != TokenType::ROUND_END){
		
		if (tokens[i].type == TokenType::IDENTIFIER){
			
			Variable var;
			int index;
			if (variables.get(word, line, tokens[i].str_value, var, index)){
				cin>>input;
				if (var.type == VariableType::V_INTEGER) var.data.int_data = stoi(input);
				else if (var.type == VariableType::V_FLOATING) var.data.flt_data = stof(input);
				else if (var.type == VariableType::V_STRING) var.data.str_data = input;
				variables.set(index, var);
				vars = variables;
			}	
			
		}else{
			
			ErrorLog::NonIdentifier(word, line);
			
		}
		i++;
	}
	cursor = i + 1;
}

void Functions::input_line(int word, int line, vector<TokenStructure> tokens, Variables& vars, int& cursor)
{
	
	int i = cursor + 2;
	
	string input = "";
	
	while (tokens[i].type != TokenType::ROUND_END){
		
		if (tokens[i].type == TokenType::IDENTIFIER){
			
			Variable var;
			int index;
			if (variables.get(word, line, tokens[i].str_value, var, index)){
				getline(cin, input);
				if (var.type == VariableType::V_INTEGER) var.data.int_data = stoi(input);
				else if (var.type == VariableType::V_FLOATING) var.data.flt_data = stof(input);
				else if (var.type == VariableType::V_STRING) var.data.str_data = input;
				variables.set(index, var);
				vars = variables;
			}	
			
		}else{
			
			ErrorLog::NonIdentifier(word, line);
			
		}
		i++;
	}
	cursor = i + 1;
}

int Functions::random_i(int word, int line, vector<TokenStructure> tokens, Variables vars, int& cursor){
	
	int i = cursor + 2;
	
	int p_size = functions[0].parameters.size();
	
	int *numbers = new int[p_size];
	
	int j = 0;
	
	while (tokens[i].type != TokenType::ROUND_END){
		
		if (j < p_size){
			if (tokens[i].type == TokenType::NUMBER){
				numbers[j] = (int)tokens[i].num_value;
				j++;
			}
		}else{
			cout<<"Too few arguments"<<endl;
			break;
		}
		i++;
	}
	
	cursor = i;
	
	return (rand() % (numbers[1] - numbers[0] + 1)) + numbers[0];
	
}



void Functions::exit_(){
	cout<<"Thank You!"<<endl;
	exit(1);
	
}

void Functions::about_(){
	cout<<"  _        _____              _         _    "<<endl;
	cout<<" | |      / ____|            (_)       | |   "<<endl;
	cout<<" | |     | (___    ___  _ __  _  _ __  | |_  "<<endl;
	cout<<" | |      \\___ \\  / __|| '__|| || '_ \\ | __| "<<endl;
	cout<<" | |____  ____) || (__ | |   | || |_) || |_  "<<endl;
	cout<<" |______||_____/  \\___||_|   |_|| .__/  \\__| "<<endl;
	cout<<"                             | |             "<<endl;
	cout<<"                             |_|             "<<endl;
	cout<<endl;
	cout<<" Welcome to LScript 1.0 | Created by Abthahi Ahmed Rifat"<<endl; 
	cout<<" Copyright (c) 2023"<<endl;
	cout<<endl;
	cout<<endl;
}
