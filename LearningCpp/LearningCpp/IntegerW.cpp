#include"IntegerW.hpp"

IntegerW::IntegerW(int x = 0) :value(x){
	//say when constructor is called and print address
	//cout << "constructor called: " << this << endl;
}

IntegerW::~IntegerW(){
	//say when dtor is called and print address
	//cout << "dtor called: " << this << endl;
}

void IntegerW::setValue(int val){
	this->value = val;
}

int IntegerW::getValue(){
	return this->value;
}

//prefix
IntegerW& IntegerW::operator++ (){
	this->value += 1;
	return *this;
}

//postfix
IntegerW IntegerW::operator++ (int x){
	IntegerW copy(*this);	//implicit copy constructor
	++(*this);	//increment this object
	return copy;//return an old copy
}

//Non-member overloads
ostream& operator<< (ostream& ostrm, IntegerW& obj){
	ostrm << obj.value;
	return ostrm;
}




//IntegerW operator+ (IntegerW&lhs, IntegerW&rhs){
//	IntegerW test;
//	test.setValue(lhs.value + rhs.value);
//	return test;
//}
//
//IntegerW operator+= (IntegerW&lhs, IntegerW&rhs){
//	lhs.setValue(lhs.value + rhs.value);
//}