#include<iostream>

namespace
{
	//constexpr really means a value is known at compiletime; 
	//function caveat: don't assume the result of value is known at compile time...			    (this is a good thing)
	//function caveat: don't assume the result of a constexpr is constant...'					(this is a good thing too... they're features as we will see)

	void constexprObjsDemo()
	{
		int size1 = 10;
		//int a1[size1]; //compile error! (c++ doesn't have stack dynamic arrays like newer versions of c)

		//constexpr objs DO have values known at compile time! We can assume this is true.
		constexpr int size2 = 10; //will be placed in read-only memory.
		int a2[size2]; //we can use a variable to initialize the size of the array.

		//technically constexpr OBJS have values determined at translation, which is both compilation and linking
		//constexpr objs can be used in variety of places: arraysizes, integral template arguments, enumerator values, and alignment specifiers

		//note: all constexpr objs are const, but not all const objs are constexpr!
	}

	constexpr int constexpr_function_cpp11(const int& obj1, const int& obj2) noexcept
	{
		return obj1 > 10 ? obj1 + obj2 : obj2; //cpp11 requires that constexpr functions have 1 statement
		//however, you can use recursion to simulate loops; 
		//you can use the ternary operator for if statements.
	}

	constexpr int pow(const int base, const int power) noexcept
	{
		//recursive call to calculate the power!
		return power == 0 ? 1 : pow(base, power - 1) * base;
	}

	constexpr int constexpr_function_cpp14(const int value, const int limit) noexcept
	{
		//apparently msvc hasn't implimented this as of yet (2018)

		//cpp14 allows you to use multiple lines in a constexpr
		//auto ret = 1;
		//for (int i = 0; i < limit; ++i)
		//{
		//	ret += value;
		//}
		//return ret ;  

		return 1;
	}

	void constexprFunctionsDemo()
	{
		constexpr int cxpr = 10;
		constexpr int obj2 = 20;
		constexpr int ret = constexpr_function_cpp11(cxpr, obj2); //requires that parameters are constant

		int a1[ret]; //using result of a constexpr function to set the size of an array
		a1[0] = 5;

		int normal_int = 5;
		//constexpr int ret2 = constexpr_function(normal_int, cxpr); //doesn't evalute to a constant! function is acting like a normal function.
		int ret2 = constexpr_function_cpp11(normal_int, cxpr); //this shows how constexpr functions can be used like non-constexpr functions

		//the fact that constexpr_function can be used as either a constxpr or a regular function prevents code duplication

		//using recursive constexpr
		constexpr int base = 2;
		constexpr int power_val = 5;
		//int power_val = 5; //uses pow in a non-constexpr way
		constexpr int power = pow(base, power_val);
		std::cout << "2 pow 5 is: " << power << std::endl;

	}
	
	class Constexpr_ctors
	{
		float x, y;
	public:
		constexpr Constexpr_ctors(float x, float y) noexcept: x(x), y(y) {}
		constexpr float getX() const noexcept { return x; } 
		void setX(float newX) { x = newX; } //cannot be constexpr because it modifies state
		//in cpp1 you can't have constexpr functions that return void (because it must cause sideeffects); but this restriction is removed in cpp14
	};

	/* Does not compile in visual studio
	class Cpp14_MutableConstexpr
	{
		int x;
	public:
		constexpr Cpp14_MutableConstexpr(int x) noexcept : x(x) {}
		constexpr void setX(int newX) noexcept { x = newX; };
	}; 
	*/

	void constexprClassesDemo()
	{
		//you can have constexpr user defined types too :)
		constexpr Constexpr_ctors actually_constexpr_obj{ 5, 6 };
		Constexpr_ctors not_constexpr_obj{ 5, 6 };

		constexpr float test_that_obj_is_constexpr1 = actually_constexpr_obj.getX();
		//constexpr float test_that_obj_is_constexpr1 = not_constexpr_obj.getX(); //error C2131: expression did not evaluate to a constant
		//according ot the book, in cpp14 you can have functions that modify the state of a constexpr; I guess it needs to be done in a block? perhaps inside the ctor.
		//		actually it allows essentially function calls within constexpr functions

		//Cpp14_MutableConstexpr cpp14Obj{ 6 }; //visual studio doesn't compile
	}

}

int main()
{
	constexprObjsDemo();
	constexprFunctionsDemo();
	constexprClassesDemo();

	//on a final note, constexpr is part of a functions interface.
	//removing constexpr from a function can break lots of code;
	//you may be tempted to do this to adding debugging information (ie logging) to the code
	//adding constexpr should thus be a long term commitment, but is highly recommended.
	std::cin.get();
}