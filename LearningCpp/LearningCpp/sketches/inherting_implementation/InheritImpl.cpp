#include "InheritImpl.h"
#include <iostream>


class InheritImpl_implementation : public InheritImpl
{
	void do_work() override
	{
		std::cout << "I'm hidden in an implementation class" << std::endl;
	}

	~InheritImpl_implementation()
	{
		std::cout << "hidden implementation dtor called" << std::endl;
	}
};

InheritImpl* GetNewInstance()
{
	return new InheritImpl_implementation();
}
