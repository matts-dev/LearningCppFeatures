// Classes in two files; demonstrating implementation file
//Matt Stone 6/16/16

#include<iostream>
#include"TwoFileClass.hpp"
using namespace std;

TwoFileClass::TwoFileClass(){
	cout << "constructor called" << endl;
}

//~ is part of the function name
TwoFileClass::~TwoFileClass(){
	cout << "deconstructor called" << endl;
}

//notice how scope resolution operators are needed to determine methods location
void TwoFileClass::talk(){
	cout << this << ":HI!!!!" << endl;
}

