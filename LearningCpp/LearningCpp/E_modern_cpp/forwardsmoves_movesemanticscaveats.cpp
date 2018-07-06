
//this file is to show the scenarios where move semantics are not as great (or do not work) like some may think.

#include<iostream>
#include<string>
#include <type_traits>
#include <vector>
#include<array>

static void log(const char* msg) { std::cout << msg << std::endl; }
namespace
{
	template<typename T>
	void template_function_design_consideration(T&& forward_ref)
	{
		//when designing template functions, always assume scearios like below do copies and not a moves; it may be a move, but it may not
		T obj = std::move(forward_ref);
	}

	//class has proper move member functions that are noexcept.
	class TypeV1
	{
	public:
		TypeV1()									{ std::cout << "no arg ctor " << std::endl; }
		TypeV1(const TypeV1& copy)					{ std::cout << "copy ctor " << std::endl; }
		TypeV1(TypeV1&& move) noexcept				{ std::cout << "move ctor " << std::endl; }
		TypeV1& operator=(const TypeV1& copy)		{ std::cout << "copy= " << std::endl; return *this; }
		TypeV1& operator=(TypeV1&& move) noexcept	{ std::cout << "move=" << std::endl; return *this; }
		virtual ~TypeV1() =							default;
	};

	//this class does not have move member functions
	class TypeV2
	{
	public:
		TypeV2() { std::cout << "no arg ctor " << std::endl; }

		//providing these remove the default implementations of move special member functions
		TypeV2(const TypeV2& copy)				{ std::cout << "v2 copy ctor " << std::endl; }
		TypeV2& operator=(const TypeV2& copy)	{ std::cout << "v2 copy= " << std::endl; return *this; }
		virtual ~TypeV2() =						 default; 
	};

	//this type lacks the noexcept keywords on its moves, making it improper.
	class TypeV3
	{
	public:
		TypeV3()								{ std::cout << "v3 noarg ctor" << std::endl; }
		TypeV3(const TypeV3& copy)				{ std::cout << "v3 copy ctor " << std::endl; }
		TypeV3& operator=(const TypeV3& copy)	{ std::cout << "v3 copy= " << std::endl; return *this; }
		TypeV3(TypeV3&& move)					{ std::cout << "v3 move ctor " << std::endl; }
		TypeV3& operator=(TypeV3&& move)		{ std::cout << "v3 move=" << std::endl; return *this; }
	};
}

int main()
{
	template_function_design_consideration(TypeV1()); //internally calls the move ctor because its provided
	template_function_design_consideration(TypeV2()); //internally calls the copy ctor because no move ctor is avaiable; this is why you should write generic functions with the mindset that as if they will perform copies!
	log("");

	std::vector<TypeV3> container_of_types_that_lack_noexceptmoves(1);
	//will attempt to move internals on buffer resize if it can (ie there no except)
	container_of_types_that_lack_noexceptmoves.reserve(100); //this will call copy ctor when moving to the new buffer because move is not marked as noexcept; (note in VS2015, this will actually wrongly call the move ctor!)
	log("");

	std::vector<TypeV1> proper_container_of_types_that_have_noexceptmoves(1);
	proper_container_of_types_that_have_noexceptmoves.reserve(100); //this will truely move when the buffer is resized and the object put into the new buffer.
	log("");

	//generally, moving containers is a O(1) operation while copying containers is a O(n) operation 
	//(with moving, you just update a single pointer; with copying you have to iterate over the entire container to copy)
	//so moving a container that has a pointer to a heap allocated array will be O(1), while copying it will be O(n).
	std::vector<TypeV1> src_fast(10);

	log("moving vector");
	std::vector<TypeV1> fast_move_exp(std::move(src_fast)); //a single move happens here, and that just updates the pointer! O(1) time!
	
	log("copying vector");
	std::vector<TypeV1> slow_copy(fast_move_exp);
	log("");

	//But here's example where move is not O(1) operation, but O(n)  -- just like the copy;
	std::array<TypeV1, 10> src_slow{};
	std::array<TypeV1, 10> slow_move_exp{std::move(src_slow)};

	//To summarize, there are three different main scenarios where moves don't work out
	//1. move operations are "noexcept" and therefore are avoided by containers for exception safety (we wouldn't like it if the vector through an exception while internally resizing its buffer)
	//2. some types do not provide move operations (eg they define a special member function and removes the automatic generation of move functions, or they mark it delete).
	//3. some types have move operations that are only marginally faster, but are not faster ing complexity analysis (big O notation)
	std::cin.get();
}