#include<iostream>
#include "Upimpl.h"

static int main_v()
{
	//this requires .h and .cpp files, so the item refers to a class that is defined in another file (upimpl.h)
	Upimpl obj;

	obj.foo();

	//fields exist in the implementation file
	obj.setX(5);
	bool value_what_was_set = 5 == obj.getX();

	std::cin.get();
}