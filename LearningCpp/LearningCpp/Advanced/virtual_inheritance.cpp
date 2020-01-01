#include<iostream>

namespace
{
	/////////////////////////////////////////////////////////////////////////////////////
	// base class
	/////////////////////////////////////////////////////////////////////////////////////
	class Base
	{
	public:
		Base(){ heapMem = new int;}
		virtual ~Base() { delete heapMem;}
		void printMemAddress() { std::cout << heapMem << "\n";}
	private:
		int* heapMem;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	// classes that do normal inhertiance of base
	/////////////////////////////////////////////////////////////////////////////////////
	class A_Child : public Base
	{};

	class B_Child : public Base
	{};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// classes that virtually inherit base
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class A_Virtual_Child : public virtual Base
	{};

	class B_Virtual_Child : public virtual Base
	{};

	/////////////////////////////////////////////////////////////////////////////////////
	// permutations of inheriting
	/////////////////////////////////////////////////////////////////////////////////////

	class Inherit_Normal_NormalChild : public A_Child, public B_Child
	{};

	class Inherit_Virtual_NormalChild : public virtual A_Child, public virtual B_Child
	{};

	class Inherit_Normal_VirtualChild : public A_Virtual_Child, public B_Virtual_Child
	{};

	class Inherit_Virtual_VirtualChild : public virtual A_Virtual_Child, public virtual B_Virtual_Child
	{};

	class Inherit_Normal_BothChildren : public virtual A_Child, public B_Virtual_Child
	{};

	void demo()
	{
		std::cout << "exploring normal inheritance\n";
		Inherit_Normal_NormalChild normalInheritance;
		//normalInheritance.printMemAddress();	//error C2385: ambiguous access of 'printMemAddress'	"note: could be the 'printMemAddress' in base 'Base' note: or could be the 'printMemAddress' in base 'Base'" 	
		normalInheritance.A_Child::printMemAddress();
		normalInheritance.B_Child::printMemAddress();
		normalInheritance.Base::printMemAddress(); // | MSVC appears to just pick one and print that memory address | DOES NOT COMPILE GCC: ‘{anonymous}::Base’ is an ambiguous base of ‘{anonymous}::Inherit_Normal_NormalChild’ |
		//exploring normal inheritance
		//	0000018AF33F1870
		//	0000018AF33E5E70
		//	0000018AF33F1870

		std::cout << "\n" << "exploring virtually inheriting normal subclasses\n";
		Inherit_Virtual_NormalChild inheritVirtually_normalChild;
		//bothVirtual.printMemAddress();	//error C2385: ambiguous access of 'printMemAddress'"note: could be the 'printMemAddress' in base 'Base' note: or could be the 'printMemAddress' in base 'Base'" 	
		inheritVirtually_normalChild.A_Child::printMemAddress();
		inheritVirtually_normalChild.B_Child::printMemAddress();
		inheritVirtually_normalChild.Base::printMemAddress(); // |Compiles MSVC | Does not compile GCC|
		//exploring virtually inheriting normal subclasses
		//	000001B81D2B57E0
		//	000001B81D2B5820
		//	000001B81D2B57E0

		//********** I believe this is the ideal set up *****************/
		std::cout << "\n" << "exploring normally inheriting virtual subclasses\n";
		Inherit_Normal_VirtualChild inheritNormally_VirtualChild;
		inheritNormally_VirtualChild.printMemAddress(); //no compile error here!
		inheritNormally_VirtualChild.A_Virtual_Child::printMemAddress();
		inheritNormally_VirtualChild.B_Virtual_Child::printMemAddress();
		inheritNormally_VirtualChild.Base::printMemAddress();
		//exploring normally inheriting virtual subclasses
		//	000002115F853D30
		//	000002115F853D30
		//	000002115F853D30
		//	000002115F853D30

		//************ This also works, but probably has more overhead ********/
		std::cout << "\n" << "exploring virtually inheriting virtual subclasses\n";
		Inherit_Virtual_VirtualChild inheritVirtually_VirtualChild;
		inheritVirtually_VirtualChild.printMemAddress(); //no compile error here!
		inheritVirtually_VirtualChild.A_Virtual_Child::printMemAddress();
		inheritVirtually_VirtualChild.B_Virtual_Child::printMemAddress();
		inheritVirtually_VirtualChild.Base::printMemAddress();
		//exploring virtually inheriting virtual subclasses
		//	00000289CDA08800
		//	00000289CDA08800
		//	00000289CDA08800
		//	00000289CDA08800

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Exploring having interfaces that virtual inhert, in this case the child that is virtual would be the interface
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// this unfortunately doesn't work, we get separate data in the base class
		std::cout << "\n" << "exploring virtual inheriting interfaces\n";
		Inherit_Normal_BothChildren inheritNormal_NormalAndVirtualChild;
		//inheritNormal_NormalAndVirtualChild.printMemAddress(); //C2385: ambiguous access of 'printMemAddress'
		inheritNormal_NormalAndVirtualChild.A_Child::printMemAddress();
		inheritNormal_NormalAndVirtualChild.B_Virtual_Child::printMemAddress();
		inheritNormal_NormalAndVirtualChild.Base::printMemAddress(); // |compiles MSVC| doesn't compile GCC|
		//exploring virtual inheriting interfaces
		//	000001B8CE653CB0
		//	000001B8CE653CF0
		//	000001B8CE653CB0


		std::cout << "end \n";
	}
}


//int main()
//{
//	demo();
//}