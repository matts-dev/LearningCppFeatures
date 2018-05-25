

#include <iostream>

namespace
{

	class B
	{
	public:
		void clone() {}
	};

	template <typename T>
	class a_template
	{
		//this is an example to show that only template methods that are used are instantiated
		//thus, no proper resource mangement implemented.
		T* ptr;
		
	public:
		a_template(T* obj) : ptr(obj) {}

		//this method is only compiled if it is used!
		void optionalCompiledMethod()
		{
			ptr->clone();
		}
	};
}

static
int main_v()
{
	a_template<int> sp1 = new int; 
	a_template<B> sp2(new B);

	//the presence of this call, has no influence on whether the template using int implements the method
	sp2.optionalCompiledMethod();

	//sp1.optionalCompiledMethod(); //this will give a compile error, because it forces the template to implement the method which uses a member function that int doesn't have

	std::cout << "press enter to close" << std::endl;
	std::cin.get();

	return 0;
}
