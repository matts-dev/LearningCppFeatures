#include<iostream>

int main()
{
	//auto deduces types the same way that parameter types are deduced (with a 1 exception that is changed post cpp14)	
	//look at the other file, TemplateTypeDeduction, and see that templates have two types deduced:
	//		the first type is in brackets, eg template<typename T>
	//		the first type is for the parameter, eg void func(T obj); where T can be be slightly different (such as const/volitile (cv) qualifiers) or have references appended.

	//HINT: mouse over the VARIABLE name in VS to see evaluated types

	auto val = 5; //evaluates to int
	const auto constval = 5; //evalutes to const int

	auto& ref = val; //evaluates int&

	auto* ptr = &val; //evaluates to pointer

	auto&& rvalue_ref1 = val;		//evaluates to int&				because val is lvalue (this is from special template param rules)
	auto&& rvalue_ref2 = constval;	//evaluates to const int&		because val is lvalue (again, this is the special template param rule)
	auto&& rvalue_ref3 = 5;			//evalutes to int&&				because 5 is an rvalue

	
	auto obj1(5);		//evaluates to int
	auto obj2 = 5;		//evaluates to int
	auto obj3{ 5 };     //sometimes an exception, sometimes not -- this msvs compiler evalutes to int
	auto obj4 = { 5 };	//exception to param rule, this evalutes to initializer_list

	std::cin.get();
}