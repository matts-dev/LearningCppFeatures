

#include<iostream>

namespace
{
	//cpp98 way of removing instructions is to make them private and declare them but do not give them a body
	class M_cpp98
	{
	public:
		M_cpp98(){}
	private:
		M_cpp98(const M_cpp98& copy); //private and undefined was cpp11 style; calling will cause link-time error
	};

	//cpp11 way of removing functions is to make them publica, and delete them
	class M_cpp11
	{
	public:
		M_cpp11() {}

		//declared as public, (so that calling doesn't give an access exception).
		M_cpp11(const M_cpp11& copy) = delete; //not private! calling will cause a compile time error 
	};

	//implicit conversion can cause issues with overloading
	void problematic_with_conversions(int x) { std::cout << x << std::endl; } //can pass bool, char, double and all will be implicitly converted.

	//you can delete any function, this helps with avoiding problematic implicit conversions!
	void overload_safe(int x ) { std::cout << x << std::endl; }
	void overload_safe(bool x) = delete;
	void overload_safe(double x) = delete;
	void overload_safe(char x) = delete;
	
	//---------------------------------------------------------------------------
	// deleted functions can prevent template instantiations! (private undefines can't)
	template<typename T>
	void func_with_edge_cases(T* ptr) {}

	//specializations prevent edge cases with void* and char* pointer's since they're normally treated differently
	//such as not deferencing
	template<>
	void func_with_edge_cases(void* ptr) = delete;
	
	template<>
	void func_with_edge_cases(char* ptr) = delete;
	//---------------------------------------------------------------------------
	
	class M
	{
	public:
		template<typename T>
		void func_with_edge_cases(T* ptr) {}
	private:
		//template<>
		//void func_with_edge_cases(void* ptr); //cpp98 attempt, but won't compile because it changes access of specialized function! We can't make this public because we don't want a non-defined function to be part of the class api.
	public:
		//template<> //compiles, but may not be portable
		//void func_with_edge_cases(void* ptr) = delete; //cpp11 way compiles! warning: this might not be portable
		//template specializations should be declared at the namespace scope.
	};
	template<>
	void M::func_with_edge_cases(void* ptr) = delete;

}

static int main_v()
{
	//the old cpp98way, ie private undefines, could have calls attempted by friends etc; but would error out at link time.


	//deleted functions can't be used in any way (at compile time), eg calls, friends. 
	//this is better than cpp98 way

	//making deleted functions public gives better error messages.
	//if you make a deleted function private, the compiler will complain about calling a private function (before complaining about calling a deleted function)
	//
	problematic_with_conversions(1);
	problematic_with_conversions(true); //we don't want this implicit conversion
	problematic_with_conversions(5.5); //we don't want this implicit conversion
	problematic_with_conversions('c'); //we don't want this implicit conversion

	overload_safe(1);
	//overload_safe(true); //error C2280: attempting to reference a deleted function
	//overload_safe(5.5); //error C2280: attempting to reference a deleted function
	//overload_safe(5.5f);//error C2280: **will try to convert to double before int**
	//overload_safe('c'); //error C2280: attempting to reference a deleted function

	//---------------------------------------------------------------------------

	//the last two function calls have specializations that mark them as deleted, since they're edge case pointers
	func_with_edge_cases(static_cast<int*>(nullptr));
	//func_with_edge_cases(static_cast<void*>(nullptr)); //error C2280:: attempting to reference a deleted function
	//func_with_edge_cases(static_cast<char*>(nullptr)); //error C2280:: 

	//---------------------------------------------------------------------------
	M obj;
	obj.func_with_edge_cases(static_cast<int*>(nullptr));

	std::cin.get();
}