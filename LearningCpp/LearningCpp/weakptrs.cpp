//Weak ptrs
//Matt Stone 7/16/16

#include<iostream>
#include<memory>
#include"verboseclasses.h"

using namespace std;
using sptrs::Base;
using sptrs::Derived;


//weak pointers do not have ownership, must request a lock, and prevent users from calling delete explicitly
//weak pointers prevent circular references
void weakptrs() {
	//shared pointer
	shared_ptr<Base> shared1 = make_shared<Base>();

	//weak pointer are created from shared pointers 
	weak_ptr<Base> weak1 = weak_ptr<Base>(shared1);

	//weak pointers cannot directly access what they point to
		//weak1->speakV();	//invalid
	weak1.lock()->speakV();	//this is how you use a weak pointer

	//lock returns a shared pointer, generally this isn't stored, but used, then ptr's dtor is called (like above)
	//below is explicitly showing what happens.
	shared_ptr<Base> shared = weak1.lock();	//this increments use_count
	shared->speakV();
	shared.reset();		//decrements use count

	//nullptr - is use_count reaches 0, then the weak pointer becomes a nullptr
	shared1.reset();	//use_count was 1, so this will call the deleter for the object
	if (weak1.lock() == nullptr) {		//weak pointers must be locked, you cannot simply check them like normal ptrs
		cout << "nullptr:" << weak1.lock() << endl;
	}
	else {
		cout << "pointer valid, count is: " << weak1.use_count() << endl;
		weak1.lock()->speakV();
	}
}


//self test
//make a weak pointer
//use a weak pointer

//what happens if a weak pointer's parent shared pointer becomes nullptr?	<the weak pointer is nullptr>
//what does the lock() function return?			<a shared pointer>



