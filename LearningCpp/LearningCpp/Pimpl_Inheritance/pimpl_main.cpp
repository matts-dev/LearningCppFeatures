#include<iostream>
#include"Child_Pimpl.h"
#include "Base_Pimpl.h"

//forward declarations DON'T help with hijacking implemenations!
struct Base_Pimpl::Implementation;

static int main_v()
{
	Base_Pimpl* base = new Base_Pimpl;
	Base_Pimpl* child = new Child_Pimpl;

	base->publicVirtualMethod();
	child->publicVirtualMethod();

	//not only is it inaccessible(private), it is an incomplete type!
	//Base_Pimpl::Implementation obj; //can't snoop on the implementation!
	//Child_Pimpl::Implementation obj; //again, inaccessible and incomplete type!
	std::cin.get();
}