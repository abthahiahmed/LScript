#include "Variables.hpp"

Variables::Variables()
{
	vars = {};
}
void Variables::add(int t, string name, Data data){
	
	vars.push_back({t, name, data});
	
//	cout<<name<<" Added Successfully, value = "<<data.int_data<<", type = "<<t<<endl;
}
void Variables::add(int t, int v_t, string name, Data data){
	
	vars.push_back({t, name, data, v_t});
	
//	cout<<name<<" Added Successfully, value = "<<data.int_data<<", type = "<<t<<endl;
}

void Variables::add(int t, int v_t, string name, vector<Data> values){
	
	vars.push_back({t, name, {}, v_t, values});
	
//	cout<<name<<" Added Successfully, value = "<<data.int_data<<", type = "<<t<<endl;
}

bool Variables::get(int word, int line, string name, Variable& var){
	
	
	int l = vars.size();
	int i = 0;
	while(i < l){
		if (vars[i].name == name){
			var = vars[i];
			return true;
		}
		i++;
	}
	cout<<"[x] Variable '"<<name<<"' is undefined at line "<<line<<endl;
	return false;
}
bool Variables::get(int word, int line, string name, Variable& var, int& index){
	
	
	int l = vars.size();
	int i = 0;
	int j = l - 1;
	while(i <= j){
		
		if (vars[i].name == name){
			var = vars[i];
			index = i;
			return true;
		}
		i++;
		if (vars[j].name == name){
			var = vars[j];
			index = j;
			return true;
		}
		j--;
		
	}
	cout<<"[x] Variable '"<<name<<"' is undefined at line "<<line<<endl;
	return false;
}
bool Variables::check(int word, int line, string name){
	int l = vars.size();
	int i = 0;
	while(i < l){
		if (vars[i].name == name){
			cout<<"[!] Variable '"<<name<<"' could not be redeclared at line "<<line<<endl;
			return true;
		}
		i++;
	}
	return false;
}
void Variables::set(int index, Variable var){
	vars[index] = var;
}


void Variables::showVarTable(){
	int l = vars.size();
	
	for (int i = 0; i < l; i++){
		
		cout << "Type : "<<vtype_to_string(vars[i].type)<<"\t";
		cout << "Name : "<<vars[i].name<<"\t";
		cout << "M. Address : "<<&vars[i]<<"\t";
		if (vars[i].type == VariableType::V_INTEGER)
			cout << "Value : "<<vars[i].data.int_data;
		else if (vars[i].type == VariableType::V_FLOATING)
			cout << "Value : "<<vars[i].data.flt_data;
		else if (vars[i].type == VariableType::V_STRING)
			cout << "Value : "<<vars[i].data.str_data;
		else if (vars[i].type == VariableType::V_BOOLEAN)
			cout << "Value : "<< (vars[i].data.bl_data ? "True" : "False");
		
		cout<<endl;
	}
}
