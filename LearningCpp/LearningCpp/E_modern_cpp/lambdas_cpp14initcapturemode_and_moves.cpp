#include<iostream>
#include<memory>
#include <functional>
int main()
{
	class Car
	{

	public:
		void drive() { std::cout << "vroom" << std::endl; }
		virtual ~Car() { std::cout << "dtor" << std::endl; }
	};

	//cpp11 offers no way to get a "move only" object (such as a unique_ptr) into a closure.
	//cpp14 offers init capture that can be used to get a move-only object into the closure.

	{
		//init capture allows you to name the variable (ie member field) in the closure
		//init capture alos allows you to write an expression for its initialization 
		std::unique_ptr<Car> uptr = std::make_unique<Car>();

		//init captures lets us name the variable moved_ptr and give it a value!
		auto closure = [moved_ptr = std::move(uptr)]() { moved_ptr->drive(); }; //move occurs at this location
		closure();

		//auto closure2 = closure; capturing a move-only prevents this from compiling
	}

	{
		//another name for init-capture is "generalized capture
		//you can create variables in the init-capture (this prevents them from being created every time the closure is invoked)
		auto closure = [ptr = std::make_unique<Car>(), ptr2= std::make_unique<Car>()]{ 
			ptr->drive(); 
			ptr2->drive();
		};
		closure();
	}

	{
		//emulating move capture in cpp11:
		//	put to-be-moved object in a std::bind object with give the lambda a reference to that object
		auto uptr = std::make_unique<Car>();
		auto func_from_move=
			std::bind(
				[](const std::unique_ptr<Car>& moveonly) {moveonly->drive(); },		
				std::move(uptr)	 //rvalue parmeter are move-constructed to std::bind's data members (normally, lvalues are copy constructed in std::bind)
			);
		func_from_move();
	}

	std::cin.get();
	return 0;
}