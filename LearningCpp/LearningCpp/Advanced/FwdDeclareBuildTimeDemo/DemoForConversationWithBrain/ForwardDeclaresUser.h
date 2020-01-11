#pragma once
#include "foobar.h"

#if MATTS_WAY
class Barfoo;
#else
#include"barfoo.h"
#endif

class UselessFowardDeclares
{
public:
	void doSomething1() {};
	void doSomething2() {};
private:
	FooBar foobar;
	BarFoo* pBarfoo;
};