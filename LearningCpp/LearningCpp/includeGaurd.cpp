//Include gaurding 
//Matt Stone 6/22/16

//#pragma once		//non-standrad way of doing a include guard

#ifndef _INCGAURD
#define _INCGUARD


#include<iostream>
using namespace std;

void testIncGuard(){
	cout << "I have been guarded" << endl;
}
#endif	/*end include guard for _INCGAURD*/


//self test
//write an include guard that will protect from multiple-includes