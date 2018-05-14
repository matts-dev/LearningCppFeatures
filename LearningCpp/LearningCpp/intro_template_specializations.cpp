
#include <iostream>
#include <limits>

namespace intro_template_specializations_ns
{
	template <typename T>
	class Demo
	{
	public:
		Demo(T arg)
		{
			std::cout << "generic" << std::endl;
		}
		void doWork() { std::cout << "generic work" << std::endl; }
	};

	template<>
	class Demo<char>
	{
	public:
		Demo(char arg)
		{
			std::cout << "specialized" << std::endl;
		}
	};

	template<typename T>
	class Demo<T*>
	{
	public:
		Demo(T* arg)
		{
			std::cout << "partial specialized" << std::endl;
		}
	};

}

void intro_template_specializations()
{
	using intro_template_specializations_ns::Demo;
	int x = 5;

	Demo<int> nonSpec(5);
	Demo<char> spec('a');
	Demo<int*> partSpec(&x);

	nonSpec.doWork();
	//spec.doWork(); not avaiable unless specialization writes version
	//partSpec.doWork(); //still not available in "partial" specializations
}