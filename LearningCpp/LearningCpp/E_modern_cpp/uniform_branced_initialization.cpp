#include <initializer_list>
#include<iostream>
#include <vector>
#include <atomic>
#include <type_traits>

//NOTICE: this file contains lots of warnings under VS, but they're necessary for the demo.

namespace
{
	class M
	{
		int x, y, z;
	public:
		M() {
			std::cout << "no arg" << std::endl;
		}

		M(int x, int y, int z) : x(x), y{y}, z{z}
		{
			std::cout << "arg" << std::endl;
		}

		M(std::initializer_list<bool> list) { std::cout << "m: init list ctor" << std::endl; }
	};
};

template <typename T, typename... argTs>
void create(argTs&&... args)
{
	//below is an example to be used with std::vector<int> and that is what the comments reflect
	T obj1( std::forward<argTs>( args )... ); //will use the ctor that uses first argument as number of elements, and second argument as their value to be initialized to
	T obj2{ std::forward<argTs>( args )... }; //will use the initialize list ctor!

	//side point for template variadic arguments usage, there is an best practice for when to use forwarding later within the book
	T obj3( args...); //same as above, just showing that this will compile without std::forward
	T obj4{ args... }; //same as above, just showing that this will compile without std::forward
}

static int main_v()
{
	int x1 = 5;
	int x2(5);
	int x3{ 5 };    // x3 and x4 are equivalent 
	int x4 = { 5 }; // be careful, if using auto in this case you will get deduction to intializer_list instead of int!
	auto x5 = { 5 }; //deoming usage of converting to initializer list

	//---------------------------------------------------------------------------------------------------
	//{} are called uniform initialization because they can be used everywhere!
	class K
	{
	public:
		int val1{ 0 }; // uniform initialization (brace initialization) works
		int val2 = 0; //initialization (not assignment) also works
		//int val3(0); //!!!compile error!!! braces can't be used here, hence brances are not uniform
	};
	K obj1;

	//there are cases where = initialization fails, so it isn't uniform 
	struct L
	{
		int val;
		explicit L(int x) : val(x) {}
	};
	L l0( 0 ); //didn't work when initializing in class header, so this isn't uniform
	L l1{ 0 }; //uniform still works
	//L l2 = 0;  //COMPILE ERROR: the existance of explicit prevents this from being uniform
	//---------------------------------------------------------------------------------------------------
	//uniform initialization is immune to the most vexing parse
	M p1(); //declares a function! not an object -- most vexing parse
	M p2{}; //uses no-arg ctor 
	
	//using M p2{} will ALWAYS use the no-arg ctor
	//this doesn't convert to initialize_list, like in some examples where an init_list ctor is available
	//do the following if you want an empty initializer list
	M p3({}); //this can't be a function declaration because it has an argument, so it defaults to an initializer list argument.

	//---------------------------------------------------------------------------------------------------
	//brace (uniform) initialization is safer because prevents automatic narrowing conversions
	float a=1.f, b=2.f, c=3.f, d=4.f;

	//int all1{ a + b + c + d }; //compile error (not detected by intellisense :P)
	int all2(a + b + c + d);  //compiles fine, despite this being an arrowing conversion (float -> int)
	int all3 = a + b + c + d; //compiles!
	double widening_fine{ a + b + c + d }; //{} initialization has no problem with widening (eg float -> double)

	//---------------------------------------------------------------------------------------------------
	//Using brace initialization will strongly prefer constructors with initializer lists if they exist
	std::vector<int> container1{ 1, 2, 3 }; //this actually uses an initializer list!

	//the difference between () and {} are large when the class provides a constructor that takes an initializer list (this is now viewed as an error in the interface)
	std::vector<int> container2( 5, 4 ); //create 5 items of value 4
	std::vector<int> container3{ 5, 4 }; //creates a container of 5 and 4, because that's what is in the initializer list

	//this initializer preference is so strong, it will even attempt to match an initializer list even if a ctor's signature better matches
	struct With_Init_List
	{
		With_Init_List(int x, bool y) { std::cout << "real args" << std::endl; }
		With_Init_List(std::initializer_list<float> list) { std::cout << "init list, args converted to init_list type" << std::endl; }
	};
	struct Without_Init_List
	{
		Without_Init_List(int x, bool y) { std::cout << "real args" << std::endl; }
	};
	With_Init_List with{ 5, false }; //uses init_list
	Without_Init_List without{ 5, false }; //use arg ctor

	//it will even employ conversions to get to a ctor that uses initializer lists 
	struct convertable
	{
		float x;
		convertable(int x, bool y) : x(x) { std::cout << "convertable: real args" << std::endl; }
		convertable(std::initializer_list<float> list) { std::cout << "convertable: init list" << std::endl; }
		operator float() const { std::cout << "converted" << std::endl;  return 0; }
		void make_compiler_work() {};
	};
	convertable cv1(5, false); //uses arg ctor
	convertable cv2{ cv1 }; //newer versions of c++ appear to make this use the copy ctor
	//---------------------------------------------------------------------------------------------------
	//It can be *nearly* impossible to write template functions with consistent behavior (because of brace initialization)
	create<std::vector<int>>(5, 3);

	//---------------------------------------------------------------------------------------------------
	std::cin.get();
}

