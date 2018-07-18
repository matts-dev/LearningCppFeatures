#include<iostream>
#include<thread>
#include <future>

namespace
{
	bool thread_work()
	{
		std::cout << "working..." << std::endl;
		return true;
	}

	bool throw_exception()
	{
		std::cout << "I'm now running!" << std::endl;
		throw std::runtime_error("An error!");
	}
}


static int main_v()
{
	//the two threading options
	{
		//thread based
		std::thread t(thread_work);

		//task-based	 (thread_work is considered a task)
		auto future = std::async(thread_work); //may or may not run concurrently when launched like this

		t.join();
		future.wait();
		
		//task based allows access to return values
		bool task_result = future.get();
	}

	//prefer task-based to thread based (there are some situations where this may not be true, see next .cpp on async modes).
	//1. task based offers an easy way to read return values
	//2. task based launchs give you an way to check for exceptions that occured during running, thread just terminate()s. 
	{
		//force the async call to run concurrently with async...
		auto future = std::async(std::launch::async, throw_exception);
		future.wait();  //the exception will be throw here, but wewon't see it until we call get()
		try
		{
			bool fut_ret = future.get();
		}
		catch (std::exception e){
			std::cout << "caught exception in main thread" << std::endl;
		}
	}
	//3. task based automatically manages threads for you, if the system cannot start another thread then it will run within the same thread, instead of throwing an exception
	//		thread will throw an exception (std::system_error) if no avaiable software/hardware threads; async just switches to a "deferred" mode and will run the computation when wait() or get() is called.
	//		types of threads
	//			1. hardware threads (cores)
	//			2. software threads (OS threads) -- these are a limited resource too
	//			3. std::threads - handles to underlying software threads (that is, if the thread isn't in a null/detached state)
	//		when async is launched in its default state, it will only run concurrently if there's an available thread, otherwise it will wait for wait() or get() to run (on the current thread)
	//4. async helps with oversubscription
	//		oversubscription - when there's more software threads ready to run than available hardware threads
	//			-it has a lot of problems (context switches, creates cache problems (cold misses, and removes "old" thread cache items that will likely be needed in the near future)
	//		async will make decisions about whether oversubscription is occuring, and it is likely to have a more complete picture of the machine's state, which means it may be able to make better decisions about whether to run as async or deferred
	//5. using async automatically keeps up to date
	//		as cutting-edge features are adding to the concurrency library, the async code will automatically be updated to use them 
	//			feature such as system-wide thread pools


	//situations where using async may be inappropriate
	//	1. need accesing to underlying thread api
	//  2. need to optimize thread-usage for appplication
	//  3. need to write threading technology not in the c++ api

}