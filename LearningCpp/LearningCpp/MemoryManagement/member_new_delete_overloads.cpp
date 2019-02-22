#include <iostream>
#include <cstdlib>

namespace
{
	/*
		DISCLAIMER: these are not necessarily good examples of overloads for new/delete.
			They don't use the new_handlers.
			They don't do checks (alignment, base class size checks, etc.)
		This is mostly to show syntax and behavior of overloading operator new/delete
	
	*/


	class OverloadedClass
	{
	public:
		OverloadedClass() { std::cout << "ctor: OverloadedClass" << std::endl; }
		virtual ~OverloadedClass() { std::cout << "v dtor: OverloadedClass" << std::endl; }	

		//////////////////////////////////////////////////////////////////////////////////////////////
		// Overloaded new/delete operators are static by default

		//////////////////////////////////////////////////////////////////////////////////////////////
		// standard new/delete
		static void* operator new (std::size_t bytes)
		{
			std::cout << "operator new" << bytes << std::endl;

			//create a byte array for this memory
			//all of the following work:
			return new char[bytes];
			//return ::new OverloadedClass();	//I dislike this syntax; 1. it will be recursive if you don't use global new ::new, 2. issues with arg-ctors
			//return std::malloc(bytes);
		}
		static void operator delete(void* mem)
		{
			std::cout << "operator delete\n" << std::endl;

			delete[] mem;
			//std::free(mem);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		//array new and delete
		static void* operator new[](size_t total_bytes)
		{
			std::cout << "new[]" << total_bytes << std::endl;
			return new char[total_bytes];
		}
			void operator delete[](void* memory)
		{
			std::cout << " delete[]\n" << std::endl;
			delete[] memory;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		// Placement new variants of singlular and array
		static void* operator new(std::size_t bytes, void* place)
		{
			std::cout << "placement new" << std::endl;
			return place;
		}
		//cannot call manually, called automatically if exception occurs in class ctor
		static void operator delete (void* mem, void* place)
		{
			std::cout << "placement delete: only called if ctor throws an exception" << std::endl;
		}
		static void* operator new[](std::size_t bytes, void* place)
		{
			std::cout << "placement new[]" << std::endl;
			return place;
		}
		//cannot call manually, called automatically if exception occurs in class ctor
		static void operator delete[](void* mem, void* place)
		{
			std::cout << "placement delete[]: only called if ANY ctor throws an exception" << std::endl;
		}

	private: 
		int bytes_4 = 0xffffffff;
	};
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	// inheritance
	class ChildClass : public OverloadedClass
	{
	public:
		ChildClass() { std::cout << "ctor: ChildClass" << std::endl; }
		virtual ~ChildClass() { std::cout << "v dtor: ChildClass" << std::endl; }	

		static void* operator new (std::size_t bytes)
		{
			std::cout << "operator new: ChildClass; size:" << bytes << std::endl;
			return new char[bytes];
		}

		//if superclass dtor is not virtual, the WRONG delete will be called on a superclass ptr
		static void operator delete(void* mem)
		{
			std::cout << "operator delete: ChildClass" << std::endl;
			delete[] mem;
		}
	private:
		int extra_size;
	};

	void true_main()
	{
		// ----- regular new/delete -----
		OverloadedClass* obj0 = new OverloadedClass();
		delete obj0;

		//-----array new/delete -----; 
		// a value equal to size of pointer is allocated before the array that contains 
		// the number of elements is used in the call to delete[]
		constexpr unsigned int arraySize = 2;
		OverloadedClass* array0 = new OverloadedClass[arraySize]();
		delete[] array0;

		//polymorphic deletes
		OverloadedClass* polyptr = new ChildClass;
		delete polyptr;

		//-----placement new variants-----
		char singleInstanceMemory[sizeof(OverloadedClass)];
		OverloadedClass* placementAllocated = new(singleInstanceMemory) OverloadedClass();
		//placement delete cannot called directly, it is only ever called if there is an exception in ctor
		//NOTE: to see placement delete being called, look at the file overload_member_new_delete.cpp for cases where exception thrown in ctor 
		placementAllocated->~OverloadedClass();

		//placement array new still stores array size before actual array, so we allocate enough room for the size
		//from my testing, it is stored in the size of a pointer (though it is not a pointer). Hence sizeof(char*)
		char arrayMemory[sizeof(char*) + arraySize * sizeof(OverloadedClass)];
		OverloadedClass* placementArray = new(arrayMemory) OverloadedClass[arraySize];
		for (unsigned int obj = 0; obj < arraySize; ++obj)
		{
			//cannot call placement delete[] manually, so, AFAIK we have to walk through calling the dtor on each
			placementArray[obj].~OverloadedClass();
		}
	}
}

//int main()
//{
//	true_main();
//}
