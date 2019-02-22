#include <iostream>
#include <algorithm>
#include <vector>

namespace
{
	class Monoid
	{
	public:
		Monoid() { std::cout << "noarg ctor" << std::endl; }
		Monoid(int arg) { std::cout << "arg ctor:" << arg << std::endl; }
		Monoid(const Monoid& copy) { std::cout << "copy ctor" << std::endl; }
		Monoid& operator=(const Monoid& copy) { std::cout << "copy=" << std::endl; return *this; }
		Monoid(Monoid&& move)noexcept { std::cout << "move ctor" << std::endl; }
		Monoid& operator=(Monoid&& move)noexcept { std::cout << "move=" << std::endl; return *this; }
	};

	int truemain()
	{
		std::vector<Monoid> vecMonoids;
		vecMonoids.resize(1);

		std::generate(std::begin(vecMonoids), std::end(vecMonoids),
			[] { return std::move(Monoid{ 2 }); }
		);

		std::cin.get();
		return 0;
	}
}

//int main()
//{
//	truemain();
//}
