#include"TemplateWithStaticLocals.h"

void B_foo()
{
	int x = 2;

	templateCall<int>(6);
}