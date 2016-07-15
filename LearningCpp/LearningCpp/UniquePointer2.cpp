//Testing with unique smart pointers
//Matt Stone 7/14/16

#include<iostream>
#include<memory>
#include"verboseclasses.h"

void testUniPointer() {
	//smart pointers are for dynamic memory management, but can they point to stack variables?
	//sptrs::Base obj1;
	//unique_ptr<sptrs::Base>uptr1(&obj1);	//yes, but this freezes the program when dtor is called
	unique_ptr<sptrs::Base> uptr1(new sptrs::Base);

	
}