#pragma once

//this does not ever directly include .inl filel
#include"template_use_A.h"
#include <string>

namespace inl_test
{
	void true_main()
	{
		TypeThatUsesTemplate obj;
		obj.indirect_print_hey();
		obj.indirect_print_obj();


		TemplateType<int> compiles_size_defined; //this compiles?
		compiles_size_defined.print_obj_adr(); //fine for some reason

		//below will compile if a .cpp instantates the template... seems MSCV is doing some magic behind the scenes
		//print_hey<const char*>(); //error LNK2001: unresolved external symbol "void __cdecl inl_test::print_hey<char const *>(void)" (??$print_hey@PEBD@inl_test@@YAXXZ)

		print_hey<std::string>(); //this only compiles if the template_use_A.cpp instantiates a print_hey<std::string>() function. MSVC seems to be linking to template bodies because this function is no where defined here.
	}
}

//int main()
//{
//	inl_test::true_main();
//}
