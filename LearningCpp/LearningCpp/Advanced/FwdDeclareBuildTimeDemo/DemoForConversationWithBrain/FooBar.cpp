#include "foobar.h"
#include "barfoo.h"

#if REFACTOR_FOOBAR
struct FooBar::Impl
{
	BarFoo obj;
};
#endif


FooBar::FooBar()
{
#if REFACTOR_FOOBAR
	impl = new FooBar::Impl;
#endif
}

FooBar::~FooBar()
{
#if REFACTOR_FOOBAR
	delete impl;
#endif
}

void FooBar::UseBarFoo()
{
#if REFACTOR_FOOBAR
	impl->obj.use();
#else
	obj.use();
#endif
}

