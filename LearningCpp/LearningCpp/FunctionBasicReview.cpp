// Functions Basic Review
//Matt Stone 6/18/2016

#include<iostream>
using namespace std;

//a function's type must be prototyped if it is used before defined in file
void funct2();

//this prototype is not NECESSARY (other was), but it's probable good practice to define everything before it is used (generally in header file)
void func();	

void func(void){
	//we call function here, before its definition; hence the need for prototype.
	funct2();
}

//parenthesis are: "function call operator"
void funct2(){
	cout << "function called" << endl;
}