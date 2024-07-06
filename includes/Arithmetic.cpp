#include "Arithmetic.hpp"

int operatorPriority(string op){
	
	if (op == "+" || op == "-")
		return 1;
	if (op == "*" || op == "/")
		return 2;
	return 0;
}

int calculate(int a, int b, string op){
	
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "/") return a / b;
	if (op == "*") return a * b;
	return 0;
}
float calculate(float a, float b, string op){
	
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "/") return a / b;
	if (op == "*") return a * b;
	return 0;
}

int isolveArithmetic(vector<TokenStructure> tokens, int& i, Variables vars, Functions funcs, int word, int line){
		
	stack<int> values;
	stack<string> ops;
	
	while ((tokens[i].type == TokenType::OPERATOR || 
	tokens[i].type == TokenType::NUMBER || 
	tokens[i].type == TokenType::IDENTIFIER || 
	tokens[i].type == TokenType::ROUND_BEGIN || 
	(tokens[i].type == TokenType::ROUND_END && tokens[i + 1].type != TokenType::LINE_END) ||
	tokens[i].type == TokenType::SQUARE_BEGIN)){
		
		if (tokens[i].str_value == "(") ops.push(tokens[i].str_value);
		else if (tokens[i].type == TokenType::NUMBER) values.push((int)tokens[i].num_value);
		else if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 1].type == TokenType::ROUND_BEGIN){
			if (tokens[i].str_value == "random"){
				values.push(funcs.random_i(word, line, tokens, vars, i));
			}
		}
		else if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 1].type == TokenType::SQUARE_BEGIN){
			int tmp_i = i;
			i += 2;
			
			Variable var;
			int index = isolveArithmetic(tokens, i, vars, funcs, word, line);
			
			if (vars.get(word, line, tokens[tmp_i].str_value, var)){
				
				if (var.type == VariableType::V_ARRAY){
					if (index > (int)var.values.size()){
						ErrorLog::OutOfIndex(word, line);
						return 0;
					}
					
					if (var.value_type == VariableType::V_INTEGER) values.push(var.values[index].int_data);
					else if (var.value_type == VariableType::V_FLOATING) values.push(var.values[index].flt_data);
					else{
						ErrorLog::OnlyNumber(word, line);
						return 0;
					}
				}
			}					
			
		}
		else if (tokens[i].type == TokenType::IDENTIFIER){
			Variable var;
			if (vars.get(word, line, tokens[i].str_value, var)){
				if (var.type == VariableType::V_INTEGER) values.push(var.data.int_data);
				else if (var.type == VariableType::V_FLOATING) values.push(var.data.flt_data);
				else{
					ErrorLog::OnlyNumber(word, line);
				}
			}
		}
		else if (tokens[i].str_value == ")"){
			
			while(!ops.empty() && ops.top() != "("){
				
				int v2 = values.top();
				values.pop();
				int v1 = values.top();
				values.pop();
				
				string op = ops.top();
				ops.pop();
				
				values.push(calculate(v1, v2, op));
				
			}
			if (!ops.empty()) ops.pop();
		}else{
			
			while(!ops.empty() && operatorPriority(ops.top()) >= operatorPriority(tokens[i].str_value)){
				
				int v2 = values.top();
				values.pop();
				int v1 = values.top();
				values.pop();
				
				string op = ops.top();
				ops.pop();
				
				values.push(calculate(v1, v2, op));
				
			}
			ops.push(tokens[i].str_value);
		}
		i++;
	}
	while(!ops.empty()){
		
		int v2 = values.top();
		values.pop();
		int v1 = values.top();
		values.pop();
		
		string op = ops.top();
		ops.pop();
		
		values.push(calculate(v1, v2, op));
		
	}	
	if (!values.empty())
		return values.top();
	else 
		return 0;
}
float fsolveArithmetic(vector<TokenStructure> tokens, int& i, Variables vars, Functions funcs, int word, int line){
		
	stack<float> values;
	stack<string> ops;
	
	while (tokens[i].type == TokenType::OPERATOR || 
	tokens[i].type == TokenType::NUMBER || 
	tokens[i].type == TokenType::IDENTIFIER || 
	tokens[i].type == TokenType::ROUND_BEGIN || 
	tokens[i].type == TokenType::ROUND_END ||
	tokens[i].type == TokenType::SQUARE_BEGIN){
		
		if (tokens[i].str_value == "(") ops.push(tokens[i].str_value);
		else if (tokens[i].type == TokenType::NUMBER) values.push(tokens[i].num_value);
		else if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 1].type == TokenType::SQUARE_BEGIN){
			int tmp_i = i;
			i += 2;
			
			Variable var;
			int index = isolveArithmetic(tokens, i, vars, funcs, word, line);
			
			if (vars.get(word, line, tokens[tmp_i].str_value, var)){
				
				if (var.type == VariableType::V_ARRAY){
					if (index > (int)var.values.size()){
						ErrorLog::OutOfIndex(word, line);
						return 0;
					}
					if (var.value_type == VariableType::V_INTEGER) values.push(var.values[index].int_data);
					else if (var.value_type == VariableType::V_FLOATING) values.push(var.values[index].flt_data);
					else{
						ErrorLog::OnlyNumber(word, line);
						return 0;
					}
				}
			}					
			
		}
		else if (tokens[i].type == TokenType::IDENTIFIER){
			Variable var;
			if (vars.get(word, line, tokens[i].str_value, var)){
				if (var.type == VariableType::V_INTEGER) values.push((float)var.data.int_data);
				else if (var.type == VariableType::V_FLOATING) values.push(var.data.flt_data);
				else{
					ErrorLog::OnlyNumber(word, line);
				}
			}
		}
		else if (tokens[i].str_value == ")"){
			
			while(!ops.empty() && ops.top() != "("){
				
				float v2 = values.top();
				values.pop();
				float v1 = values.top();
				values.pop();
				
				string op = ops.top();
				ops.pop();
				
				values.push(calculate(v1, v2, op));
				
			}
			if (!ops.empty()) ops.pop();
		}else{
			
			while(!ops.empty() && operatorPriority(ops.top()) >= operatorPriority(tokens[i].str_value)){
				
				float v2 = values.top();
				values.pop();
				float v1 = values.top();
				values.pop();
				
				string op = ops.top();
				ops.pop();
				
				values.push(calculate(v1, v2, op));
				
			}
			ops.push(tokens[i].str_value);
		}
		i++;
	}
	while(!ops.empty()){
		
		float v2 = values.top();
		values.pop();
		float v1 = values.top();
		values.pop();
		
		string op = ops.top();
		ops.pop();
		
		values.push(calculate(v1, v2, op));
		
	}	
	
	return (float)values.top();
}