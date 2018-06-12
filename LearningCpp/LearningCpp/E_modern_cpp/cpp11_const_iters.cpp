#include<iostream>
#include <vector>


int main()
{
	int sum = 0;
	std::vector<int> numbers;

	//non-const iterators look like this
	for (auto iter = numbers.begin(); iter != numbers.end(); ++iter)
	{
		sum += *iter;
	}
	sum = 0;

	//however, we are not changing the iter, so it would be better to use a const iter.
	//in cpp98, it was a hassle that required casting
	typedef std::vector<int>::iterator Iterator;  //since this is modeling cpp98, avoiding using using declarations which are a cpp 11 feature
	typedef std::vector<int>::const_iterator ConstIterator;
	for (auto iter = static_cast<ConstIterator>(numbers.begin()); iter != static_cast<ConstIterator>(numbers.end()); ++iter)
	{
		sum += *iter;
		//also, conversion from iterators from to const iterators wasn't portable in cpp98; so the code might not compile
	}
	sum = 0;

	//cpp11 added an easy way to get const iterators
	for (auto iter = numbers.cbegin(); iter != numbers.end(); ++iter)
	{
		sum += *iter;
	}
	sum = 0;

	//the book points out that there are some cases where member functions for constant iterators don't exist.
	//because of this reason, generic code should use the non-member versions of cbegin and cend
	//cpp11 only added non-member functions begin() and end()

	//cpp14 added nonmember functions cbegin, cend, rend, rbegin, crbegin, crend
	auto start = std::cbegin(numbers);
	auto end = std::cend(numbers);

	//cpp11 can define its own cbegin by cleverly using templates
	//see below function ee::cend()

	std::cin.get();
}

namespace ee
{
	template<typename T>
	auto cend(const T& collection) -> decltype(std::end(collection))
	{
		//since collection is const, this returns a constant iterator.
		return std::end(collection);
	}
};