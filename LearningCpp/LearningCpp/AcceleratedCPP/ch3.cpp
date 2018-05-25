

#include<iomanip>
#include<ios>
#include<iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <functional>

//playing around with stuff talked about in chapter 3
int main_x()
{
	std::vector<double> values;
	values.push_back(5);
	values.push_back(-1.0);
	values.push_back(4);
	values.push_back(-5.244);
	values.push_back(100.2);
	values.push_back(8.9);

	//std::sort(values.begin(), values.end());
	std::sort(values.begin(), values.end(), std::greater<double>());

	std::streamsize prec = std::cout.precision();
	/*for (double val : values)
	{
		std::cout << std::setprecision(4) << val << std::endl;
	}*/
	//typedef std::vector<double>::size_type vec_sz;
	using vec_sz = std::vector<double>::size_type; //more modern c++ way, as opposed to typedef

	for (vec_sz i = 0; i < values.size(); ++i)
	{
		std::cout << std::setprecision(4) << values[i] << std::endl;
	}
	std::cout << std::setprecision(prec);

	return 0;
}