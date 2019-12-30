#pragma once
#include "inl_test.h"
#include <iostream>


namespace inl_test
{
	template<typename T>
	void print_hey()
	{
		T hey_str = "hey\n";
		std::cout << hey_str; 
	}

	template<typename T>
	void TemplateType<T>::print_obj_adr()
	{
		std::cout << &obj << "\n"; 
	}

}