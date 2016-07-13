// decltype
// Matt Stone 7/13/16

#include <iostream>
#include <string>
#include <ctime>
#include "inhert.hpp"
#include <typeinfo>
#include "copyinstance.hpp"
using namespace std;

// ***see basic decltype before analyzing the below function*** it is for advance decltype type usage
// this determines the returntype after parameters are checked; what comes after -> determines return type
template <typename T, typename U>
auto trailingReturnFunct(T& lhs, U& rhs) -> decltype(lhs + rhs) {
	return lhs + rhs;
}

void decltypes() {
	// ---------------------------- BASIC DECLTYPE() ----------------------------

	//decyltype can be used to infer the type from another type
	auto knowntype = string("blue blue electric blue");

	//decltype takes another type as an argument
	decltype(knowntype) unknowntype;

	//we know that they're they same type, so we can make this assignment
	unknowntype = knowntype;

	//printing off both variables to show decltype worked.
	cout << knowntype << endl;
	cout << unknowntype << endl;

	// ---------------------------- ADVANCED DECLTYPE ----------------------------
	const char* cstr = "cstring";
	string cppstr = "cppstring";
	cout << trailingReturnFunct(cstr, cppstr) << endl;

	// ----------------------------  DECLYTYPE IS STATIC TYPE, so no polymorphism ----------------------------
	Inherit::Base* bptr;
	srand((unsigned int)time(nullptr));
	int random = rand() % 3;
	switch (random) {
		case 0:
			bptr = new Inherit::Base;
			break;
		case 1:
			bptr = new Inherit::Middle;
			break;
		case 2:
			bptr = new Inherit::Bottom;
			break;
		default:
			bptr = nullptr;
	}

	//using decyltype on polymorphic pointer?
	cout << endl << "created a: ";
	bptr->speakV();

	//create an undefined type object on stack
	decltype(*bptr) uktype = *bptr;
	uktype.speakV();
	cout << typeid(uktype).name() << endl;

	//create an undefined type object on heap
	//auto uktypeptr = new decltype(*bptr)();
	//auto uktypeptr = new std::remove_reference<decltype(*bptr)>::type(); //creates base objects, not polymorphic
	auto uktypePtr = new std::remove_pointer<decltype(bptr)>::type();	//creates base objects, not polymorphic
	//uktypeptr->speakV();

	delete bptr;
	delete uktypePtr;
}

//silly trailing return type
auto returnstring(string str) -> decltype(str) {
	return str;
}