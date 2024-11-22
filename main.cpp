// LScript 1.0 | Abthahi Ahmed Rifat

#include <iostream>
#include <fstream>

#include "includes/Tokenizer.hpp"
#include "includes/Parser.hpp"
#include "includes/Interpreter.hpp"
#include "includes/Variables.hpp"
#include "includes/global.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	if (argc > 1){
		ifstream file(argv[1]);
		
		if (file.is_open()){
			if (argc > 2){
				debugLanguage = argv[2];
			}
			
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
			cout<<"No such file is found to interprete!"<<endl;
		}
		
	}else{
		// CLI
		cout<<" Welcome to LScript 1.1.1 | Created by Abthahi Ahmed Rifat"<<endl; 
		cout<<" Copyright (c) 2024"<<endl;
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
