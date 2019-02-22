//#include <iostream>
//#include <cstdlib>
//
///* 
//	This file is special and will require commenting out because the operator new and operator delete can only be done at the global namespace level
//		error C2323: '`anonymous-namespace'::operator new': non-member operator new or delete functions may not be declared static or in a namespace other than the global namespace
//
//	1. Defining a global new/delete means all cpp_files(translation units) will use these operators! 
//	2. Global new and delete can be accessed like ::new and ::delete
//*/
//
//
/////////////////////////////////////////////////////////////////////////////////
//// standard new overloads
//
//void* operator new(std::size_t bytes)
//{
//	//this cannot be ::new because it will cause recursion
//	//return ::new char[bytes];
//
//	return std::malloc(bytes);
//}
//void operator delete(void* memory)
//{
//	std::free(memory);
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// tagged new overloads
//
////this could be any type (include primitives); different types allow differen calls of new
//struct CustomNewTag {};
//
//void* operator new(std::size_t bytes, const CustomNewTag& Tag )
//{
//	//this cannot be ::new because it will cause recursion
//	//return ::new char[bytes];
//	std::cout << "Special Tagged New Operator" << std::endl;
//	return std::malloc(bytes);
//}
//void operator delete(void* memory, const CustomNewTag& Tag)
//{
//	// Tagged delete deallocation functs are a type of placement function...
//	// Thus, they are only called when there is an exception thrown in the ctor
//	//they cannot be called manually
//
//	std::cout << "Special Tagged Delete Operator" << std::endl;
//	std::free(memory);
//}
//
//struct ExceptionInCtor
//{
//	ExceptionInCtor()
//	{
//		throw std::runtime_error("try to crash!");
//	}
//};
//
//
//
//
//int main()
//{
//		int* array0 = new int[4];	//this uses the global new operator
//		delete array0;
//
//		array0 = ::new int[2];		//this uses same new operator; explicitly at global scope
//		::delete array0;
//
//		int* x = new(CustomNewTag{}) int;
//		delete x; //does not call tagged delete
//
//		try {
//			//The only way to call a tagged delete is to throw an exception in ctor after tagged new
//			ExceptionInCtor* ptr = new(CustomNewTag{}) ExceptionInCtor();
//		} catch (const std::exception& ) {}
//
//}
