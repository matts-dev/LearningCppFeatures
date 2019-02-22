#include <iostream>
#include "Tester.h"
#include "Receiver_OnlyForwardDeclaresInHeader.h"


//should already be forward declared in headers, but here for clairty.
enum class ETYPE : int;

namespace
{
	int truemain()
	{
		Tester provider;
		Receiver receiver;

		//nowhere in this scope is there a declaration for ETYPE!
		//not a single header defines it internally!
		//only the .cpps of each file have the definition.
		receiver.TakeValue(provider.getTypeValue());

		std::cin.get();
		return 0;
	}
}

//int main()
//{
//	///probably should wrap this entire folder in namespace FWD_DCL_ENUM
//	truemain();
//}
