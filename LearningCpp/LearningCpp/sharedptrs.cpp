//Shared ptrs basics
//Matt Stone 7/15/16

#include<iostream>
#include<memory>
#include"verboseclasses.h"
#include"DummyClass.h"
#include<utility>	//for swap
using namespace std;
using sptrs::Base;
using sptrs::Derived;

//shared pointers only call the delete function when the user_count (reference count) becomes zero

void ptrs_shared() {
	// ----------------------------- CREATING SHARED POINTERS -----------------------------
	cout << " ----------------------------- CREATING SHARED POINTERS -----------------------------" << endl;
	//shared pointers can be created using their constructors
	shared_ptr<Base> sptr1(new Base);		//this is the way I prefer to make them, though I believe make_shared is the standard way
	shared_ptr<Base> sptr2(new Derived);	//This method of assignment is not exception safe 
	sptr1->speakV();
	sptr2->speakV();

	//best way to make a shared pointer
	shared_ptr<DummyClass> exceptSafe = make_shared<DummyClass>(1, false); //exception safe, combines creation of object and pointer in 1 step		

	//------ CUSTOM DELETER ---- (using lambda function at end, but function could be defined somewhere else)
	//shared_ptr<Base> smartBasePtr = shared_ptr<Base>(new Base, [](Base* p) {cout << "deleted"; delete p; });

	//------- DELETE[] ---- deleting an shared pointer to an array requires a custom deleter
	//shared_ptr<Base> arraySPtr(new Base[3], [](Base* ptr) {cout << "del[]"; delete[] ptr; });

	//creating a nullptr
	shared_ptr<Base> nullptrdemonstration;	//will behave like nullptr in if statements

	//shared pointers can be created using make_shared
	shared_ptr<DummyClass> dcptr1 = make_shared<DummyClass>(1, false);	//pass constructor arguments in this argument (compile time error args don't match)
	dcptr1->saySomething(); cout << endl;

	//assignment operators
	shared_ptr<Base> sptr4 = sptr2;	//creates a new shared pointer pointing to object

	//WARNING - BELOW IS BAD CODE; below circumvent updating user_count, do not do it!
	//shared_ptr<Base> sptr3 = make_shared<Base>(*sptr2);	//get object from another shared pointers raw ptr

	//getting raw pointers (ADVISED AGAINST - makes user_count invalid)
	Base* bptr = &(*sptr2);	//getting normal ptr, again -- this is bad!
	//Base* bptr = sptr2;	//INVALID; cannot get normal ptr this way. Must dereference object, then get address
	//sptr2.get()->speakV();	//.get() returns a raw pointer

// ---------------------------- USING SHARED PTRS -----------------------------
	cout << "----------------------------- USING SHARED POINTERS -----------------------------" << endl;

	//there can be multiple shared pointers pointing to an object
	auto dcptr2 = dcptr1;
	//you can print how many shared pointers point to an object
	cout << "there are " << dcptr1.use_count() << "shared pointers pointing to this object." << endl;

	//demonstrate how sptr3 can circumvent user_count by getting a raw pointer, then making new shared pointer from raw ptr
	//cout << sptr2.use_count() << endl;
	//cout << sptr3.use_count() << endl;

	//GET() function	returns raw pointer (samething as dereferncing, then taking address)
	cout << "\nusing get() to get the adr of the object" << endl;
	dcptr1.get()->saySomething();
	cout << endl;	//newline


	//equal operators
	cout << endl << "analyzing equal operators" << endl;
	cout << "(sptr2 == sptr4) is: " << (sptr2 == sptr4) << endl;
	cout << "(*sptr2 == *sptr4) is: " << (sptr2 == sptr4) << endl << endl;

	//using usecount
	cout << "sptr4 is: " << sptr4.get() << ".\nsptr2 is: " << sptr2.get() << endl;
	cout << "sptr2 user count of: " << sptr2.use_count() << endl;
	sptr4.reset();	//reduces user count
	cout << "reset() sptr4" << endl;
	cout << "sptr2 user count of: " << sptr2.use_count() << endl << endl;

	/* //below shows that reseting with a new instance also drops user count
	sptr4 = sptr2;
	cout << "set sptr4 to sptr2" << endl;
	cout << "sptr2 user count of: " << sptr2.use_count() << endl;
	cout << "resting sptr4 with a new instance" << endl;
	sptr4.reset(new Base);
	cout << "sptr2 user count of: " << sptr2.use_count() << endl;

	//cout << "attempting to call dtor if following use_count is 1:" << sptr2.use_count() << endl;
	//sptr2.reset(); //calls dtor since user count is 0	//WARNING - make cause issues later in program

	*/

	//swaping - esotrics 
	/*
	cout << endl << "swapping operations" << endl;
	auto ptrA = make_shared<Base>();
	shared_ptr<Base> ptrB = make_shared<Derived>();
	cout << "done with constructors for swaping" << endl;
	ptrA.swap(ptrB);	//no constructors called when using smart pointer member function of swap
	swap(ptrA, ptrB);	//no contructors on
	*/
	//cout << "dtor called when using objects, implicit copy constructor?" << endl;
	//swap(*ptrA, *ptrB);

	// ---------------------------- DYNAMIC CAST ----------------------------
	cout << "----------------------------- DYNAMIC CASTS -----------------------------" << endl;
	//static_pointer_cast<type>(sPtr)			// use these functions for casts like normal pointers
	//const_pointer_cast<type>(sPtr)
	//dynamic_pointer_cast<type>(sPtr)



	//creating a variable for casting (easily shows a hidden derived pointer)
	shared_ptr<Base> polyDerivedPointer = sptr2;

	// ------- DYNAMIC_POINTER_CAST METHOD--- - The ideal way of dynamically casting smart pointers
	shared_ptr<Derived> castSharedPtr;	//no arguments will point to nullptr;

	//syntax: newCastedPointerType = dynamic_pointer_cast<CLASSTYPE, not sharedptr type> (shared pointer to cast from);
	//castSharedPtr = dynamic_pointer_cast<Derived>(sptr1); // invalid cast, dyn type is base
	castSharedPtr = dynamic_pointer_cast<Derived>(polyDerivedPointer);	//valid cast, dyn type is derived

	if (castSharedPtr) {
		cout << "dynamic_pointer_cast passed" << endl;
		castSharedPtr->speakV();
	}
	else { cout << "dynamic_pointer_cast failed" << endl; }
	// ----------------------------------------------------------------------------------------

	// ------- RAW PTR METHOD- Not recommended.  method to check if subclass: get temp raw pointer, dyn cast, check, do work, then abandon raw ptr
	Base* tempPtr1 = &*sptr2;
	Derived* tempPtr2 = dynamic_cast<Derived*>(tempPtr1);		//you can combine the the line above
	if (tempPtr2 != nullptr) {	//could just use if(tempPtr2), but i'm being explicit
		cout << "valid cast";
		tempPtr2->speakV();
	}
	tempPtr1 = nullptr; //abandon dangling ptr to ensure smart_pointers stay valid
	// ----------------------------------------------------------------------------------------



}

//selftest (using verboseclasses.h)
//create a shared pointer using the shared pointer constructor
//create a shared pointe using make shared. How do you pass arguments to the constructor?
//do a dynamic pointer cast to a derived type 
//write a shared pointer that points to nullptr (implicitly)
//safely create a new shared pointer that will update user_count
//use reset to manually drop the user count

//questions
//what does the get() function return?												<a raw pointer>
//what happens when you get a raw pointer, then make a new shared ptr from it?		<you corrupt the user_count, making separate shared ptrs>
//what happens when you call reset on a use_count of 1?								<it calls dtor>