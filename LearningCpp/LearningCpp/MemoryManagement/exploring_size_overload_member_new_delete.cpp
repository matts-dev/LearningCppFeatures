#include <iostream>
#include <stdexcept>

namespace
{
	////////////////////////////////////////////////////////////////////////////
	//new and delete can be overloaded on a class-by-class basis
	class SingleMemberOverload
	{
		//I have laid out the functions in the order they're called for the lifetime of the object
	public:
		//1.
		void* operator new (std::size_t bytes)
		{
			std::cout << "operator new: SingleMemberOverload; size:" << bytes << std::endl;

			//create a byte array for this memory
			return new char[bytes];
		}

		//2.
		SingleMemberOverload() { std::cout << "ctor: SingleMemberOverload" << std::endl; }

		//3.
		//~SingleMemberOverload() { std::cout << "dtor: SingleMemberOverload" << std::endl; }			//use this version to have class without vtable
		virtual ~SingleMemberOverload() { std::cout << "v dtor: SingleMemberOverload" << std::endl; }	//use this version to add vtable to clas

		//4.
		void operator delete(void* mem)
		{
			std::cout << "operator delete" << std::endl;

			//delete 
			delete[] mem;
		}
	private: //give some state to class

		//gives size of 4; comment to see that a class with no state has a size of 1.
		//int State;	//comment/uncomment to give class some memory
		//int State2; //useful for checking out packing induced by a vtable

	};
	////////////////////////////////////////////////////////////////////////////
	class ArrayMemberOverload
	{
	public:
		ArrayMemberOverload() { std::cout << "ctor: ArrayMemberOverload" << std::endl; }
		//~ArrayMemberOverload() { std::cout << "dtor: ArrayMemberOverload" << std::endl; }
		virtual ~ArrayMemberOverload() { std::cout << "v dtor: v" << std::endl; }	//use this version to add vtable to class

		//array new and delete
		void* operator new[](size_t total_bytes) 
		{
			std::cout << "new[] : ArraymemberOverload;  bytes:" << total_bytes << std::endl;
			return new char[total_bytes];
		}
		void operator delete[](void* memory) 
		{
			std::cout << " delete[] : ArraymemberOverload" << std::endl;
			delete[] memory;
		}
	private:
		int bytes_4 = 0xffffffff; //gives some size to the class
	};

	//////////////////////////////////////////////////////////////////////////////////

	class PlacementNew
	{
	public:
		PlacementNew(bool throwException = false)
		{
			std::cout << "ctor: PlacementNew" << std::endl; 
			if (throwException)
			{
				throw std::runtime_error("test"); 
			}
		}
		~PlacementNew() { std::cout << "dtor: PlacementNew" << std::endl; }
		//virtual ~PlacementNew() { std::cout << "v dtor: v" << std::endl; }	//use this version to add vtable to class

		//note: these operators must be public
		void* operator new(std::size_t bytes, void* place)
		{
			std::cout << "placement new" << std::endl;
			return place;
		}
		void operator delete (void* mem, void* place)
		{
			std::cout << "placement delete: only called if ctor throws an exception" << std::endl;
			//perhaps memset it to zero?
		}
		void* operator new[](std::size_t bytes, void* place)
		{
			std::cout << "placement new[]" << std::endl;
			return place;
		}
		void operator delete[](void* mem, void* place)
		{
			std::cout << "placement delete[]: only called if ctor throws an exception" << std::endl;
		}

	private:
		int state = 0xffffffff;
	};

	////////////////////////////////////////////////////////////////////////////
	// inheritance
	class Child : public SingleMemberOverload
	{
	public:
		Child() { std::cout << "ctor: Child" << std::endl; }
		//~Child() { std::cout << "dtor: Child" << std::endl; }			//use this version to have class without vtable
		virtual ~Child() { std::cout << "v dtor: Child" << std::endl; }	//use this version to add vtable to class

		void* operator new (std::size_t bytes)
		{
			std::cout << "operator new: Child; size:" << bytes << std::endl;

			//create a byte array for this memory
			return new char[bytes];
		}
		void operator delete(void* mem)
		{
			std::cout << "operator delete: Child" << std::endl;

			//delete 
			delete[] mem;
		}
	private:
		int extra_size;
	};

	///////////////////////////////////////////////////////////////////////
	struct BadBase
	{
		void* operator new(size_t bytes)
		{
			std::cout << "BadBase::operator new" << std::endl;
			return malloc(bytes);
		}
	};
	struct BadChild : public BadBase
	{
		//incorrectly inherits and will call the base's new operator
	};
	//////////////////////////////////////////////////////////////////////
	struct DeleteMatcher
	{
		DeleteMatcher()
		{
			throw std::runtime_error("try crash!");
		}
		void* operator new(std::size_t bytes)
		{
			return new char[bytes];
		}
		//this function will be called if the one below it doesn't exist
		void operator delete(void* mem)
		{
			delete[] mem;
		}
		//this function will be favored since it matches the operator new more closely
		void operator delete(void* mem, size_t bytes)
		{
			delete[] mem;
		}
	};
	///////////////////////////////////////////
	
	void true_main()
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		// Singular New
		//FINDINGS (x64):
		//without vtable and no int member:				new's size is 1
		//without vtable with member variable int:		new's size is 4; the size of an int
		//vtable with no int member:					new's size is 8; size of pointer in x64 
		//vtable with int member:						new's size is 16; vtable pointer + int and some padding
		//vtable with 2 int members:					new's size is 16; vtable pointer + 2 ints (which are 4 each); since vtable alignment makes class 8 byte aligned
		SingleMemberOverload* mo = new SingleMemberOverload();
		delete mo;

		//this does NOT use the overloaded new in anyway
		SingleMemberOverload* moArray = new SingleMemberOverload[2];
		delete[] moArray;

		//////////////////////////////////////////////////////////////////////////////
		// new[] and delete[]
		//
		// FINDINGS (x64)
		// Regardless of array number, 8 bytes will be allocated in addition to required size.
		// Allocating with a class that has no data members
		//		allocating [1] gives 9 bytes, 8 + 1 byte for the size of class
		//      allocating [2] gives 10 bytes, 8 + 2
		// allocating where class holds a 4byte int
		//		allocating [2] gives 16, 8 + 4 + 4
		//		allocating [1] gives 12, 8 + 4
		// The extra 8 bytes is an integer specifying the array size, this is most likely the mechanism how delete[] works
		// adding a vtable to an array of [2] that are 1byte each gives: 24; 8 (size) + 8 + 8; the last two are pointers into the vtable
		// adding a vtable to an array of [2] that should be 4 bytes each gives: 40; 8(size) + 2*(8 + 8); there are two 8s per obj because 1: vtable ptr, and 2: 4bytes for int + 4bytes for padding
		ArrayMemberOverload* ao_array = new ArrayMemberOverload[2];
		delete[] ao_array;

		ArrayMemberOverload* ao = new ArrayMemberOverload(); //again, shows that 'new' is different than 'new[]'
		delete ao;

		//////////////////////////////////////////////////////////////////////////////
		// Placement New
		char single_instance_bytes[sizeof(PlacementNew)];
		PlacementNew* pn = new(single_instance_bytes) PlacementNew(false);
		pn->~PlacementNew(); //one does not directly call placement delete, just call dtor

		try
		{
			//placement delete operator is only called when exception thrown in ctor!
			PlacementNew* pn = new(single_instance_bytes) PlacementNew(true);
			pn->~PlacementNew();
		}
		catch(std::exception all) {	}

		//when using placement new for arrays, YOU have to account for extra space (ie a long?) for array size
		//though, since you can't call placement delete directly, I'm not sure why this extra size is even necessary...
		constexpr unsigned int size = 3;
		char array_memory[sizeof(PlacementNew) * size + sizeof(uint64_t)];	//taking sizeof array (PlacementNew[2]) will yield pointer size!

		PlacementNew* arr = new(array_memory) PlacementNew[size];

		//instead of delete...
		for (unsigned int obj = 0; obj < size; ++obj)
		{
			//manually call dtors since we used placement new and can't call placement delete (with good reason since that memory shouldn't be deleted)
			arr[obj].~PlacementNew();
		}

		//call placement delete[] via causing exception in one of the object's ctors
		try
		{
			PlacementNew* arr2 = new(array_memory) PlacementNew[size]{false, false, true};
		}catch (std::exception all) {}

		///////////////////////////////////////////////////////////////////////////////////
		// Inheritance
		Child* child = new Child;
		delete child;

		//virtual delete behavior tests
		SingleMemberOverload* polymorphicPtr = new Child;
		//will below correctly call the delete on CHILD (ie like a virtual delete) when pointer is super class!?
		delete polymorphicPtr; //the answer is: yes if the dtor is virtual, if not the WRONG delete will be called!

		//pitfall: operator new is inherited
		BadChild* badChild = new BadChild; // calls the BASE class new!
		delete badChild;

		//will attempt to match delete that most closely matches new
		try
		{
			DeleteMatcher* obj = new DeleteMatcher;
			delete obj;
		}
		catch (std::exception&) {}
	}
}

//int main()
//{
//	true_main();
//}
