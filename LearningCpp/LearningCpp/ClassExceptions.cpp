//review of exceptions
//Matt Stone 6/27/16

#include<iostream>
#include<exception>
#include<string>

using namespace std;
class CException : public exception {
	const char* msg = nullptr;
public:
	//constructors
	CException(const char* str) throw() :msg(str){}	//throw means this will not throw exception
	const char* what() const throw() { return msg; }

};

class breakme{
public:
	breakme(string str) { if (str.length() <= 0) throw CException("empty string exception"); }
};

void classExceptions(){
	try{
		breakme invalid("");
		cout << "you shouldn't see this code if you did a bad constructor" << endl;
	}
	catch (exception &e){
		cout << e.what() << endl;
	}
}

//self test
//write an exception class that inherits from exception
//write the constructor to accept a constant char* string and set it as the error
//overload what, be careful what return type and qualifiers should be associated with the method
