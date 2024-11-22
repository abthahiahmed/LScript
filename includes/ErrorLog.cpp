#include "ErrorLog.hpp"


ErrorLog::ErrorLog()
{
	
}

void ErrorLog::TypeError(int t1, int t2, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Type Error : '"<<type_to_string(t1)<<"' assigning to '"<<vtype_to_string(t2)<<"'. Value type must be same as variable type at line "<<line<<endl;
	else
		cout<<"[x] টাইপ এরর : '"<<type_to_string(t1)<<"'-কে অ্যাসাইন করা হচ্ছে "<<vtype_to_string(t2)<<" হিসেবে । ভ্যালু টাইপ অবশ্যই ভ্যারিয়েবল টাইপের সাথে মিল হতে হবে। লাইন নম্বর "<<line<<endl;
}
void ErrorLog::OnlyNumber(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Type Error : Only numbers are allowed for arithmetic operations at line "<<line<<endl;
	else
		cout<<"[x] টাইপ এরর : শুধুমাত্র নাম্বার ব্যবহার করে গাণিতিক কার্যক্রম সম্ভব। লাইন নম্বর "<<line<<endl;

}
void ErrorLog::Undefined(string t, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Identifier '"<<t<<"' is undefined at line "<<line<<endl;
	else
		cout<<"[x] আইডেন্টিফাইর '"<<t<<"'-টি ডিফাইন করা হয়নি। লাইন নম্বর "<<line<<endl;

}
void ErrorLog::Unexpected(string t, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Unexpected token '"<<t<<"' at line "<<line<<endl;
	else
		cout<<"[x] '"<<t<<"' টোকেনটি অপ্রত্যাসিত। লাইন নম্বর "<<line<<endl;

}
void ErrorLog::Redeclared(string t, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Identifier '"<<t<<"' could not be redeclared at line "<<line<<endl;
	else
		cout<<"[x] আইডেন্টিফাইর '"<<t<<"'-টি পুনরায় ডিক্ল্যার করা সম্ভব নয়। লাইন নাম্বার "<<line<<endl;
}
void ErrorLog::WrongToken(int t1, int t2, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Expected '"<<type_to_string(t1)<<"', '"<<type_to_string(t2)<<"' given at line "<<line<<endl;
	else 
		cout<<"[x] হওয়া উচিৎ '"<<type_to_string(t1)<<"' কিন্তু '"<<type_to_string(t2)<<"' দেওয়া হয়েছে। লাইন নাম্বার "<<line<<endl;
}

void ErrorLog::EndOfLine(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Unexpected end of line at line "<<line<<endl;
	else 
		cout<<"[x] লাইন সঠিকভাবে সম্পূর্ন হয়নি। লাইন নাম্বার "<<line<<endl;
}

void ErrorLog::ConditionError(int t1, int t2, int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Condition could not be solved between "<<type_to_string(t1)<<" and "<<type_to_string(t2)<<" at line "<<line<<endl;
	else
		cout<<"[x] "<<type_to_string(t1)<<" এবং "<<type_to_string(t2)<<" এর মধ্যে শর্ত সমাধানযোগ্য নয়।  লাইন নাম্বার "<<line<<endl;
}

void ErrorLog::NonIdentifier(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Expected Identifiers but non-identifier given at line "<<line<<endl;
	else
		cout<<"[x] আইডেন্টিফাইর এর বদলে নন-আইডেন্টিফাইর দেওয়া হয়েছে। লাইন নাম্বার "<<line<<endl;
}

void ErrorLog::BraceError(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Some of braces are not closed correctly until "<<(line)<<endl;
	else
		cout<<"[x] কিছু ব্র্যাকেট বন্ধ করা হয়নি। লাইন নম্বর "<<(line)<<endl;
}

void ErrorLog::RoundError(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Some of round brackets are not closed correctly at line "<<(line)<<endl;
	else
		cout<<"[x] কিছু প্রথম ব্র্যাকেট বন্ধ করা হয়নি। লাইন নাম্বার "<<(line)<<endl;
}

void ErrorLog::ElseWithoutIf(int word, int line){
	if (debugLanguage == "en")
		cout<<"[x] Conditional statment 'else' with out 'if' at line "<<line + 1<<endl;
	else
		cout<<"[x] কন্ডিশনাল স্টেটমেন্ট 'if' ছাড়া 'else' ব্যবহার করা হয়েছে। লাইন নাম্বার "<<line + 1<<endl;
}
void ErrorLog::OutOfIndex(int word, int line){
	if (debugLanguage == "en")
		cout<<"[!] Index of array out of length at line "<<line + 1<<endl;
	else
		cout<<"[!] অ্যারে এর ইনডেক্স তার সর্বোচ্ছ দৈর্ঘ্য হতে বেশি হয়ে গিয়েছে। লাইন নাম্বার "<<line + 1<<endl;
}


ErrorLog::~ErrorLog()
{
}

