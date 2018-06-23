#include<iostream>
#include<memory>
#include <vector>

namespace
{
	class Demo
	{
		int val;
	public:
		Demo(int x) : val(x){}
	};

	float calculate() { return 0.1f; /*pretend this may throw an exception*/ }

	void dangerous_misuse_potential(std::shared_ptr<Demo> ptr, float param2)
	{
		//if passing new directly to this function, compiler optimizations may rearrnage things to be 
		//not exception safe
	};
}

int main()
{
	std::allocator<Demo> allocator;

	//cpp14 added make_unique<>() to the potenial make functions!

	//3 make functions
	auto uptr1 = std::make_unique<Demo>(5);
	auto sptr1 = std::make_shared<Demo>(5);
	auto sptr2 = std::allocate_shared<Demo>(allocator, 5);
	
	//prefer the make functions! there's several advantages (and disadvantges)
	//1. the make functions prevent you from directly using new
	//2. the make functions allow you to use auto and only write the type name once
	//3. make functions give exception safety
	{
		//not exception safe! the compile generate the following order: 
		//		1.new Demo(5), 2.calculate(), 3.shared_ptr ctor
		//with that ordering, if calculated throws an exception, the "new demo(5)" is never deleted!
		dangerous_misuse_potential(std::shared_ptr<Demo>(new Demo(5)), calculate());

		//exception safe, no possible reordering to introduce exception risk
		dangerous_misuse_potential(std::make_shared<Demo>(5), calculate());
	}
	//4. make_shared saves a memory allocation
	{
		//allocates 1. new Demo, and 2. a control block!
		std::shared_ptr<Demo> sptr1(new Demo(5));

		//allocates both demo and a control block in the same memory allocation! (this may cause problems if you overload the new operator!)
		auto sptr2 = std::make_shared<Demo>(5);

		//so, std::make_shared gives a performance upgrade! This also applies for "allocate_shared"
	}

	//limitations of the make function
	//1. you can't specify a custom deleter when using std::make_shared
	//2. make_shared uses () initilaizers, not {}!
	{
		//if you provide a ctor with an initializer_list...
		//   ctor() will match ctor with arguments
		//   ctor{} will strongly prefer the initializer list ctor
		//This means, depending on how smart pointers are implemented, you will only get one of these behaviors!
		//		the make functions actually implement the parenthesis ctors, so
		auto sptr = std::make_shared<std::vector<int>>(5, 3); //makes a vector: {3, 3, 3, 3, 3}, and not {5, 3}
		
		//This makes it hard use an initializer list with smart pointers...
		//it turn out that {} initializers can't be perfect forwarded (more on that later the book says)
		//There exists a work around though, it looks like you need to store the initlaizer list in an auto variable, and pass that to the ctor.
	}

	//limitations to shared_pointer specifically (not unique_ptr)
	//1. Custom memory managed classes (defining operator new and delete)
	{
		//a class that defines operator new and operator delete allows you to specify where the memory is allocated from...
		//these typicaly work by allocating sizes exactly of the class that overloaded the operators.
		// The problem is: std::make_shared allocates the object and the control block in the same contiguous memory!
		

		//another issues is that the control block lives longer than the object!
		//if the object and the control block are within the same contiguous memory block, none of it can be freed until both the control block and the object can be deleted
		//		weak pointers keep the control block alive!
		//      so, as long as a weak pointer hangs around, so does the control block!
		//			if the control block and object reside in the same allocated memory block, then the object's memory won't be freed until the weak pointer is dtored!
		//			this means, having a really big object can hang on to memory if std::make_shared is used
		class HugeClass
		{
			int data[2014];
		public:
			HugeClass() { std::cout << "ctor" << std::endl; }
			~HugeClass() { std::cout << "dtor" << std::endl; }
		};

		{ //weak pointer lifetime scope
			std::weak_ptr<HugeClass> wptr;
			{ //shared pointer life time scope
				auto sptr = std::make_shared<HugeClass>();
				wptr = sptr;
			} //leave scope, sptr drops reference count to 0! but dtor is called, but memory is not freed. (this may not be true for all implmentations)

			if (wptr.expired())
			{
				std::cout << "wptr registers as expired, but is keeping the control block alive!" << std::endl;
			}
		} //leaving scope calls weakptr dtor, which finally frees the control block

		{ //weak pointer lifetime scope
			std::weak_ptr<HugeClass> wptr;
			{ //shared pointer life time scope
				auto sptr = std::shared_ptr<HugeClass>( new HugeClass() ); //forces two memory allocations, one for type and one for control block
				//the above line is exception safe because ONLY a new is happening in the arguments, the compiler can't reorder anything
				wptr = sptr;
			} //leave scope, sptr drops reference count to 0! memory is freed for object, but control block memory is not freed. this is good because we free the "huge class" memory!

			if (wptr.expired())
			{
				std::cout << "wptr registers as expired, but is keeping the control block alive!" << std::endl;
			}
		} //leaving scope calls weakptr dtor, which finally frees the control block
	}

	//a note on exception safety
	{
		auto deleter = [](Demo* rawPtr) {std::cout << "deleting : " << rawPtr << std::endl; delete rawPtr; };

		//version 1, not exception safe
		{
			//reordering may cause exception before shared_ptr gains control over the allocated "Demo" class
			dangerous_misuse_potential(std::shared_ptr<Demo>(new Demo(5)), calculate());
		}

		//version 2, exception safe but slow!
		{
			//this is exception safe, if sptr_dlt throws exception in allocating control block, it will delete the "new Demo(5)"
			std::shared_ptr<Demo> sptr_dlt(new Demo(5), deleter);
			
			//passing an lvalue of sptr_dlt copies the shared pointer, meaning an atomic read of the reference count
			dangerous_misuse_potential(sptr_dlt, calculate());
		}

		//version 3, exception safe and fast!
		{
			//this line is exception safe, see version 2
			std::shared_ptr<Demo> sptr_dlt(new Demo(5), deleter);

			//passing an rvalue! move doesn't need the atomic read of the reference count
			dangerous_misuse_potential(std::move(sptr_dlt), calculate()); //this will null out sptr_dlt
			if (!sptr_dlt)
				std::cout << "nulled out the sptr_dlt" << std::endl;
		}
		
	}
}