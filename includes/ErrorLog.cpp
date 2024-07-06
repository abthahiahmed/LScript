#include "ErrorLog.hpp"


ErrorLog::ErrorLog()
{
	
}

void ErrorLog::TypeError(int t1, int t2, int word, int line){
	cout<<"[x] Type Error : '"<<type_to_string(t1)<<"' assigning to '"<<vtype_to_string(t2)<<"'. Value type must be same as variable type at line "<<line<<endl;

}
void ErrorLog::OnlyNumber(int word, int line){
	cout<<"[x] Type Error : Only numbers are allowed for arithmetic operations at line "<<line<<endl;

}
void ErrorLog::Undefined(string t, int word, int line){
	cout<<"[x] Identifier '"<<t<<"' is undefined at line "<<line<<endl;

}
void ErrorLog::Unexpected(string t, int word, int line){
	cout<<"[x] Unexpected token '"<<t<<"' at line "<<line<<endl;

}
void ErrorLog::Redeclared(string t, int word, int line){
	cout<<"[x] Identifier '"<<t<<"' could not be redeclared at line "<<line<<endl;

}
void ErrorLog::WrongToken(int t1, int t2, int word, int line){
	cout<<"[x] Expected '"<<type_to_string(t1)<<"', '"<<type_to_string(t2)<<"' given at line "<<line<<endl;

}

void ErrorLog::EndOfLine(int word, int line){
	cout<<"[x] Unexpected end of line at line "<<line<<endl;

}

void ErrorLog::ConditionError(int t1, int t2, int word, int line){
	cout<<"[x] Condition could not be solved between "<<type_to_string(t1)<<" and "<<type_to_string(t2)<<" at line "<<line<<endl;
}

void ErrorLog::NonIdentifier(int word, int line){
	cout<<"[x] Expected Identifiers but non-identifier given at line "<<line<<endl;
}

void ErrorLog::BraceError(int word, int line){
	cout<<"[x] Some of braces are not closed correctly until "<<(line)<<endl;
}

void ErrorLog::RoundError(int word, int line){
	cout<<"[x] Some of round brackets are not closed correctly until at line "<<(line)<<endl;
}

void ErrorLog::ElseWithoutIf(int word, int line){
	cout<<"[x] Conditional statment 'else' with out 'if' at line "<<line + 1<<endl;
}
void ErrorLog::OutOfIndex(int word, int line){
	cout<<"[!] Index of array out of length at line "<<line + 1<<endl;
}


ErrorLog::~ErrorLog()
{
}

