#include<iostream>
#include <string>

namespace
{
	//void funct_overload(int& lvalue_ref) { std::cout << "lvalue ref" << std::endl; }
	//void funct_overload(int&& rvalue_ref) { std::cout << "rvalue ref" << std::endl; }

	template <typename T> void funct_overload(const T& lvalue_ref) { std::cout << "lvalue ref" << std::endl; }
	template <typename T> void funct_overload(const T&& rvalue_ref) { std::cout << "rvalue ref" << std::endl; } //not a universal reference because constT&& is excluded from being universal reference by standard 

	class Player { 
	public:
		explicit Player(int x, int y) {};
		explicit Player(float x, float y) {};
	};
	template <typename... Ts> 
	Player factory(Ts&&... args)
	{
		return Player(args...);
	}

}

static int main_v()
{
	//generic lambdas are like having a templated lambda and are available in cpp14
	{
		auto generic_lambda = [](auto&& a, auto&& b) { return a + b; };  //note: accepting universal references
		
		int v1 = generic_lambda(5, 5);
		double v2 = generic_lambda(2.5, 2.5);
		std::string v3 = generic_lambda(std::string("hel"), std::string("lo"));
	}

	{
		auto forwarding_lambda = [](auto&& param) {
			return funct_overload(std::forward<decltype(param)>(param));
		};

		int x = 5;
		forwarding_lambda(x);
		forwarding_lambda(5);
	}
	{
		auto better_forwarding_lambda = [](auto&&... params) {
			return factory(std::forward<decltype(params)>(params)...);
		};
		Player obj = better_forwarding_lambda(5, 5);
	}
}