//Operator functions, ie operator overloading (ad-hoc polymorphism)
//Matt Stone 6/20/2016

#include<iostream>
#include"DummyClass.h"

using namespace std;

int operator + (DummyClass& lhs, DummyClass&rhs);
int operator ! (DummyClass& rhs);

void operators(){
	DummyClass A(43);
	DummyClass B(22);
	cout << A + B << endl;
	cout << !A << endl;
}


int operator + (DummyClass& lhs, DummyClass&rhs){
	cout << "operator overload for + called" << endl;
	int left = lhs.getValue();
	int right = rhs.getValue();
	return (left + right);	
}

int operator ! (DummyClass& rhs){
	int value = rhs.getValue();
	value = !value;
	return value;
}


//Self Check Test
//Write operator overload for +
//Write operator overlaod for -
//write operator overload for *
//write operator overload for /
//