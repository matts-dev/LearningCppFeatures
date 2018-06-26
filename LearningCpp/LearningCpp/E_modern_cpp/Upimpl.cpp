#include <iostream>
#include "Upimpl.h"

//no one can access this or know the layout of this struct without having the .cpp!
//also changing this doesn't require clients of the Upimpl.h header recompile
struct Upimpl::Implementation
{
	//private fields
	int x;

	//private methods for Upimpl go here; they cannot be seen/accessed by clases/cpps outside of this translation unit (.cpp)
	void private_method()
	{
		std::cout << "private method of Upimpl that follows the pimpl idiom" << std::endl;
	}
};

//------------------------------------------------------------------

Upimpl::Upimpl() noexcept
{
	//using unique pointers means that you don't need call delete in the dtor!
	pimpl = std::make_unique<Upimpl::Implementation>();
}

Upimpl::Upimpl(Upimpl&& move) noexcept : pimpl(nullptr)
{
	//moves require careful attention!
	//in this case, if an exception arises -- the move ctor must be able to delete the pimpl; which is which the move ctor must be defined in the .cpp of implementation struct

	//you can just move the entire pointer!
	pimpl = std::move(move.pimpl);
}

Upimpl::Upimpl(const Upimpl& copy) noexcept : pimpl(nullptr)
{
	if (copy.pimpl)
	{
		this->pimpl = std::make_unique<Upimpl::Implementation>(*(copy.pimpl));
	}
}

Upimpl& Upimpl::operator=(const Upimpl& copy) noexcept
{
	if (!copy.pimpl)
	{
		//copy was null, set this to null
		pimpl.reset();
	}
	else if (!this->pimpl)
	{
		//there isn't a previous implementation to remove
		pimpl = std::make_unique<Implementation>(*copy.pimpl);
	}
	else
	{
		//use copy assignment operator
		*pimpl = *copy.pimpl;
	}
	return *this;
}

Upimpl& Upimpl::operator=(Upimpl&& move) noexcept
{
	//must be definied in .cpp of implementation struct for deleting destination's pre-move implementation poitner

	//again, just move the entire pointer! :3
	pimpl = std::move(move.pimpl); //this will call move ctor and null out the move.pimpl
	return *this;
}

//Unique_Ptr NEEDS to see this defintion...
//uptr has its deleter as part of its signature... and it has a static_assert to check if it is deleting an incomplete type
//however, if the declaration of std::make_unique sees this code, it can delete it!
Upimpl::~Upimpl()
{
	//in cpp11 pimpl, nothing to delete since the unique pointer dtor will be called here (which will take of deleting our dynamically allocated memory!)

	//note: in this .cpp, implementation is defined, so when the dtor for unique_ptr is inserted in this scope, it will be able to delete
	//the implementation struct because it isn't an incomplete type!
}

void Upimpl::foo()
{
	pimpl->private_method();
}

int Upimpl::getX()
{
	return pimpl->x;
}

void Upimpl::setX(int newX)
{
	pimpl->x = newX;
}

//note that a lot of the work required (ie defining bodies within .cpp of the implementation struct) to get set up for pimpl with unique pointers isn't required for shared pointers 
//because shared pointers don't use deleters in their type. But you should use a uniqueptr because it is more appropriate (ie exclusive ownership)