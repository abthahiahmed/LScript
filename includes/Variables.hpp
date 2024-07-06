#pragma once
#include <iostream>
#include <vector>
#include <variant>
#include "Types.hpp"
#include "Tokenizer.hpp"
using namespace std;

struct Data{
	int int_data;
	string str_data;
	float flt_data;
	bool bl_data;
};

struct Variable{
	int type;
	string name;
	Data data;
	// For Array Purpose
	int value_type;
	vector<Data> values;
};

class Variables
{
private:
	vector<Variable> vars;
public:
	
	Variables();
	void add(int t, string name, Data data);
	void add(int t, int v_t, string name, Data data);
	void add(int t, int v_t, string name, vector<Data> values);
	bool get(int word, int line, string name, Variable& var);
	bool get(int word, int line, string name, Variable& var, int& index);
	bool check(int word, int line, string name);
	void set(int index, Variable var);
	void showVarTable();
};

