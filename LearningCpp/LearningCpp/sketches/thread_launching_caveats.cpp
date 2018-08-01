#include<iostream>
#include<thread>

namespace{
	class M
	{
	public:
		void foo(int x) {
			std::cout << "member function: " << x << std::endl;
		}

		void operator()(){
			std::cout << "used as functor" << std::endl;
		}
	};

	void accepts_arg_ref(M& param)
	{
		std::cout << "argument: " << &param << std::endl;
	}
}

int main()
{
	M obj;

	//launch a thread that uses a member function, this capability is done within the invoke call (I'm not sure how it determines at compiletime that obj is not an argument, but to be called.
	std::thread t1(&M::foo, std::ref(obj), 5); //syntax for launching member function (this apparently doesn't need std::ref?)
	t1.join();

	//launch thread as a functor
	std::thread t2(std::ref(obj));  //must wrap in std::ref unless we want a copy to be made
	t2.join();

	//in this case, obj is an argument to the function
	std::thread t3(&accepts_arg_ref, std::ref(obj)); 
	t3.join();
	std::cin.get();
}