#include <iostream>
#include <memory>
#include <vector>
#include <functional>

namespace
{
	class M
	{
	public:
		M() { std::cout << "M noarg-ctor" << std::endl; }
		M(int x) { std::cout << "M arg-ctor" << std::endl; }
		M(M&& move) { std::cout << "move ctor" << std::endl; }
		virtual ~M() { std::cout << "M dtor" << std::endl; }

		void doWork() { std::cout << "working" << std::endl; }
	};

	class N : public M
	{
	public:
		N() : M() {}
		N(int x) : M(x){}
	};

	class O : public M
	{
	public:
		O(int x) : M(x) {}
	};


	std::unique_ptr<M> factory(bool makeChild)
	{
		if (makeChild)
			return std::make_unique<N>();
		else
			return std::make_unique<M>();
	}

	// ----------------- Advanced Factory Method ---------------------------
	enum class Type : char { M, N, O };

	//Using a custom deleter changes the type of the unique ptr (this doesn't happen with shared_ptrs)
	auto deleter = [] (M* rawPtr) { 
		std::cout << "deleting " << rawPtr << std::endl;
		delete rawPtr;
	};

	template <typename... Ts>
	std::unique_ptr<M, decltype(deleter)> advanced_factory(Type choice, Ts&&... args) //notice that the deleter is part of the signature!
	{
		//very ugly, but we have to use this signature when using custom deleters; this is probably why you can't specify custom deleters with make_unique
		std::unique_ptr<M, decltype(deleter)> ptr_with_log_deleter(nullptr, deleter);
		switch (choice)
		{
			case Type::M:
				//notice reset doesn't change the deleter, because it's part of the signature!
				ptr_with_log_deleter.reset(new M(std::forward<Ts>(args)...));
				break;
			case Type::N:
				ptr_with_log_deleter.reset(new N(std::forward<Ts>(args)...));
				//ptr_with_log_deleter.reset(new N(args...)); //compiles
				break;
			case Type::O:
				ptr_with_log_deleter.reset(new N(std::forward<Ts>(args)...));
				break;
		}
		return ptr_with_log_deleter;
	}
	//------------------------------------------------------

	void deleter_func(M* rawPtr)
	{
		//custom deleters always except a raw pointer as argument
		//when dealing with polymorphism, make sure that the bass class has a virtual dtor!
		std::cout << "deleting " << rawPtr << std::endl;
		delete rawPtr;
	}
}

static int main_v()
{
	//reasons to avoid regular pointers...
		//* From just the declaration, you don't know if its your responsibility to destroy the pointer.
		//		*->You also cannot tell the proper mechanism for deleting, is there a logging function?
		//* A pointer declartion may refer to a single object or an array of objects; it's ambiguous!
		//		*->this also leads to the an ambiguity for deleting, should you use delete or delete[]?
		//* From a raw pointer, it is hard to make sure it is destroyed only once, and that there are no dangling pointers.
		//* Its hard to tell if you have resource leaks 

	//std::auto_ptr should be avoided! its like a unique pointer but worse!
	{

//auto ptr is not in cpp17
		
#define DISABLE_FOR_CPP17 
#ifndef DISABLE_FOR_CPP17
		std::auto_ptr<M> dep_aptr = std::auto_ptr<M>(new M());
		dep_aptr->doWork();

		//autoptr copy operations are attempts at move semantics; this is cpp98, before move semantics were at thing.
		std::auto_ptr<M> transfer = dep_aptr; //nulls out dep_aptr
		transfer->doWork();

		//the move hijacking of copies led to weird behavior, such as when trying to store auto_ptrs in containers, or copying an autoptr being set to null
		std::vector<std::auto_ptr<M>> container;
		//container.push_back(transfer);//doesn't compile
		//container.push_back(std::auto_ptr<M>(new M())); //this WILL compile, but it isn't what we want, we want to transfer the auto_ptr to the container! 
		//container[0]->doWork(); //cannot store the transfer ptr in the container, so better not call this

		//ALWAYS prefer unique pointer, don't use autoptr... its removed in cpp17
#endif
	}

	//unique pointers are small like raw pointers, but have their lifetime managed! 
	//They also have copy operations and move operations! This makes superior to auto_ptr in every way!
	{
		//You can assume that unique pointers are the size of raw pointers, or just barely larger than raw pointers.
		M* raw_ptr = nullptr;
		std::unique_ptr<M> u_ptr1(new M(5));
		auto u_ptr2 = std::make_unique<M>(5);

		//both these pointers are of size 8 bytes!
		std::cout << "size of a raw ptr: " << sizeof(raw_ptr) << std::endl;
		std::cout << "size of a unique ptr: " << sizeof(u_ptr1) << std::endl;

		//You can move unique pointers, but you can't copy them!
		//std::unique_ptr<M> u_ptr3 = u_ptr1;  //C2280: copy ctor is deleted!
		//std::unique_ptr<M> u_ptr3(u_ptr1);	//C2280: copy ctor is deleted
		std::unique_ptr<M> u_ptr3 = std::move(u_ptr1); //compiles fine!			//sets u_ptr1 to nullptr
		std::unique_ptr<M> uptr4(std::move(u_ptr2)); //compiles!				//sets u_ptr2 to nullptr
	}

	{
		//unique pointers make good return types for factory methods because they cant automatically be converted to shared pointers!
		std::unique_ptr<M> ptr1 = factory(true);
		auto ptr2 = factory(false);
		std::shared_ptr<M> ptr3 = factory(true);
	}

	{
		auto ptr1 = advanced_factory(Type::M, 0); //will cause a compile error unless all types can take an integer as parameter!
		auto ptr2 = advanced_factory(Type::N, 1); //will cause a compile error unless all types can take an integer as parameter!
		auto ptr3 = advanced_factory(Type::O, 2); //will cause a compile error unless all types can take an integer as parameter!
		//auto ptr1 = advanced_factory(Type::M);
		//auto ptr2 = advanced_factory(Type::N);
		//auto ptr3 = advanced_factory(Type::O);
	}


	{
		//different deleters may change the size of the unique pointer (this is NOT true for shared pointers, because shared pointers store deleters in their shared control block)
		//prefer deleters that are specified by lambdas, they're even smaller than function pointers. In fact, lambda's don't add any size at all to the function pointer!
		auto deleter_lambda = [](M* rawPtr) {std::cout << "logging delete" << std::endl; delete rawPtr; };
		void(*deleter_fp)(M*) = &deleter_func;
		std::function<void(M*)> deleter_func_obj = &deleter_func;

		//notice that these unique pointers specify their type to include the type of the deleter (look at ctors, auto used for compactness)
		auto uptr_lambda = std::unique_ptr<M, decltype(deleter_lambda)>(new M, deleter_lambda);
		auto uptr_fptr = std::unique_ptr<M, decltype(deleter_fp)>(new M, deleter_fp);
		auto uptr_func_obj = std::unique_ptr<M, decltype(deleter_func_obj)>(new M, deleter_func_obj);

		std::cout << "The size of the uptr with " << "a lambda deleter: " << sizeof(uptr_lambda) << std::endl;				//8 bytes
		std::cout << "The size of the uptr with " << "a function pointer deleter: " << sizeof(uptr_fptr) << std::endl;		//16 bytes
		std::cout << "The size of the uptr with " << "a function obj deleter: " << sizeof(uptr_func_obj) << std::endl;		//72 bytes
	}

	{
		//using unique pointers are even safe with exceptions! stack unwinding will call dtor on uptr
		try
		{
			//stack unwind the scopes
			{
				{
					auto deleter_lambda = [](M* rawPtr) {std::cout << "deleting " << rawPtr << std::endl; delete rawPtr; };
					auto ptr = std::unique_ptr<M, decltype(deleter_lambda)>(new M, deleter_lambda);
					std::cout << "\n\ncreated " << ptr.get() << " " << std::endl;
					std::cout << "throwing exception, will dtor be called in stack unwinding?" << std::endl;
					throw std::runtime_error("exception");
				}
			}
		}
		catch (std::runtime_error e)
		{
			std::cout << "exception handled!" << std::endl;
		}
		//output:
		//created 000002B6C5DD0770
		//throwing exception, will dtor be called in stack unwinding ?
		//deleting 000002B6C5DD0770
		//M dtor
		//exception handled!
	}

	{
		//note the syntax below is illegal because it was deemed problematic
		//std::unique_ptr<M> uptr = new M; //IE no conversions directly from pointer to uptr.

		//there are two forms of unique pointers (this is not true for shared ptr), the single object form and the array form.
		//these different forms have different apis, for example the [] operator is removed from the single object form.
		auto uptr_obj = std::make_unique<M>();
		//uptr_obj[0]; //not present in single object api!

		//std::unique_ptr<M[]> uptr_array(new M[5]);
		std::unique_ptr<M[]> uptr_array_cpp14 = std::make_unique<M[]>(5); //make an array of size 5 in cpp14
		uptr_array_cpp14[5]; //operator is okay!
		//uptr arrays should be avoided in favor of std::vector or other containers; but you may need it when dealing with C apis.

		//note: unique pointers are good for implementing the pImpl idiom
	}
	//you can easily convert to a shared pointer from a unique pointer (but not the other way around)
	//this is why your factory methods should return unique pointers, instead of shared pointers. Doing so allows the caller to decided the ownership of the pointer.
	{
		std::unique_ptr<M> uptr = std::make_unique<M>();
		std::shared_ptr<M> sptr = std::move(uptr); //requires that you move ownership!
	}

	{
		//transferring ownership with custom deleters? works :3
		auto deleter_lambda = [](M* rawPtr) {std::cout << "super custom deleting " << rawPtr << std::endl; delete rawPtr; };
		std::unique_ptr<M, decltype(deleter_lambda)> uptr(new M, deleter_lambda);
		std::shared_ptr<M> sptr = std::move(uptr);
	}

	std::cin.get();
}