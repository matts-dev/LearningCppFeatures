#pragma once
#include <iostream>


//will each translation units get a copy of this, or will they share a single body?
template <typename T>
void templateCall(T parm)
{
	static int numTimesCalled = 0;
	numTimesCalled++;

	std::cout << numTimesCalled << std::endl;
}