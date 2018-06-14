#include <iostream>
#include <vector>
#include <stdexcept>

namespace
{
	//exceptions are part of the signature, kinda? You at least cannot remove noexcept from virtual functions (which makes sense)
	class Base_M
	{
	public:
		//no except is part of the signature, removing it from MAY cause api may cause issues
		virtual void method() noexcept {}
		//virtual void method() {} //however, this actually doesn't generate a compile issue MSVC; 
	};

	class Child_M : public Base_M
	{
	public:
		//noexcept is part of the function signature! (using override forces compiler to warn us)
		//virtual void method() override {} //will not compile because lacking noexcept
		virtual void method() noexcept override {} //most do this to match the noexcept signature 
	};

	//--------------------------------------------------------------------------------
	
	class DemoMethods
	{
		///noexcept allows for compiler optimizations that remove a methods unwinding overhead; stacks may not unwind in noexcept methods
	public:
		//the following two methods do not have compiler optimizations that remove unwinding code
		void method0() throw() {}//cpp98 no except, deprecated
		void method2() {} 

		// has compiler optimizations that avoid stack unwinding overhead
		void method1() noexcept {} //cpp11 no except

	};

	DemoMethods operator+(DemoMethods obj1, DemoMethods obj2) noexcept
	{
		return obj1;
	}

	//DemoMethods add(DemoMethods obj1, DemoMethods obj2) noexcept //uncomment to see noexecpt behavior; this will cause an abort instead of catch!
	DemoMethods add(DemoMethods obj1, DemoMethods obj2)  //this will allow a catch, because the below template "conditionaly_except" doesn't deduce to noexcept
	{
		return obj1;
	}
	//--------------------------------------------------------------------------------
}

void Part1_demoing_move_perf_increases_container()
{
	std::vector<DemoMethods> container(5);
	DemoMethods obj;

	//pretend the following call causes a buffer expansion in the underlying array
	container.push_back(obj);

	//cpp11, if a there exists a "noexcept" way to move the objects of the type the vector holds...
	//the vector will move from the old internal array to the new internal array
	//however, the moves need to be noexcept, otherwise the vector will default and use the copy behavior found in cpp98

	//"move if you can, copy if you must" describes how many of the cpp11 container operations work
	container.push_back(obj);
}

//the noexcept of this function is dependent on the functions used in the template; if they're noexcept, then this is noexcept
template<typename T>
void conditionaly_except(T* obj1, T*obj2) noexcept(noexcept(*obj1 + *obj2 ) && noexcept(add(*obj1, *obj2)))
{
	*obj1 + *obj2;
	add(*obj1, *obj2);

	//violation of noexcept contract! use this to test when exceptions are caught and when the cause abort!
	//hint, just change which commented out version of "add()" above (one is noexcept, the other is exception neutral)
	throw std::runtime_error{ "error" };
}

void Part2_demoing_conditionally_except()
{
	DemoMethods a;
	DemoMethods b;

	//whether this function throws exceptions is determined by if its template deduced function calls are noexcept
	try
	{
		conditionaly_except(&a, &b);
	}
	catch (std::runtime_error e)
	{
		std::cout << "an exception was caught?" << std::endl;
	}

	//note that the std::swap functions are conditionally noexcept...
	//a lot of std::algoritms use swap internally, providing noexcept swaps will give a large perf increase!
}

static int main_v()
{
	Part1_demoing_move_perf_increases_container();
	Part2_demoing_conditionally_except();
	
	//Making a function noexcept is not a light decision; changing it later can seriously break client code.
	//If you change an exception status, 
	//you can either get new exceptions being caught when they should crash...
	//or you can get programs terminating where previously would have been caught by an exception

	//--------------------------------------
	//Exception neutral functions: functions that allow exceptions to move up the call stack.

	//-------------------------------
	//Do not try to contort functions to make them noexcept, if they need to throw exceptions, let them.
	//You will likely lose much more in terms of readability (or subtle things like cache conflicts) for the small perf gain

	//---------------------------
	//in cpp98, dtors and dellallocations could throw exceptions, but it was considered bad practice
	//in cpp11, destructors and memory deallocation are implicitly noexcept; they can still throw exceptions, but only if states "noexcept(false)" {or internally something has this specification}

	//---------------------------
	//wide contract vs narrow contract functions
	//wide contract function: function that has no precondition and can be called anywhere without consequence
	//narrow contract: function that has precondition that must be met if the function is going to be called; other a crash/exception will occur
	//
	//in generally, noexcept should be applied to wide contract functions, no narrow contract functions

	//---------------------------
	//There are legitimate reasons noexcept functions may call functions without noexcept
	//		eg calling a c library
	//		calling old api
	//thus, in these cases, it is okay to have noexcept even though some interior functions may not have noexcept
	//which is why the compiler will not warn about noexcept functions calling exception neutral functions!

	std::cin.get();
}