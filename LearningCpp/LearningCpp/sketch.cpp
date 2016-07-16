//file for quick testing

#include<iostream>
#include<memory>
#include"verboseclasses.h"
using namespace std;
using sptrs::Base;

//testing using {} to destroy a dangling pointer
void sketch() {
	shared_ptr<Base> smartBasePtr;
	{	//prevents dangling pointer
		Base* bptr1 = new Base;
		//smartBasePtr.reset(bptr1);	//using dangling pointer

		//attempt to make the below exception safe is to call new before
		smartBasePtr = shared_ptr<Base>(bptr1, [](Base* p) {cout << "deleted"; delete p; });
	}
	smartBasePtr->speakV();
}