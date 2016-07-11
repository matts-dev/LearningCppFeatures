//exploring generic functions with RTTI
//Matt Stone 7/11/2016

#include <iostream>
#include "inhert.hpp"
#include "DummyClass.h"
#include <ctime>	
using namespace std;

//Turns out, this doesn't need RTTI - it can figure out 
template<typename T>
void polyTest(T* tPtr) {
	tPtr->speakV();
	Inherit::Bottom* botPtr = dynamic_cast<Inherit::Bottom*>(tPtr);
	if (botPtr) {	//check if pointer is nullptr
		botPtr->botOnly();
	}
};

void genFunctRtti() {
	srand(static_cast<unsigned int>(time(nullptr)));
	Inherit::Base* bPtr;

	//generate a random pointer that is polymorphic
	switch (rand() % 3) {
		case 0:
			bPtr = new Inherit::Base;
			break;
		case 1:
			bPtr = new Inherit::Middle;
			break;
		case 2:
			bPtr = new Inherit::Bottom;
			break;
		default:			
			bPtr = nullptr;
	}
	//determine which type was selected
	bPtr->speakV();	
	polyTest(bPtr);

	//Doesn't need rtti, it will figure out at compile time that at compile time there is an error
	//DummyClass x;
	//DummyClass* xptr = &x;
	//polyTest(xptr);

	delete bPtr;
}