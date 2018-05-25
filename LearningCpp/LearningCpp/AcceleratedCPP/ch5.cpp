
#include<iostream>
#include<vector>
#include<list>
#include<string>

int global = 0;

struct A
{
	//A(){std::cout<<ctor<<std::endl;} //keeps getting optimized out in msvc
	A(int z = 1) { std::cout << "ctor" << std::endl; } //provide a no-arg ctor that won't get optmized out
	A(const A& copy) { std::cout << "cpy ctor" << std::endl; }
	A& operator= (const A copy) { std::cout << "operater=" << std::endl; }
	~A() { std::cout << "dtor" << std::endl; }
};

static int main_x()
{

	std::vector<double> a_vec(4);
	std::list<double> a_list(4);


	std::cout << "vector that is value-initialized" << std::endl;
	for (std::vector<double>::const_iterator iter = a_vec.begin(); iter != a_vec.end(); ++iter)
	{
		std::cout << *iter << " ";
	} std::cout << std::endl;

	std::cout << "list that is value-initialized" << std::endl;
	for (std::list<double>::const_iterator iter = a_list.begin(); iter != a_list.end(); ++iter)
	{
		std::cout << *iter << " ";
	}std::cout << std::endl;

	//------------------------------------------------------------
	//attempting to add elements from a vector container to a list container.
	a_list.insert(a_list.begin(), a_vec.begin(), a_vec.begin() + 2);
	for (auto iter = a_list.begin(); iter != a_list.end(); ++iter)
	{
		std::cout << *iter << " ";
	}std::cout << std::endl;

	//----------------------------------------------------------------
	//using reverse iterators
	double val = 0;
	for (auto riter = a_list.rbegin(); riter != a_list.rend(); ++riter)
	{
		*riter = val;
		val++;
	}

	//print off elements that should be counting down since using reverse iterators.
	for (auto iter = a_list.begin(); iter != a_list.end(); ++iter)
	{
		std::cout << *iter << " ";
	}std::cout << std::endl;

	// showing off internal memory management
	std::vector<A> vec_strucs(2); //this will cause 2 no-arg ctor calls
	vec_strucs.resize(1); //this will cause a single dtor since we need to delete 1 item to resize the vector.
	vec_strucs.resize(2); //this will create a new struct, and will thus call the ctor 1 time
	vec_strucs.reserve(2); //this will allocate 2 additional spaces in memory, not calling the constructors, but preventing memory allocation later. 

	return 0;
}