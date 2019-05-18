#include <iostream>
#include <string>

namespace
{
	struct A
	{
		int x;
		virtual ~A() {}
	};
	struct B
	{
		std::string x;
	};

	struct C : public A, public B
	{
		double y;
	};


	int true_main()
	{
		C obj;

		A* pa = &obj; //b0
		B* pb = &obj; //b8
		std::cout << pa << std::endl;
		std::cout << pb << std::endl;

		//char* bytes = static_cast<char*>(pb); //does not compile: invalid static_cast form B* to char*
		//char* bytes = reinterpret_cast<char*>(pb); //compiles fine, same as old-style cast below
		char* bytes = (char*)(pb); //b8
		std::cout << (void*)bytes << std::endl; //b8

		A* pa_AfterCasts = (A*)(bytes); //b8

		std::cout << pa_AfterCasts << std::endl;
		if (pa_AfterCasts == pa) { std::cout << "pointers match" << std::endl; }
		else { std::cout << "pointers don't match" << std::endl; }

		//bonus: how to dis=ambiguate x
		std::cout << obj.B::x << std::endl;

		return 0;
	}
}

//int main()
//{
//	true_main();
//}
