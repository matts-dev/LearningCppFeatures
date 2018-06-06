#include<iostream>
#include<vector>
#include<unordered_map>
#include <functional>

namespace
{
	struct Y
	{
		void talk() { std::cout << "hello " << std::endl; }
	};

	template<typename T> class NameFinder;
}

template<typename Iter>
void iterate_and_copy(Iter b, Iter end)
{
	//this just shows how auto is useful.
	//note that in VS, mousing over auto variable in template methods doesn't show you the deduced type...
	//this is because it cannot note to which template instantiation you're curious about 
	//(eg template<int> vs template<double>, etc.)

	for (; b != end; ++b)
	{
		//typename std::iterator_traits<Iter>::value_type currentCopy = *b; //book put typename before, but it doesn't seem necessary for compilation
		std::iterator_traits<Iter>::value_type currentCopy = *b;
		//vs. r
		auto copy = *b;

		currentCopy.talk();
		copy.talk();

		//NameFinder<decltype(copy)> copy_type;
		//NameFinder<decltype(currentCopy)> currentCopy_type;
	}
}

static int main_v()
{
	using std::vector;
	using std::unordered_map;

	//create a vector of 5 Y objs
	vector<Y> container(5);
	iterate_and_copy(container.begin(), container.end());

	//-----------------------------------------------------------------------
	//auto provides the most compact storage of lambdas (ie the closure)

	//NOTE: closure type is up to the compiler,
	//	-- so storing in auto is more portable than trying to write out type!
	auto compact_storage = [](int x, double y) { std::cout << x + y << std::endl; };

	// you can bind a closure to a std::function obj, but it requires more space than using auto as the storage type.
	// std::function, if necessary, will allocate storage on heap if there is not enough storage. 
	std::function<void(int,double)> requires_more_storage = [](int x, double y) { std::cout << x + y << std::endl; };
	
	//--------------------------------------------------------------------------
	unordered_map<std::string, int> wordCount;
	for (const std::pair<std::string, int>& item : wordCount)
	{
		//this has the terrible bug that item is actually a COPY of the pair within word count.
		//this is because std::string should be const std::string
		//the compiler automatically copies the pair item so match the signature,
		//this will cause bugs if you attempt to modifiy what is in the map container
	}

	for (const auto& item : wordCount)   //item type: const std::pair<const std::string, int>&
	{
		//this doesn't create a copy, it uses an actual reference to the pair in the wordCount!

	}

	// -------------------------------------------------------------
	//strange bug with vector...
	//say we were going to use variable below to iterate over size
	unsigned size = container.size();  //this will work on windows 32, but now window 64

	//unsigned happens to be the same size as std::vector<Y>::size_type on windows 32, both are 32 bits!
	//however, on windows 64, unsigned is 32 bits while the ...::size_type is 64 bits!
	auto size_safe = container.size(); //this is safe for both platforms! no refactoring required.

	// -------------------------------------------------------------
	//Using auto also serves as a gaurd for changing code,
	//if you change the return of a function, and those returns are captured in auto variables,
	//then no refactorings will be needed!
}