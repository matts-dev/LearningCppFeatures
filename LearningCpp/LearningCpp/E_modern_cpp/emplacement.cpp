#include<iostream>
#include <vector>
#include <memory>
#include <list>
#include <regex>

namespace //make LoudType static to this .cpp
{
	class LoudType{
	public:
		LoudType() noexcept { std::cout << "no arg ctor" << std::endl; }
		LoudType(const char* arg) noexcept { std::cout << "arg ctor" << std::endl; }

		LoudType(const LoudType& copy) noexcept { std::cout << "copy ctor" << std::endl; }
		LoudType(LoudType&& move) noexcept { std::cout << "move ctor" << std::endl; }

		LoudType& operator=(const LoudType& copy) noexcept { std::cout << "copy operator=" << std::endl; return *this; }
		LoudType& operator=(LoudType&& move) noexcept { std::cout << "move operator=" << std::endl;  return *this; }
	};
}

int main()
{
	std::vector<LoudType> vec;
	vec.reserve(100); //preallocates memory without calling any ctors; good for preventing early buffer expansions

	//Basics on emplace
	{
		//pushback creates temporary objects at the call site
		std::cout << "pushback with argument" << std::endl;
		vec.push_back("use argument ctor"); //1. creates temporary, 2. moves temporary
		//vec.push_back(LoudType("use argument constructor")); //same as above
		std::cout << "\n\n\n" << std::endl;

		//emplacement forwards the arguments to be constructed within the container
		std::cout << "emplacement with argument" << std::endl;
		vec.emplace_back("use argument ctor"); //1. only calls the arg ctor
		std::cout << "\n\n\n" << std::endl;
	}

	//in practice, emplacement isn't always faster (you need to bench test the two alternatives to ultimately know 
	//heuristics to determine if emplacement will likely be faster
	{
		//1. emplacement is generally faster when the object is constructed, but generally not when the object is assigned.
		{
			//construct an object
			std::cout << "constructing an object with emplace back" << std::endl;
			vec.emplace_back("constructing an object");

			//overwrite an object, but creating a temporary first
			std::cout << "\nassigning an object with emplace" << std::endl;
			vec.emplace(std::begin(vec), "this will use operator=, which will require creating a temporary object first");
			std::cout << "\n\n\n" << std::endl;

			//you can rely on non-node based containers to construct objects with emplace_back
		}
		//2. emplacement is faster when the arguments passed are different than the type contained by the container
		{
			//passing different arguments means you're likely passing constructor arguments.
			//passing an argument of the same type means you're probably creating a copy before emplacing it.
		}
		//3. emplacement is generally faster when the container doesn't reject duplicates; rejecting duplicates requires first creating an object then comparing it -- and potentially disregarding the dupliate.
		{
			//this isn't any faster than insertion because insertion will also create a temporary object
			//such containres are things like std::set or std::unordered_set
		}
	}

	//avoid using empalcement with managed types
	{
		using NodeBasedContainer = std::list<std::shared_ptr<LoudType> >;
		NodeBasedContainer sps;

		auto deleter = [](LoudType* item) {delete item; }; //custom deleter prevents us from using std::make_shared

		//best way to use emplacement with managed types
		std::shared_ptr<LoudType> temp(new LoudType("temp"), deleter); //exception safe
		sps.emplace_back(temp); //push_back is equally good in this case.

		//bad way to use emplacement
		sps.emplace_back(new LoudType("exception issue possible"), deleter); //if an exception is thrown in the creation of a node, then the new item we created will never be cleaned up!

		//why is the above bad?
		//1. we allocated a raw LoudType at the call site of emplace_back. This would be okay if it were directly passed to the ctor of the shraed_ptr, but it isn't
		//2. a node is dynamically allocated before the shared_ptr is constructed, if this throws an exception, the 'new LoudType' is never passed to the node. meaning it is never cleaned up!

		//rule of thumb: never allow the separation the call of new from the object that manages the resource
			//emplacement is unlikely to outperform insertion when resource managing classes are used
	}

	//emplacement may have weird behavior because it uses explicit construction
	{
		std::vector<std::regex> regexs;
		regexs.reserve(100);

		//std::regex reg = nullptr; //compile error
		//std::regex reg(nullptr); //compiles because reg takes a char* "expression", but it isn't built to handle nullptr
		
		//regexs.push_back(nullptr); //compile error, we're safe
		//regexs.emplace_back(nullptr); //compiles but crashes, but this goes to show you that emplace_back is more permissive because it uses explict constructors
	}

	std::cin.get();
}