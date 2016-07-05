// Matt Stone (c)
#include<iostream>
void references(void){
	int x = 1;
	int y = 2;
	int z = 3;
	std::string str1 = "str1";
	std::string str2 = "str2";

	//Reference vs pointer
	int* ptr = &x;	//needs address operat
	int& ref = x;	//needs variable

	//Pointers need to be dereferenced
	std::cout << "x ptr: " << *ptr << std::endl;

	//References are treated like normal variables; no dereference
	std::cout << "x ref: " << ref << std::endl;

	//Pointers can be changed
	ptr = &y;

	//References are essentially immutable; this is an assignment
	ref = y;

	//Attempting to change a reference creates an assignment
	std::cout << "x ptr: " << *ptr << std::endl;
	std::cout << "x ref: " << ref << std::endl;


}
