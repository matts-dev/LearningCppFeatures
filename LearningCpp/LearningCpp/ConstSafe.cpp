//Const safe methods for classes
//Matt Stone 6/7/16
#include<iostream>
#include<stdio.h>

using namespace std;

namespace constSafe{
	class A {
		int x = 99;	//private is default
	public:
		void talk(){ cout << "talking" << endl; }
		int getX(){ return x; };
		void setX(int x){ this->x = x; }
	};

	class B_constProtected {
		int x = 99;
	public:
		int getX() const { puts("constsafe method called"); return x; };
		void setX(int x){ this->x = x; }
		//compiler prevents allowing const method from changing values <below>
		//void trick(const int x) const{ this->x = x; }; 
	};

	class C_constOptionalMethods {
		int x = 99;
	public:
		void setX(const int& x){ this->x = x; }
		int getX(){ cout << "not constsafe called:"; return x; }
		int getX() const { cout << "constsafe called:"; return x; };
	};
	
} // ending namespace


void constsafe(void){
	//Normal class without any const safe
	cout << "Normal class, without const protection" << endl;
	constSafe::A mutObject;
	mutObject.talk();
	cout << mutObject.getX() << " is the default x" << endl;
	mutObject.setX(44);
	cout << mutObject.getX() << " is the new x" << endl;
	cout << endl << endl;

	//cannot call methods, because this class doesn't have const-safe methods
	const constSafe::A	constObj;
		//constObj.getX();	//method is not constsafe! compiler error
		//constObj.setX();	//method is not const safe! compiler error

	//CONST SAFE CLASS - class with constsafe methods
	cout << "using a const safe class" << endl;

	//non-const objects still work like normal
	constSafe::B_constProtected mutObj2;
	mutObj2.setX(11);
	mutObj2.getX();

	//const objects can only use const-safe methods
	const constSafe::B_constProtected constObj2;
	constObj2.getX();
	//constObj2.setX(); const objects cannot use non-const safe methods
	cout << endl << endl;


	cout << "overloading methods with const safe version, creates optional methods" << endl;
	//You can define two versions of the same method, one for consts, one for muts
	constSafe::C_constOptionalMethods mutObj3;
	const constSafe::C_constOptionalMethods constObj3;

	cout << "mut object.getX():\t";
	cout << mutObj3.getX() << endl;

	cout << "const object.getX():\t"; 
	cout << constObj3.getX() << endl;

	
}


//self check assessment
//create a class that has const safe methods
//will a normal intance use const safe methods? <yes>
//can a const instance of a class use non-const methods in any situation? <no>
//if there exists a const version of a method, and a non-const version (same identifier), which one will be used?
//			either, a mutable object will use mutable method; a const object will use const method
//write a mutable object and a const object and have them  call the same method (but having a const version for theconst object)