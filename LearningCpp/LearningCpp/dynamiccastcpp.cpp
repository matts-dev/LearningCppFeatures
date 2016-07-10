//Dynamic casts
//Matt Stone 7/10/16

#include<iostream>
#include<ctime>
#include"inhert.hpp"		//has a base, middle, and bottom class that are polymorphic (virtual)

using namespace std;
void dynamiccasts() {
	//create an instance of each object on stack
	Inherit::Base baseObj;
	Inherit::Middle midObj;
	Inherit::Bottom botObj;

	//pointer to the base type
	Inherit::Base* baseptr;

	//randomly make the pointer point to an object;
	srand(static_cast<unsigned int>(time(0)));
	int choice = rand() % 3;
	switch (choice) {
		case 0:
			baseptr = &baseObj;
			cout << "randomly selected base" << endl;
			break;
		case 1:
			baseptr = &midObj;
			cout << "randomly selected middle" << endl;
			break;
		case 2:
			baseptr = &botObj;
			cout << "randomly selected bottom" << endl;
			break;
		default:
			baseptr = nullptr;
			cout << "error, passing nullptr as result from random " << endl;
	}

	//determine what type the pointer refers to at runtime; if dynamic cast fails, nullptr is returned 

	if (dynamic_cast<Inherit::Bottom*>(baseptr)) {	//same thing as baseptr != nullptr
		//start with lowest subclass because dynamic cast will pass if middle subclass were checked
		cout << "the RTTI give type is bottom" << endl;	}
	else if (dynamic_cast<Inherit::Middle*>(baseptr) != nullptr) {	//show nullpointer explicitly, but since this is 0, nullptr will be false
		cout << "the RTTI given type is middle" << endl;
	}
	else if (baseptr != nullptr) {	//or just if(baseptr)
		cout << "the RTTI given type is base" << endl;
		//show that an attept to downcast it will fail
	}
	else {
		cout << "something went wrong with selecting a pointer" << endl;
	}

	//Enable the below code to see: baseptr-> bottom dyncast middle != nullptr;
	//ie you can dynamic cast a bottom object to middle object, so you should always check for the further subclass first
	/*
	if (dynamic_cast<Inherit::Bottom*>(baseptr)) {	//same thing as baseptr != nullptr
	//start with lowest subclass because dynamic cast will pass if middle subclass were checked
	cout << "the RTTI give type is bottom" << endl;
	//show that dynamic cast on base also works to cast it ot middle
	cout << "\n\ndynamic_cast to middle, ptradr:" <<  dynamic_cast<Inherit::Middle*>(baseptr) << "\nnote: 0 is nullptr" << endl;
	}
	else if (dynamic_cast<Inherit::Middle*>(baseptr) != nullptr) {	//show nullpointer explicitly, but since this is 0, nullptr will be false
	cout << "the RTTI given type is middle" << endl;
	}
	else if (baseptr != nullptr) {	//or just if(baseptr)
	cout << "the RTTI given type is base" << endl;
	//show that an attept to downcast it will fail
	cout << "\n\ndynamic_cast to middle, ptradr:" << dynamic_cast<Inherit::Middle*>(baseptr) << "\nnote: 0 is nullptr" << endl;
	}
	else {
	cout << "something went wrong with selecting a pointer" << endl;
	}
	*/


}


//self test
//Will dynamic cast work without a virtual table? (virtual tables are created with a class has virtual keyword inside)		<no, gives compile time error>


//practical 
//write a dynamic case from the base, middle, and bottom class using random <hint: include inheirt and use the classes already created>
