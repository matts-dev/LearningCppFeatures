#include<iostream>
#include "InheritImpl.h"


//forward declarations are not enough to expose members functions for hidden types (nor do they convey enough size information to store an instance on the stack)
//also, this forward declaration does not convey that it is an extension of InheritImpl; that information is local to InheritImpl's .cpp
class InheritImpl_implementation; 

static int main_v()
{
	InheritImpl* ptr = GetNewInstance();
	ptr->do_work();
	delete ptr;


	//InheritImpl_implementation this_is_incomplete_type;
	//this_is_incomplete_type.do_work();

	//InheritImpl_implementation* still_doesntwork = (InheritImpl_implementation)ptr; //cannot c-style cast to implementation either! Looks to be pretty tough to find a way to access that type! (rightly so, this is mostly me trying to find a way to circumvent the alternative to pimple)

	std::cin.get();
}