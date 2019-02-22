#include "Receiver_OnlyForwardDeclaresInHeader.h"

#include "ForwardDeclareThis.h"
#include <iostream>

void Receiver::TakeValue(ETYPE value)
{
	switch (value)
	{
		case ETYPE::A:
			std::cout << "TYPE: A" << std::endl;
			break;
		case ETYPE::B:
			std::cout << "TYPE: B" << std::endl;
			break;
		case ETYPE::C:
			std::cout << "TYPE: C" << std::endl;
			break;
	}
}
