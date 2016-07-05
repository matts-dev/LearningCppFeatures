//nullptr
//Matt Stone 7/3/16

//the nullptr keyword was added in c++11 because NULL was defined differently on different systems.
//NULL could have been 0, or (void*)0, etc. however, this caused ambiguity on some function calls. 
//e.g. char* param	- this would not accept a void* pointer, it only accepts char*
//e.g. int param - this would accept a zero (ie NULL), which could cause overloaded functions to be called by mistake
//nullptr works with all pointer types and removes any ambiguity 

#include<iostream>
#include<string>
using namespace std;

void useptr(string* obj);

void nullptrs(){
	string str = "happy bird man";
	string*ptr = &str;

	useptr(ptr);
	useptr(nullptr);
}


void useptr(string* obj){
	if (obj == nullptr){
		cout << "nullptr found" << endl;
	}
	else {
		cout << *obj << endl;
	}
}
