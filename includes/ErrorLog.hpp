#pragma once
#include <iostream>
#include "Types.hpp"
#include "global.hpp"
using namespace std;

class ErrorLog
{
public:
	ErrorLog();
	~ErrorLog();
	
	static void TypeError(int t1, int t2, int word, int line);
	static void Undefined(string t, int word, int line);
	static void Redeclared(string t, int word, int line);
	static void Unexpected(string t, int word, int line);
	static void WrongToken(int t1, int t2, int word, int line);
	static void ConditionError(int t1, int t2, int word, int line);
	static void EndOfLine(int word, int line);
	static void NonIdentifier(int word, int line);
	static void OnlyNumber(int word, int line);
	static void BraceError(int word, int line);
	static void RoundError(int word, int line);
	static void ElseWithoutIf(int word, int line);
	static void OutOfIndex(int word, int line);
};

