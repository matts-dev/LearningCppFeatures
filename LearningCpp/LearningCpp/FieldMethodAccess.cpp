//Accesing members of the base class
//Matt Stone 7/5/16

//I already know the basics of access (private, protected, using accessors/gets, etc.),
//so I explored some more detailed stuff in this file (ie using virtual functions and accessing private members that way)

#include<iostream>
#include<cstdio>
using namespace std;

class Base {
public:
	void speak() { cout << "\tBase Class Speaking (to be overloaded)!" << endl; };
	virtual void virt() { cout << "\tBase class virutal" << endl; }
};

class Derived : public Base {
public:
	//overload of speak
	void speak() { cout << "\t!!Overloaded: Derived Class Speaking!!" << endl; }
	void virt() { cout << "\tchild class virtual" << endl; }
};

//This class is used to through 3 node inheritance, most examples don't use this class.
class ThreeDerived : public Derived {
private:
	void virt() { cout << "\t3rd derived private virtual" << endl; }
};

void access() {
	Derived derv;

	derv.speak();			//access the overload
	derv.Base::speak();		//acces the parent version

	cout << endl << "Using BASE CLASS Pointer (showing different between virtual)" << endl;
	Base* basePtr = &derv;

	//pointers of base class type will use base type methods, even if child has overloaded them
	basePtr->speak();

	//pointers of base class type will use the CHILD methods, if the base class specified them as virtual
	basePtr->virt();

	//you can force a base-class pointer to use its own version of a virtual using the scope resolution operator
	cout << endl << "attempting to use the base's version of the virtual function" << endl;
	basePtr->Base::virt();


	cout << endl << "for completness, here is a child pointer access the all the methods " << endl;
	Derived* dervPtr = &derv;
	dervPtr->speak();
	dervPtr->Base::speak();
	dervPtr->virt();
	dervPtr->Base::virt();

	cout << endl << "3 length inheritance" << endl;
	ThreeDerived threeDerived;
	Base* basePtr2 = &threeDerived;
	Derived* dervPtr2 = &threeDerived;
	ThreeDerived* d3Ptr = &threeDerived;

	//Base pointer
	cout << "using base pointer for virtual" << endl;
	basePtr2->virt();		//this will access a PRIVATE function, due to the fact that this is virtual

	//Derived pointer
	cout << "using derived pointer for virtual" << endl;
	dervPtr2->virt();

	//Three derived Pointer
	cout << "using 3rd derived pointer for virtual" << endl;
	//d3Ptr->virt();		//notice the last virtual function is private, 
	//d3Ptr->speak();		//will use the deepest overloaded function


}