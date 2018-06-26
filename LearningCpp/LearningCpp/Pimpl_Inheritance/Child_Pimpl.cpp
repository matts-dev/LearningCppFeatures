#include <iostream>
#include "Child_Pimpl.h"

//again, this class is local to the translation unit (ie .cpp) and no one else can use it (or see what it holds!)
struct Child_Pimpl::Implementation
{
	int super_secret_data = 1244215;
	void private_method()
	{
		std::cout << "child: internal method call not exposed to header" << std::endl;
	}
};

Child_Pimpl::Child_Pimpl()
{
	//cpp11 version of pimpl idiom!
	pimpl = std::make_unique<Child_Pimpl::Implementation>();

	//because implementation struct/classes are defined in .cpps, they're local to that translation unit
	//this means they cannot be used outside the translation unit they're defined because they will be a incomplete type...
	//no other .cpp will have the information necessary for instantiating or using the implmentation of another pimpl idiom class...
	//Base_Pimpl::Implementation obj;

	//this poses a problem for traditional inheritance...
	//You can't move protected members to the implementation struct...
	//because the child classes will not be able to see the details of the implmentation!
	//This is because, in order for a child to know the API of a parent implementation struct, it must include something to have the classes definition (not just declaration).
	//Because it is declared in the .cpp of the parent class, the child doesn't get the definition of the parent's implementation struct... Thus it can never use it!
	
	//So, I guess if you want to use inheritance and the pimpl idiom, you must go for a hybrid.
	//allow your encapsulated private members exist in implementation file, but expose your protected variables in the 
	//header so that child classes can properly use them!
}


Child_Pimpl::~Child_Pimpl()
{
}

void Child_Pimpl::publicVirtualMethod()
{
	std::cout << "Child Method: Public" << std::endl;
	protectedVirtualMethod();
}

void Child_Pimpl::protectedVirtualMethod()
{
	std::cout << "Child Method: Protected" << std::endl;
	pimpl->private_method();
}
