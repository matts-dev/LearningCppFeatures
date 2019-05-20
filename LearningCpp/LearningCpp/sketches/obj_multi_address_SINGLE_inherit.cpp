#include <iostream>

namespace
{
	struct NonVirtualBase
	{
		int x;
	};
	struct VirtualDerived : public NonVirtualBase
	{
		std::string y;

		//vtable will change the address of this object!
		virtual ~VirtualDerived() {}
	};


	int true_main()
	{
		VirtualDerived obj;

		NonVirtualBase* pa = &obj; //b0
		VirtualDerived* pb = &obj; //b8
		std::cout << pa << std::endl;
		std::cout << pb << std::endl;

		return 0;
	}
}
//int main()
//{
//	true_main();
//}
