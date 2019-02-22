#include <iostream>
#include <tuple>
#include <cstdio>

using namespace std;

namespace
{
	std::tuple<float, int, double> foo()
	{
		return std::make_tuple(1.0f, 5, 2.0);
	}

	int true_main()
	{
		float x;
		int y;
		double z;

		std::tie(x, y, z) = foo();

		printf("%0.2f, %2d, %0.2f", x, y, z);
		std::cin.get();

		return 0;
	}
}

//int main()
//{
//	true_main();
//}
