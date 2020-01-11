#pragma once

#define MATTS_WAY 0
#define REFACTOR_FOOBAR 0

#if REFACTOR_FOOBAR
//don't include implementation details 
//in header
struct BarFoo;
#else
//includes implementation details in header
#include "BarFoo.h"
#endif

class FooBar
{
public:
	FooBar();
	~FooBar();
	void UseBarFoo();
private:
#if REFACTOR_FOOBAR 
	struct Impl; //impl has BarFOo
	Impl* impl;
#else
	BarFoo obj;
#endif
};
