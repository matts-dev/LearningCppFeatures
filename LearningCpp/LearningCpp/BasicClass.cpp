//Basic class and use in single file 
//Matt Stone 6/16/2016

#include<iostream>

using namespace std;

class Basic{
	//fields default to private
	//int x;

	//you can make things private expicitly
private:
	//placing a constructor in private restricts its use
	Basic(){
		;//you must still define the constructor if you don't want to use it
	};
public:
	//force user to use a argument constructor
	Basic(int value){ cout << "constructed with " << 1 << endl; };
	void talk(){ cout << "object talking" << endl; }
protected:
	int c;
}; //c++ classes must end in semicolon

void basicClass(void){
	Basic basicClass(1);
	Basic* ptr = new Basic(1);

	//using public methods
	basicClass.talk();
	ptr->talk();

	//Basic invalid;	//no arg constructor is private

	delete ptr;
}

//self test
//write a complete class, and instantiate it in a method.
//create a public variable and public function, use them in a method
//create a private variable and private method used in a public function; use it.
