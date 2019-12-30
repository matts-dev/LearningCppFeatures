#pragma once
#include "inl_test.h"

namespace inl_test
{
	struct TypeThatUsesTemplate
	{
		TypeThatUsesTemplate();
		~TypeThatUsesTemplate();

		void indirect_print_hey();
		void indirect_print_obj();
	private:
		TemplateType<int>* incomplete_type_in_header;
	};
}

