//inline function 
//Matt Stone 7/9/16

#include <iostream>
using namespace std;

//inline essentially copies and pastes a function anywhere it is called into the code.
//Sine functions have their own scope, inline behaves like {} were copy and pasted


//you must put inline at the functions declaration for it to work properly
inline void foo() {//inline is a suggestion that the compiler may or may not take
	cout << "foo" << endl;
}

void inlineFunctions() {
	foo();
	foo();
	foo();
	foo();
}