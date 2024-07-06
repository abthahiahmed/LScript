#include "Parser.hpp"

Parser::Parser(vector<vector<TokenStructure>> toks)
{
	tokens = toks;
	line = 0;
	cursor = 0;
	success = true;
}



void Parser::check(TokenType type){
	if (tokens[line][cursor].type == TokenType::ROUND_BEGIN) rounds.push(TokenType::ROUND_BEGIN);
		
	if (tokens[line][cursor].type == TokenType::ROUND_END){
		if (!rounds.empty()) rounds.pop();
		else{
			ErrorLog::RoundError(tokens[line][cursor].word, tokens[line][cursor].line);
			success = false;
		}
	}
	
	
	if (tokens[line][cursor].type != type){
		ErrorLog::WrongToken(type, tokens[line][cursor].type, tokens[line][cursor].word, tokens[line][cursor].line);
		success = false;
//		exit(1);
	}
	if (cursor < (int)tokens[line].size() - 1) cursor++;
}



void Parser::checkBODMAS(){
	
	stack<TokenType> rounds;
	while(tokens[line][cursor].type == TokenType::OPERATOR || 
		tokens[line][cursor].type == TokenType::NUMBER || 
		tokens[line][cursor].type == TokenType::IDENTIFIER || 
		tokens[line][cursor].type == TokenType::ROUND_BEGIN || 
		tokens[line][cursor].type == TokenType::ROUND_END){
			
						
//		if (tokens[line][cursor].type == TokenType::ROUND_BEGIN) rounds.push(TokenType::ROUND_BEGIN);
//		
//		if (tokens[line][cursor].type == TokenType::ROUND_END){
//			if (!rounds.empty()) rounds.pop();
//			else{
//				ErrorLog::RoundError(tokens[line][cursor].word, tokens[line][cursor].line);
//				success = false;
//				break;
//			}
//		}
		
		TokenType current = tokens[line][cursor].type;
		TokenType previous = tokens[line][cursor - 1].type;
		
		// 10 +
		if (current == TokenType::OPERATOR && previous == TokenType::NUMBER){
			check(current);
		}
		// a + 
		else if (current == TokenType::OPERATOR && previous == TokenType::IDENTIFIER){
			check(current);
		}
		// ) +
		else if (current == TokenType::OPERATOR && previous == TokenType::ROUND_END){
			check(current);
		}
		
		// ( 10
		else if (current == TokenType::NUMBER && previous == TokenType::ROUND_BEGIN){
			check(current);
			
		}
		// + 10
		else if (current == TokenType::NUMBER && previous == TokenType::OPERATOR){
			check(current);
			
		}				
		// ( a
		else if (current == TokenType::IDENTIFIER && previous == TokenType::ROUND_BEGIN){
			check(current);
		}
		// + a
		else if (current == TokenType::IDENTIFIER && previous == TokenType::OPERATOR){
			check(current);
		}	

		// + (
		else if (current == TokenType::ROUND_BEGIN && previous == TokenType::OPERATOR){
			check(current);
		}	
		// = (
		else if (current == TokenType::ROUND_BEGIN && previous == TokenType::ASSIGN){
			check(current);
		}	
		
		// a )
		else if (current == TokenType::ROUND_END && previous == TokenType::IDENTIFIER){
			check(current);
		}
		// 10 )
		else if (current == TokenType::ROUND_END && previous == TokenType::NUMBER){
			check(current);
		}				
		else{
			success = false;
			break;
		}				
	}
	if (tokens[line][cursor - 1].type == TokenType::OPERATOR){
		ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
		success = false;
	}
//	if (!rounds.empty()){
//		ErrorLog::RoundError(tokens[line][cursor].word, tokens[line][cursor].line);
//		success = false;
//	}	
}

void Parser::checkRegular(){
	if (tokens[line][cursor].type == TokenType::IDENTIFIER){
		check(TokenType::IDENTIFIER);
		checkExpr();
	}
	else if (tokens[line][cursor].type == TokenType::NUMBER){
		check(TokenType::NUMBER);
		checkExpr();
	}
	else if (tokens[line][cursor].type == TokenType::STRING){
		check(TokenType::STRING);
		checkExpr();
	}else{
		ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
		success = false;
	}
}

void Parser::checkForIndex(){
	if (tokens[line][cursor].type == TokenType::IDENTIFIER){
		check(TokenType::IDENTIFIER);
		checkExpr();
	}
	else if (tokens[line][cursor].type == TokenType::NUMBER){
		check(TokenType::NUMBER);
		checkExpr();
	}else{
		ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
		success = false;
	}
}

// Grammer
void Parser::checkExpr(){
	

	
	
	// {
	if (tokens[line].size() > 1 && tokens[line][cursor].type == TokenType::BRACE_BEGIN) { 
		check(TokenType::BRACE_BEGIN);
		braces.push(TokenType::BRACE_BEGIN);
		checkExpr();
	}
	else if (tokens[line][cursor].type == TokenType::BRACE_END) { 
		check(TokenType::BRACE_END);
		if (braces.size() < 1){
			ErrorLog::BraceError(tokens[line][cursor].word, tokens[line][cursor].line);
			success = false;
		}
		if (braces.size() > 0 && braces.top() == TokenType::BRACE_BEGIN) braces.pop();
//		checkExpr();
	}
	
	// ( 123
	else if (tokens[line][cursor].type == TokenType::ROUND_BEGIN && tokens[line][cursor + 1].type == TokenType::NUMBER){
		check(TokenType::ROUND_BEGIN);
		checkExpr();
		check(TokenType::ROUND_END);
	}
	// + (
	else if (tokens[line][cursor].type == TokenType::OPERATOR && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN){
		check(TokenType::OPERATOR);
		check(TokenType::ROUND_BEGIN);
		checkExpr();
	}
	// ) +

	
	
	// Integer i = 10;
	else if (tokens[line][cursor].type == TokenType::DATA_TYPE && tokens[line][cursor + 1].type == TokenType::IDENTIFIER && tokens[line][cursor + 2].type == TokenType::ASSIGN){
		check(TokenType::DATA_TYPE);	
		check(TokenType::IDENTIFIER);
		check(TokenType::ASSIGN);
		// a[..]
		if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::SQUARE_BEGIN){
			check(TokenType::IDENTIFIER);
			check(TokenType::SQUARE_BEGIN);
			checkForIndex();
			check(TokenType::SQUARE_END);
			checkExpr();
		}
		// a
		else if (tokens[line][cursor].type == TokenType::IDENTIFIER){
			check(TokenType::IDENTIFIER);
			
			if (tokens[line][cursor].type == TokenType::ROUND_BEGIN){
				check( TokenType::ROUND_BEGIN);
				checkExpr();
				check( TokenType::ROUND_END);
			}
			checkExpr();
		}
		// 123
		else if (tokens[line][cursor].type == TokenType::NUMBER){
			check(TokenType::NUMBER);
			if (tokens[line][cursor].type == TokenType::OPERATOR){
				check(TokenType::OPERATOR);
				checkBODMAS();
			}
			checkExpr();
		}
		// "Hello World"
		else if (tokens[line][cursor].type == TokenType::STRING){
			check(TokenType::STRING);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::BOOLEAN){
			check(TokenType::BOOLEAN);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::ROUND_BEGIN){
			checkBODMAS();
		}
		else{
			
			ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
			success = false;
		}
		
	}

	else if (tokens[line][cursor].type == TokenType::DATA_TYPE && tokens[line][cursor + 1].type == TokenType::IDENTIFIER){
		check(TokenType::DATA_TYPE);	
		check(TokenType::IDENTIFIER);
		checkExpr();
	}	
	
	// a[..]
	else if (tokens[line][cursor - 1].type == TokenType::IDENTIFIER && tokens[line][cursor].type == TokenType::SQUARE_BEGIN){
		check(TokenType::SQUARE_BEGIN);
		checkForIndex();
		check(TokenType::SQUARE_END);
		checkExpr();
	}
	
	// a = ...
	else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::ASSIGN){
		check(TokenType::IDENTIFIER);
		check(TokenType::ASSIGN);
		if (tokens[line][cursor].type == TokenType::IDENTIFIER){
			check(TokenType::IDENTIFIER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::BOOLEAN){
			check(TokenType::BOOLEAN);
			checkExpr();
		}
		// 123
		else if (tokens[line][cursor].type == TokenType::NUMBER){
			check(TokenType::NUMBER);
			if (tokens[line][cursor].type == TokenType::OPERATOR){
				check(TokenType::OPERATOR);
				checkBODMAS();
			}
			checkExpr();
		}
		// "Hello World"
		else if (tokens[line][cursor].type == TokenType::STRING){
			check(TokenType::STRING);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::ROUND_BEGIN){
			checkBODMAS();
		}
		else{
			ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
			success = false;
		}
		
	}
	// Array(Integer) arr = [];
	else if (tokens[line][cursor].type == TokenType::DATA_TYPE && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN && tokens[line][cursor + 2].type == TokenType::DATA_TYPE){
		
		check(TokenType::DATA_TYPE);
		check(TokenType::ROUND_BEGIN);
		check(TokenType::DATA_TYPE);
		check(TokenType::ROUND_END);
		check(TokenType::IDENTIFIER);
		
		if (tokens[line][cursor].type == TokenType::ASSIGN) check(TokenType::ASSIGN);
		
		if (tokens[line][cursor].type == TokenType::SQUARE_BEGIN) check(TokenType::SQUARE_BEGIN);
		
		checkExpr();
		
		if (tokens[line][cursor].type == TokenType::SQUARE_END) check(TokenType::SQUARE_END);
	}
	
	
	// a (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::OPERATOR){
		check(TokenType::IDENTIFIER);
		check(TokenType::OPERATOR);
		checkRegular();
		
	}

	// 10 (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::NUMBER && tokens[line][cursor + 1].type == TokenType::OPERATOR){
		check(TokenType::NUMBER);
		check(TokenType::OPERATOR);
		checkRegular();
	}

	// 10 (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::STRING && tokens[line][cursor + 1].type == TokenType::OPERATOR){
		check(TokenType::STRING);
		check(TokenType::OPERATOR);
		checkRegular();
	}
	
	
	// a (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::SEPERATOR){
		check(TokenType::IDENTIFIER);
		check(TokenType::SEPERATOR);
		checkRegular();
		
	}

	// 10 (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::NUMBER && tokens[line][cursor + 1].type == TokenType::SEPERATOR){
		check(TokenType::NUMBER);
		check(TokenType::SEPERATOR);
		checkRegular();
	}

	// 10 (+,-,*,/,%) ...
	else if (tokens[line][cursor].type == TokenType::STRING && tokens[line][cursor + 1].type == TokenType::SEPERATOR){
		check(TokenType::STRING);
		check(TokenType::SEPERATOR);
		checkRegular();
	}

	else if (tokens[line][cursor].type == TokenType::KEYWORD && tokens[line][cursor + 1].type == TokenType::KEYWORD && tokens[line][cursor + 2].type == TokenType::ROUND_BEGIN){
		check(TokenType::KEYWORD);
		check(TokenType::KEYWORD);
		check(TokenType::ROUND_BEGIN);
		checkRegular();
		check(TokenType::ROUND_END);
		
	}
	

	else if (tokens[line][cursor].type == TokenType::KEYWORD && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN){
		
		if (tokens[line][cursor].str_value == "if"){
			conditional_statements.push("if");
		}
		
		if (tokens[line][cursor].str_value == "for"){
			check(TokenType::KEYWORD);
			check(TokenType::ROUND_BEGIN);
			checkExpr();
			check(TokenType::LINE_END);
			checkExpr();
			check(TokenType::ROUND_END);
			
		}else{
			check(TokenType::KEYWORD);
			check(TokenType::ROUND_BEGIN);
			
			
			
			checkRegular();
			
			check(TokenType::ROUND_END);
		}
			

		
	}
	
	// func()
	else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN){
		
		check(TokenType::IDENTIFIER);
		check(TokenType::ROUND_BEGIN);
		
		if(tokens[line][cursor].type != TokenType::ROUND_END){
			if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN){
				check(TokenType::IDENTIFIER);
				check(TokenType::ROUND_BEGIN);
			}
			else if (tokens[line][cursor].type == TokenType::IDENTIFIER){
				check(TokenType::IDENTIFIER);
			}
			else if (tokens[line][cursor].type == TokenType::NUMBER){
				check(TokenType::NUMBER);
			}
			else if (tokens[line][cursor].type == TokenType::STRING){
				check(TokenType::STRING);
			}else{
				ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
				success = false;
			}
//			

//			while (tokens[line][cursor].type == TokenType::IDENTIFIER || 
//			tokens[line][cursor].type == TokenType::ROUND_BEGIN ||
//			(tokens[line][cursor].type == TokenType::ROUND_END) ||
//			tokens[line][cursor].type == TokenType::NUMBER || 
//			tokens[line][cursor].type == TokenType::STRING ||
//			tokens[line][cursor].type == TokenType::SEPERATOR){
//				
//				if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::ROUND_BEGIN){
//					check(TokenType::IDENTIFIER);
//					check(TokenType::ROUND_BEGIN);
//					checkExpr();
//	//				check(TokenType::ROUND_END);
//				}
//				else if (tokens[line][cursor].type == TokenType::IDENTIFIER){
//					check(TokenType::IDENTIFIER);
//					checkExpr();
//				}
//				else if (tokens[line][cursor].type == TokenType::NUMBER){
//					check(TokenType::NUMBER);
//					checkExpr();
//				}
//				else if (tokens[line][cursor].type == TokenType::STRING){
//					check(TokenType::STRING);
//					checkExpr();
//					
//				}else{
//					ErrorLog::EndOfLine(tokens[line][cursor].word, tokens[line][cursor].line);
//					success = false;
//				}
//				
//			}
			checkExpr();
		}
		check(TokenType::ROUND_END);
		checkExpr();
	}
	
	
	else if (tokens[line][cursor + 2].type != TokenType::NUMBER && tokens[line][cursor + 2].type != TokenType::IDENTIFIER && tokens[line][cursor + 2].type != TokenType::STRING){
		// (+,-,/,*,%) 123
		if (tokens[line][cursor].type == TokenType::OPERATOR && tokens[line][cursor + 1].type == TokenType::NUMBER){
			check(TokenType::OPERATOR);
			check(TokenType::NUMBER);
			checkExpr();
		}
		// (+,-,/,*,%) abc
		else if (tokens[line][cursor].type == TokenType::OPERATOR && tokens[line][cursor + 1].type == TokenType::IDENTIFIER){
			check(TokenType::OPERATOR);
			check(TokenType::IDENTIFIER);
			checkExpr();
		}	
		// (+,-,/,*,%) "Hello World"
		else if (tokens[line][cursor].type == TokenType::OPERATOR && tokens[line][cursor + 1].type == TokenType::STRING){
			check(TokenType::OPERATOR);
			check(TokenType::STRING);
			checkExpr();
		}	

		// , 123
		else if (tokens[line][cursor].type == TokenType::SEPERATOR && tokens[line][cursor + 1].type == TokenType::NUMBER){
			check(TokenType::SEPERATOR);
			check(TokenType::NUMBER);
			checkExpr();
		}
		// , abc
		else if (tokens[line][cursor].type == TokenType::SEPERATOR && tokens[line][cursor + 1].type == TokenType::IDENTIFIER){
			check(TokenType::SEPERATOR);
			check(TokenType::IDENTIFIER);
			checkExpr();
		}	
		// , "Hello world"
		else if (tokens[line][cursor].type == TokenType::SEPERATOR && tokens[line][cursor + 1].type == TokenType::STRING){
			check(TokenType::SEPERATOR);
			check(TokenType::STRING);
			checkExpr();
		}
		
		else if (tokens[line][cursor].type == TokenType::RELATIONAL && tokens[line][cursor + 1].type == TokenType::NUMBER && tokens[line][cursor + 2].type != TokenType::RELATIONAL){
			check(TokenType::RELATIONAL);
			check(TokenType::NUMBER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::RELATIONAL && tokens[line][cursor + 1].type == TokenType::IDENTIFIER && tokens[line][cursor + 2].type != TokenType::RELATIONAL){
			check(TokenType::RELATIONAL);
			check(TokenType::IDENTIFIER);
			checkExpr();
		}		
		else if (tokens[line][cursor].type == TokenType::RELATIONAL && tokens[line][cursor + 1].type == TokenType::STRING && tokens[line][cursor + 2].type != TokenType::RELATIONAL){
			check(TokenType::RELATIONAL);
			check(TokenType::STRING);
			checkExpr();
		}		
	}
	
	
	// Relational Operations
	else if (tokens[line][cursor - 1].type != TokenType::NUMBER && tokens[line][cursor - 1].type != TokenType::IDENTIFIER && tokens[line][cursor - 1].type != TokenType::STRING){
		if (tokens[line][cursor].type == TokenType::NUMBER && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::NUMBER){
			check(TokenType::NUMBER);
			check(TokenType::RELATIONAL);
			check(TokenType::NUMBER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::NUMBER && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::IDENTIFIER){
			check(TokenType::NUMBER);
			check(TokenType::RELATIONAL);
			check(TokenType::IDENTIFIER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::NUMBER){
			check(TokenType::IDENTIFIER);
			check(TokenType::RELATIONAL);
			check(TokenType::NUMBER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::IDENTIFIER){
			check(TokenType::IDENTIFIER);
			check(TokenType::RELATIONAL);
			check(TokenType::IDENTIFIER);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::IDENTIFIER && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::STRING){
			check(TokenType::IDENTIFIER);
			check(TokenType::RELATIONAL);
			check(TokenType::STRING);
			checkExpr();
		}
		else if (tokens[line][cursor].type == TokenType::STRING && tokens[line][cursor + 1].type == TokenType::RELATIONAL && tokens[line][cursor + 2].type == TokenType::STRING){
			check(TokenType::STRING);
			check(TokenType::RELATIONAL);
			check(TokenType::STRING);
			checkExpr();
		}
	}
	
	
	

	
	
	else if (tokens[line][cursor].type == TokenType::KEYWORD){
		
		if (tokens[line][cursor].str_value == "else"){
			if (conditional_statements.empty()){
				ErrorLog::ElseWithoutIf(tokens[line][cursor].word, tokens[line][cursor].line);
				success = false;
				return;
			}
			conditional_statements.pop();
		}
		
		check(TokenType::KEYWORD);
		if (tokens[line][cursor].type == TokenType::KEYWORD){
			checkExpr();
		}
		
		
		
	}
	
	
	
}

bool Parser::parse(){
	
	
	int token_len = tokens.size();
	
	while (line < token_len){
		
		cursor = 0;
		if ((int)tokens[line].size() > 0){
			checkExpr();
			if (tokens[line][cursor].type != TokenType::LINE_END && tokens[line][cursor].type != TokenType::BRACE_BEGIN /*&& tokens[line][cursor].type != TokenType::BRACE_END*/){
				
				ErrorLog::Unexpected(tokens[line][cursor].str_value, tokens[line][cursor].word, tokens[line][cursor].line);
				
				success = false;
			}else{
				
				if (tokens[line][cursor].type == TokenType::LINE_END) check(TokenType::LINE_END);
				
				if (tokens[line][cursor].type == TokenType::BRACE_BEGIN) { 
					check(TokenType::BRACE_BEGIN);
					braces.push(TokenType::BRACE_BEGIN);
				}
				
//				if (tokens[line][cursor].type == TokenType::BRACE_END) {
//					check(TokenType::BRACE_END);
//					if (braces.size() < 1){
//						cout<<"[x] Some of braces are not closed correctly until "<<(tokens[line][cursor].word, tokens[line][cursor].line)<<endl;
//						success = false;
//
//					}
//					if (braces.size() > 0 && braces.top() == TokenType::BRACE_BEGIN) braces.pop();
//					
//				}
				
				if (cursor < (int)tokens[line].size() - 1) {
					
					ErrorLog::Unexpected(tokens[line][cursor].str_value, tokens[line][cursor].word, tokens[line][cursor].line);
					success = false;
					
				}
			}
		}
		if (!rounds.empty()){
			ErrorLog::RoundError(tokens[line][cursor].word, tokens[line][cursor].line);
			success = false;
			break;
		}	
		line++;
	}


	if (success && braces.size() > 0){
		ErrorLog::BraceError(tokens[line - 1][cursor].word, tokens[line - 1][cursor].line);
		success = false;
	}
	
//	cout<<"Parsed.."<<endl;
	return success;
}