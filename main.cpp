// LScript 1.0 | Abthahi Ahmed Rifat

#include <iostream>
#include <fstream>

#include "includes/Tokenizer.hpp"
#include "includes/Parser.hpp"
#include "includes/Interpreter.hpp"
#include "includes/Variables.hpp"
using namespace std;

int main(int argc, char *argv[])
{

	if (argc > 1){
		ifstream file(argv[1]);
		string line;
		Tokenizer tokenizer = Tokenizer();
		
		
		while(getline(file, line)){
			
			if (line != "") tokenizer.tokenize(line);
			
		}
		
		Parser parser = Parser(tokenizer.getTokens());
		
		if (parser.parse()){
//			cout<<"[i] Parsing done...!"<<endl;
			
			Interpreter interpreter = Interpreter(tokenizer.getTokens());
			interpreter.interprete();
			
			cout<<endl;
			cout<<"[i] Code executed successfully."<<endl;
		}
		
		
	}else{
		// CLI
		
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
		string command;
		Variables var_store;
		while (true){
			
			cout<<"[LS] -> ";
			getline(cin, command);
			
			if (command != ""){
				
				Tokenizer tokenizer = Tokenizer();
				tokenizer.tokenize(command);
					
//				tokenizer.showTokens();
				
				Parser parser = Parser(tokenizer.getTokens());
				
				if (parser.parse()){
					
					Interpreter interpreter = Interpreter(tokenizer.getTokens(), var_store);
					interpreter.interprete();
					
					var_store = interpreter.getVariableStore();

				}
			}
		}
	}
	
    return 0;
}
