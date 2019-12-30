#include "template_use_A.h"
#include "inl_test.inl"
#include <string>

namespace inl_test
{
	TypeThatUsesTemplate::TypeThatUsesTemplate()
	{
		incomplete_type_in_header = new TemplateType<int>;
	}

	TypeThatUsesTemplate::~TypeThatUsesTemplate()
	{
		delete incomplete_type_in_header;
	}

	void TypeThatUsesTemplate::indirect_print_hey()
	{
		print_hey<std::string>();
		//print_hey<const char*>();
	}

	void TypeThatUsesTemplate::indirect_print_obj()
	{
		incomplete_type_in_header->print_obj_adr();
	}

}

