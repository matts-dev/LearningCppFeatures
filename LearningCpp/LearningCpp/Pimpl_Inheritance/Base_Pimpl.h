#pragma once
class Base_Pimpl 
{
private:
	//we can't forward declare the Imple like this (same line as ptr declaration)...
	class SomeClassYXZ* ptr; //can't forward imple like this...

protected: //normally will be PRIVATE, this is to prove a point about inheritance: even a protected base implementation can't be used because it is an incomplete type
	//we must separately forward declare it, this allows us to scope Implementation to be  within Base_Pimpl class, 
	//we want to scope it in Base_Pimpl because so we don't want linker name classes with other classes following the pimple idiom
	struct Implementation;
	Implementation* pimpl;

public:
	Base_Pimpl();
	virtual ~Base_Pimpl();

	virtual void publicVirtualMethod();

protected:
	virtual void protectedVirtualMethod();
};

