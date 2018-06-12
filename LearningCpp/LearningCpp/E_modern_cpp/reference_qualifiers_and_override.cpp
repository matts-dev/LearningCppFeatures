#include<iostream>

namespace
{

}

static int main_v()
{
	//using the override keywords helps for numerous reasons.
	//* it gives you a compile time check that your function signature matches some super class signature
	//* it protects you from refactoring code in a super class that silently creates bugs in subclasses. (with override keyword, you will get a compile error if you change the higher signature)

	//previous c++11 requirements for overriding functions
	//*base class must mark function as virtual
	//*function signatures must match (if they're not dtors), ie const, name, parameters, return type, and exception status.
	class Base
	{
	public:
		void virtual method1(float x) & {}
		void virtual method2(int x) {}
		void virtual method3() const {}
		void method4();
	};
	class Child : public Base
	{
	public:
		//incorrect overrides
		//void method1(float x) && override {}  //change in the new cpp11 reference qualifier
		//void method2(unsigned int x) override {} //change in parameter type to unsigned
		//void method3() override {} //method does not have const qualifier 
		//void method4() override {} //method 4 is not a virtual function

		//proper overrides 
		void method1(float x) & override {}
		void method2(int x) override {}
		void method3() const override {}
		//note override is a contextual keyword:
		//that is, it is a keyword when following a function, 
		//but you can still use it as a variable name since that is a different context. (final is also a contextual keyword)
	};


	//c++11 adds a new requirement for overriding functions
	//functions can have reference qualifiers, ie a & or && behind the function.
	//reference qualifiers determine which function gets called based on the reference type of the obj, ie an lvalue object acts differently than an rvalue object!
	class RefQualiferDemo
	{
	public:
		static RefQualiferDemo factory() { return RefQualiferDemo{}; }

		//new reference qualifiers; see the & and && after the function name?
		//if *this is an lvalue, it will call the method with a & at the end.
		//if *this is an rvalue, it will call the method with && at the end.
		void method() & { std::cout << "l-value ref method:         probably should be copied instead of moved" << std::endl; }
		void method() && { std::cout << "r-value ref method:         allows clever moving!" << std::endl; }

		//methods that accept either rvalue or lvalue references (not that neither of these are reference qualified because there is no & or && after the function)
		void method(RefQualiferDemo& lvalue) { std::cout << "this accepts ONLY lvalues" << std::endl; }
		void method(RefQualiferDemo&& rvalue) { std::cout << "RVALUES only are accepted!" << std::endl; }
	};

	RefQualiferDemo obj1;
	obj1.method(); //lvalue method called
	RefQualiferDemo::factory().method(); //rvalue method called


	//lvalueness and rvalueness determines copying behavior!
	class CarefullyManaged
	{
	public:
		CarefullyManaged() { /*std::cout << "noarg ctor" << std::endl; */}
		CarefullyManaged(const CarefullyManaged& copy) { std::cout << "copy ctor" << std::endl; }
		CarefullyManaged(const CarefullyManaged&& move) { std::cout << "move ctor" << std::endl; }
		CarefullyManaged& operator=(const CarefullyManaged& copy) { std::cout << "copy ctor" << std::endl; return *this; }
		CarefullyManaged& operator=(const CarefullyManaged&& move) { std::cout << "move ctor" << std::endl; return *this; }
		//virtual ~CarefullyManaged() {}

		static CarefullyManaged factory() { return std::move(CarefullyManaged{}); }
	};

	CarefullyManaged source = CarefullyManaged{};

	auto cmobj1 = source;
	auto cmobj2 = CarefullyManaged::factory();

	std::cin.get();
}