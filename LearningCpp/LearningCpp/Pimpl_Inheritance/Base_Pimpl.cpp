#include "Base_Pimpl.h"
#include <iostream>

class SomeClassYXZ
{

};

//No one can see or use this implemenation class! Also, changes to it
//do not cause recompiles for any class/cpp using the Base_Pimpl header!
struct Base_Pimpl::Implementation
{
	int super_secret_data = 1244215;
	void private_method()
	{
		std::cout << "base: internal method call not exposed to header" << std::endl;
	}
};

Base_Pimpl::Base_Pimpl()
{
	//cpp98 style of pimple
	pimpl = new Base_Pimpl::Implementation;
	ptr = new SomeClassYXZ;
}


Base_Pimpl::~Base_Pimpl()
{
	delete pimpl;
	delete ptr;
}

void Base_Pimpl::publicVirtualMethod()
{
	std::cout << "Base Method: public" << std::endl;
	protectedVirtualMethod();
}

void Base_Pimpl::protectedVirtualMethod()
{
	std::cout << "Base Method: protected" << std::endl;
	pimpl->private_method();
}
