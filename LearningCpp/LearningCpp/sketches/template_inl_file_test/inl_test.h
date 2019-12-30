#pragma once

/** A test that demostrates how you can separate out the template implemenation to improve build times */
namespace inl_test
{
	/** A template function that prints out hey*/
	template<typename T>
	void print_hey();

	/** A template type that prints out the object address*/
	template<typename T>
	class TemplateType
	{
	public:
		void print_obj_adr();
	private:
		T obj;
	};
}

