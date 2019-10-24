#include <iostream>

namespace
{
	struct A
	{
		void foo() { std::cout << __func__ << std::endl; }
		void bar() { std::cout << __FUNCTION__ << std::endl; }
		//void baz() { std::cout << __PRETTY_FUNCTION__ << std::endl; } //gcc only
		void typeidName() { std::cout << typeid(*this).name() << std::endl; }
	};

	int true_main()
	{
		A obj;
		obj.foo();
		obj.bar();
		//obj.baz();
		obj.typeidName();
		return 0;
	}
}

//int main()
//{
//	return true_main();
//}