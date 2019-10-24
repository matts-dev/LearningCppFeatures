#include <type_traits>
#include <utility>
#include <iostream>
namespace
{
	//based off of online cpp reference signatures and bodies of visual studio implementations functions 
	template< class T >
	T&& my_forward(typename std::remove_reference<T>::type& t) noexcept
	{
		std::cout << "parameter is L-value" << std::endl;
		return (static_cast<T&&>(t));
	}

	template< class T >
	T&& my_forward(typename std::remove_reference<T>::type&& t) noexcept
	{
		std::cout << "parameter is R-value" << std::endl;
		return (static_cast<T&&>(t));
	}

	int illegal_to_pass_ravlue(int& param)
	{
		return param;
	}


	void test(int value, int& lvaluetype, int&& rvaluetype)
	{
		//note rvaluetype is actually an lvalue, but its type is rvalue
		auto&& valueResult = my_forward<int>(value);				//parameter is L - value
		auto&& lvalueResult = my_forward<int&>(lvaluetype);			//parameter is L - value		//note, these are still lvalue parameters
		auto&& rvalueResult = my_forward<int&&>(rvaluetype);		//parameter is L - value		//note, these are still lvalue parameters
		auto&& literalResult = my_forward<int&&>(3);                //parameter is R - value		//a true rvalue has to use the second type of function                 
	}
	int true_main()
	{
		int x = 5;

		illegal_to_pass_ravlue(x);
		//illegal_to_pass_ravlue(5); //compile error, can't pass rvalue into lvalue ref
		
		test(x, x, 6);


		return 0;
	}
}

//int main()
//{
//	true_main();
//}