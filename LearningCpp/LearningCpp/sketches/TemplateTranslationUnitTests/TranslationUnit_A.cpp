#include"TemplateWithStaticLocals.h"

void A_foo()
{
	int x = 6;

	templateCall<int>(6);
}