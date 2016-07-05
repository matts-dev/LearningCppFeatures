//Conversion Operator
//Matt Stone 6/26/16
#include<iostream>
#include<string>
#include<sstream>
#include"DummyClass.h"

using namespace std;

class ComplexClass{
private:
	int n = 0;
	int d = 1;
public:
	explicit ComplexClass(int n = 0, int d = 1) : n(n), d(d){}	//allows implicit assignment of non-fraction
	friend ostream& operator<<(ostream& os, const ComplexClass& obj);
	//Conversion Operator
	operator std::string () const;
	operator DummyClass () const { return DummyClass(n); }
};

ostream& operator<<(ostream& os, const ComplexClass& obj){
	os << obj.n << '/' << obj.d;
	return os;
}

ComplexClass::operator std::string() const {
	stringstream ss;
	ss << n << '/' << d;
	string result;
	ss >> result;
	return result;	
}


void conversionOp(){
	ComplexClass a12(7, 14);
	string str = "The fraction is: ";
	str += a12;		//type conversion to string using conversion operator
	cout << str << endl;

	//this is calling the copy constructor in DummyClass, there is typeconversion to dummy class using conversion operator on a12
	DummyClass copyconstr(a12);
	cout << "class from conversion operator has value (numerator): "
		<< copyconstr.getValue() << endl;

}


//self test
// what is a conversion operator?						<essentially, a user defined type case>
// write a conversion operator for a string (toString)	
// what is a conversion operator's return type?			<it has no return type, it is refered from its function name>
// what parameters does a conversion operator allow?	<none, it should not have ANY parameters>
// what must the function name be of the conversion operator?		<it should be the name of the type returned>
// Can you write a conversion operator for another class?			<yes>
// write a conversion operator for another class