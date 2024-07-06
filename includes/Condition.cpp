#include "Condition.hpp"

string checkCondition(string a, string b, string r){
	if (r == ">"){
		if (a > b) return "True";
		return "False";
	}  
	if (r == "<"){
		if (a < b) return "True";
		return "False";
	}  	
	if (r == "=="){
		if (a == b) return "True";
		return "False";
	}  	
	if (r == "<="){
		if (a <= b) return "True";
		return "False";
	}  
	if (r == ">="){
		if (a >= b) return "True";
		return "False";
	} 
	return "False";
}
string checkCondition(int a, int b, string r){
	if (r == ">"){
		if (a > b) return "True";
		return "False";
	}  
	if (r == "<"){
		if (a < b) return "True";
		return "False";
	}  	
	if (r == "=="){
		if (a == b) return "True";
		return "False";
	}  	
	if (r == "<="){
		if (a <= b) return "True";
		return "False";
	}  
	if (r == ">="){
		if (a >= b) return "True";
		return "False";
	} 
	return "False";
}
string checkCondition(float a, float b, string r){
	if (r == ">"){
		if (a > b) return "True";
		return "False";
	}  
	if (r == "<"){
		if (a < b) return "True";
		return "False";
	}  	
	if (r == "=="){
		if (a == b) return "True";
		return "False";
	}  	
	if (r == "<="){
		if (a <= b) return "True";
		return "False";
	}  
	if (r == ">="){
		if (a >= b) return "True";
		return "False";
	} 
	return "False";
}

string checkCondition(int word, int line, vector<TokenStructure> tokens, int& i, Variables vars){
	string result = "False";

	if (tokens[i].type == TokenType::NUMBER && tokens[i + 2].type == TokenType::NUMBER){
		result = checkCondition(tokens[i].num_value, tokens[i + 2].num_value, tokens[i + 1].str_value);
		i += 2;
		return result;
	}
	if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 2].type == TokenType::IDENTIFIER){
		Variable a;
		Variable b;
		
		vars.get(word, line, tokens[i].str_value, a);
		vars.get(word, line, tokens[i + 2].str_value, b);
		
		if (a.type == VariableType::V_INTEGER && b.type == VariableType::V_INTEGER){
			result = checkCondition(a.data.int_data, b.data.int_data, tokens[i + 1].str_value);
		}
		if (a.type == VariableType::V_FLOATING && b.type == VariableType::V_FLOATING){
			result = checkCondition(a.data.flt_data, b.data.flt_data, tokens[i + 1].str_value);
		}
		if (a.type == VariableType::V_STRING && b.type == VariableType::V_STRING){
			result = checkCondition(a.data.str_data, b.data.str_data, tokens[i + 1].str_value);
		}	
		i += 2;
		return result;	
	}
	if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 2].type == TokenType::STRING){
		Variable a;
		
		vars.get(word, line, tokens[i].str_value, a);
		
		if (a.type == VariableType::V_STRING){
			result = checkCondition(a.data.str_data, tokens[i + 2].str_value, tokens[i + 1].str_value);
		}	
		i += 2;
		return result;	
	}
	if (tokens[i].type == TokenType::IDENTIFIER && tokens[i + 2].type == TokenType::NUMBER){
		Variable a;
		
		vars.get(word, line, tokens[i].str_value, a);
		
		if (a.type == VariableType::V_INTEGER){
			result = checkCondition(a.data.int_data, (int)tokens[i + 2].num_value, tokens[i + 1].str_value);
		}
		if (a.type == VariableType::V_FLOATING){
			result = checkCondition(a.data.flt_data, (float)tokens[i + 2].num_value, tokens[i + 1].str_value);
		}
		i += 2;
		return result;	
	}
	
	ErrorLog::ConditionError(tokens[i].type, tokens[i + 2].type, word, line);
	return "False";

}

