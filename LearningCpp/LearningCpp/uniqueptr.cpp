//Unique ptr
//Matt Stone 7/14/16

#include<iostream>
#include<memory>
#include<typeinfo>
#include"verboseclasses.h"

using namespace std;

//Unique pointers do not allow other pointers to point to an object
//Unique pointers are lightweight - use them if possible (in preference to other smart pointers)
//When to use unique pointers - use when there will be only 1 pointer to an object

//Smart pointers take care of memory cleanup for you!!! no need to delete. :)


//prototypes
void speakifderived(unique_ptr<sptrs::Base>& ptr);

//Main
void uniquePtrs() {

	// -------------------------- BASIC POINTERS --------------------------
	//create a new instance of base, held in an unique pointer
	unique_ptr<sptrs::Base> bptr1(new sptrs::Base());

	//use the unique pointer just like a normal pointer
	bptr1->speakV();

	// -------------------------- ALTERNATIVE INSTANTIATION --------------------------

	//make unique function - anothe way to create a unique ptr
	auto bptr2 = make_unique<sptrs::Base>();
	bptr2->speakV();

	// -------------------------- USING UNIQUE POINTER --------------------------

	//reset method can be used to destroy an object
	bptr1.reset();
	bptr2.reset(new sptrs::Base());//reset method can be used to destroy, and make a new object

	//moving a unique pointer
	unique_ptr<sptrs::Base> bptr3;
	bptr3 = move(bptr2);
	bptr3->speakV();
	

	// -------------------------------- CHECKING FOR NULLPTRS --------------------------------
	cout << "checking for nullptr";
	
	//simply check like it is a normal pointer
	if (!bptr3) {			//todo: look up how to write a class that can return true/false in like this
		cout << "nullptr" << endl;
	}	else {	cout << "non-null ptr" << endl;	}
	cout << "checking for nullptr explicitly";
	if (bptr3 == nullptr) {//or you can check like this
		cout << "nullptr" << endl;
	}
	else { cout << "non-null ptr" << endl; }


	// -------------------------------- RELEASING A POINTER --------------------------------
	//note: there is no assignment operator for other ptrs so the below code is invalid
	//bptr3 = bptr2;
	auto bptr3a = bptr3.release();	//release doesn't call dtor, but returns normal pointer
	bptr3.reset(bptr3a);
	(*bptr3).speakV();

	// -------------------------------- DELETE (CALL DTOR) ON UNQUE--------------------------------
	bptr3.reset();		//calls dtor 

	// -------------------------- POLYMORPHIC POINTERS --------------------------
	unique_ptr<sptrs::Base> bptr4(new sptrs::Derived);
	bptr4->speakV();

	unique_ptr<sptrs::Base> bptr5 = make_unique<sptrs::Derived>();
	bptr5->speakV();

	// -------------------------- PASSING UNIQUE_PTR TO FUNCT --------------------------
	cout << "passing pointers to function that uses derived" << endl;
	//bptr5 = derived
	//bptr1 = base
	bptr1.reset(new sptrs::Base);
	cout << "\nbase will have 3 calls to speakv, but one should not pass" << endl;
	bptr1->speakV();
	speakifderived(bptr1);
	bptr1->speakV();//tests if pointer was restored

	cout << "\nderived will have 3 calls to speakv, all three should pass" << endl;
	bptr5->speakV();
	speakifderived(bptr5);
	bptr5->speakV();//tests if pointer was restored
}

void speakifderived(unique_ptr<sptrs::Base>& ptr) {
	//retrieve from unique pointer
	sptrs::Base* rawPtr = ptr.release();

	//attempt a downcast
	sptrs::Derived* castPtr = dynamic_cast<sptrs::Derived*>(rawPtr);

	//check if cast was sucessful
	if (castPtr) {
		castPtr->speakV();
	}
	//restore smart pointer
	ptr.reset(rawPtr);
}