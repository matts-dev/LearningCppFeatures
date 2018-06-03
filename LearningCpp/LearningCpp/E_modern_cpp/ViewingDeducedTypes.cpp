#include<iostream>

namespace
{
	template<typename T> class NameFinder; //no definition/specification, this will give compile error with targeted type
	
	class A_Super {	};
	class B_Child : public A_Super { };
}

int main()
{
	//visual studio mouse over variable name to see type 
	const double val = 5;
	auto a = val;  //double 
	auto b = &val; //const double*

	//using compiler errors (uncomment out below to see error msgs with types!)
	//NameFinder<decltype(a)> type_of_a; //'type_of_a' uses undefined class '`anonymous-namespace'::NameFinder<double>'
	//NameFinder<decltype(b)> type_of_b; //'type_of_b' uses undefined class '`anonymous-namespace'::NameFinder<const double *>'
	//A_Super* polymorphic = new B_Child(); //decltype is a compile time construct!
	//NameFinder<decltype(polymorphic)> type_of_ptr; //'type_of_ptr' uses undefined class '`anonymous-namespace'::NameFinder<`anonymous-namespace'::A_Super *>
	//delete polymorphic;

	//runtime output can be unreliable, if you're using typeid.
	//typeid treats types as if they were arguments to a template function; passed by VALUE!
	//which means reference, const, and volitile are ignored!
	//to understand, review TemplateTypeDeduction.cpp for pass-by-value.
	const auto& cref = val;
	std::cout << typeid(cref).name() << std::endl; //returns double! not const double& 

	//If you want reliable runtime type information, the boost::typeindex.hpp is an option;
	//it works much better than typeid.

	std::cin.get();
}