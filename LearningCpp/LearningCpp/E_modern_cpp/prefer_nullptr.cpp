#include<iostream>

namespace
{
	//Some random class to use
	struct M
	{

	};

	//this is NOT probably how it is done 
	template <typename T>
	class ImplicityConvert
	{
		T* ptr;
	public:
		ImplicityConvert() { ptr = new T{}; }
		~ImplicityConvert() { delete ptr; }
		operator T*() { return ptr; }
	};

	//something to get an address of
	int x = 6;

	//-------------------------------------------- LOOK AT THESE ----------------------------------
	void overload(int x) {	std::cout << "int " << std::endl; }
	void overload(M* m) { std::cout << "pointer" << std::endl; }
	int* get_something() { return &x; }

	//this kind of function works fine with NULL
	void doSomethingInferredOnAPointer(int* arg) { std::cout << typeid(decltype(arg)).name() << std::endl; }

	//template instantiation really helps with nullptr!
	template<typename T>
	void doSomethingInferredOnAPointer_template(T arg) { std::cout << typeid(decltype(arg)).name() << std::endl; }

	//advance template that will outright fail with NULL or 0
	template<typename PTR, typename FUNC>
	auto getPtr(PTR obj, FUNC fptr) -> decltype(auto)
	{
		return fptr(obj);
	}

	M* flip_back(M* ptr) { return ptr; }
}

int main()
{
	//the options
	M* ptr1 = 0;
	M* ptr2 = NULL;
	M* ptr3 = nullptr;

	//0 and NULL cause issues with overloading
	overload(0);			//calls int overload
	overload(NULL);			//calls int overload
	overload(nullptr);		//calls pointer overload

	//In c++11, the guideline is:
	//DO NOT OVERLOAD METHODS ACCEPTING POINTERS WITH METHODS ACCEPTING ACCEPTING INTEGER TYPES
	//Even though c++11 now has nullptr, some developers still use NULL and 0.
	//By continuing to adopt that guideline, it protects against many subvert bugs in teams.

	//----------------------------------------------------------------

	//The circular definition of nullptr
	std::nullptr_t x = nullptr;
	//nullptr_t is defined to be the type of nullptr
	//nullptr is defined to be the type of nullptr_t!
	//nullptr_t is designed to implicitly convert to all pointer types, which is how nullptr can become any pointer type!
	ImplicityConvert<M> converter;
	M* ptr = converter;

	//---------------------------------------------------------------
	auto whats_this = get_something();
	if (whats_this == nullptr) 
	{
		//using a check like this communicates to the reader that the auto variable is a pointer!
		//as opposed to just typeing if(x){}
	}
	//----------------------------------------------------------------
	std::cout << "Non-templates passed null" << std::endl;
	doSomethingInferredOnAPointer(0);			//int*
	doSomethingInferredOnAPointer(NULL);		//int*
	doSomethingInferredOnAPointer(nullptr);		//int*

	//template instantiations that expect pointers...
	std::cout << "templates passed null" << std::endl;
	doSomethingInferredOnAPointer_template(0);			//int
	doSomethingInferredOnAPointer_template(NULL);		//int
	doSomethingInferredOnAPointer_template(nullptr);	//nullptr_t

	//M* ret1 = getPtr(0, flip_back);		//causes very cryptic compiler error
	//M* ret2 = getPtr(NULL, flip_back);	//causes very cryptic compiler error
	M* ret3 = getPtr(nullptr, flip_back);	//correctly instantiates to M* as argument!
	//----------------------------------------------------------------
	std::cin.get();
}
