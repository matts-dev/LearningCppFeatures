#include<iostream>

namespace
{
	/////////////////////////////////////////////////////////////////////////////////////
	// base class
	/////////////////////////////////////////////////////////////////////////////////////
	class Base
	{
	public:
		Base() { heapMem = new int; }
		virtual ~Base() { delete heapMem; }
		void printMemAddress() { std::cout << heapMem << "\n"; }
	private:
		int* heapMem;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	// classes that do normal inhertiance of base
	/////////////////////////////////////////////////////////////////////////////////////
	class A_Child : public Base
	{
	};

	class B_Child : public Base
	{
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// classes that virtually inherit base
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class A_Virtual_Child : public virtual Base
	{
	};

	class B_Virtual_Child : public virtual Base
	{
	};

	/////////////////////////////////////////////////////////////////////////////////////
	// permutations of inheriting
	/////////////////////////////////////////////////////////////////////////////////////

	class Inherit_Normal_NormalChild : public A_Child, public B_Child
	{
	};

	class Inherit_Virtual_NormalChild : public virtual A_Child, public virtual B_Child
	{
	};

	class Inherit_Normal_VirtualChild : public A_Virtual_Child, public B_Virtual_Child
	{
	};

	class Inherit_Virtual_VirtualChild : public virtual A_Virtual_Child, public virtual B_Virtual_Child
	{
	};

	class Inherit_Normal_BothChildren : public virtual A_Child, public B_Virtual_Child
	{
	};

	void demo()
	{
		{ //test virtual inheritance
			Inherit_Normal_VirtualChild* child = new Inherit_Normal_VirtualChild;
			A_Virtual_Child* aV = child; //pass these through the intermediate pointer to give next conversion a chance to point to something different
			B_Virtual_Child* bV = child;
			Base* aBase = aV;
			Base* bBase = bV; 
			if (aBase == bBase)
			{
				std::cout << "virtual base class pointers address match \n";
			}
			else
			{
				std::cout << "virtual base class pointers address -DON'T- match \n";
			}
			delete child;
		}

		{ //test normal inheritance
			Inherit_Normal_NormalChild* child = new Inherit_Normal_NormalChild;
			A_Child* aV = child; //pass these through the intermediate pointer to give next conversion a chance to point to something different
			B_Child* bV = child;
			Base* aBase = aV;
			Base* bBase = bV;
			if (aBase == bBase)
			{
				std::cout << "normal base class pointers address match \n";
			}
			else
			{
				std::cout << "normal base class pointers address -DON'T- match \n";
			}
			delete child;
		}


		std::cout << "end \n";
	}
}


int main()
{
	demo();
}