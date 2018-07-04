#include<iostream>
#include <string>

namespace
{
	void log(char* msg) { std::cout << msg << std::endl; }

	void function_v(short x)
	{
		std::cout << "this is the function accepting an interger" << std::endl;
	}

	template<typename T>
	void function_v(T&& x)
	{
		std::cout << "this is the universal reference function" << std::endl;
	}

	//---------------------------------------------------

	class BaseV
	{
	public:
		BaseV() { log("No arg ctor"); }
		BaseV(const BaseV& copy) { log("copy ctor"); }
		BaseV operator=(const BaseV& copy) { log("copy="); }
		BaseV(BaseV&& move) { log("move ctor"); }
		BaseV operator=(BaseV&& move) { log("move="); }

		//this can take the form of move or copy ctors!
		template<typename T>
		BaseV(T&& univeral_ref_type) { log("universal ref ctor hijack! this can cause weird compile errors if you're passing values in that instantiate fields"); }
	};

	class DerivedV : public BaseV
	{
	public:
		DerivedV() { log("noarg child"); }

		//does not call base copy ctor! since the type is Derived, the template of BaseV can instantiate a ctor that accepts a "DerivedV"!
		DerivedV(const DerivedV& copy) : BaseV(copy){ log("copy child"); }
	};
}

static int main_v()
{
	{
		//universal references can hijack what would be considered normal functions 
		short val = 5;
		function_v(val); //this will call the true function that accepts a short
		function_v(5); //universal references hijack this function, 

		log("");
	}

	{
		BaseV obj;
		BaseV does_not_copy(obj); //because copy ctor has const on its argument, the template is a better match!

		const BaseV c_obj;
		BaseV does_copy(c_obj);

		log("");
	}

	{
		//inheritance can be screwed up by universal references, the universal reference can hijack the super calls to copy ctors/assignment operators!
		DerivedV obj1;

		log("\nbelow is the copy ctor for a chid class, but its call to the superclass copy ctor is hijacked by the universal reference!\n");
		DerivedV failed_copy(obj1);
	}

	std::cin.get();
}