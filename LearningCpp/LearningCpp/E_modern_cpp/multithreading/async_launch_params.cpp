#include<iostream>
#include <future>

namespace
{
	void function_worker()
	{
		std::cout << "working" << std::endl;
	}
}

static int main_v()
{
	//there's two async launch policies; deferred and async.

	//the default async call bitwise 'or's the two launch parameters
	//this allows async to chose how work is done (either concurrently or in the same thread) 
	//		it's also how it is able to silently handle when there are no more threads available, async just switches to a deferred state and runs the function object when the future is used.
	auto future = std::async(std::launch::async | std::launch::deferred, &function_worker);
	auto future_implicit = std::async(&function_worker); //same as above

	//std::launch::async - future will be completed on another thread concurrently
	//std::launch::deferred - futured will be completed on current thread when requested

	//using default launch parameters has some potential issues:
	//	1. unknown if async will be run on another thread or run on same thread
	//  2. unknown if async will be run concurrently or sequentially (same thread)
	//  3. unknown if async will ever complete at all (if it is deferred and the future never calls get() or or wait())

	//sideeffects of the above notes
	// --Thread local variables may exhibit weird behavior, because if it is run concurrently, it will modify its own set of thread-local variables; if it is run on same thread it will modify the current threads thread local variables
	// --loops that use the futures wait_for may never terminate if the future is deferred
	//			wait_for(TIME) waits for a given time or until the future completes running
	//			this function indefinitely return std::future_status::deferred and never return std::future_status::ready if the async is in a deferred state rather than an async state.
	//					there isn't a direct way to ask if a future's source is deffered or async
	//						you must call something like "future.wait_for(0s)" and test if it returns a std::future_status::deferred
	//			these bugs likely don't show up in testing because they require heavy loads to use up the available threads

	//The default launch configuration is okay under the following conditions
	//		1. the task doesn't have to be ran concurrently
	//		2. thread local variables are irrelevant 
	//		3. its okay that the task my never execute, or you're sure that wait() or get() will be called by all paths.
	//		4. the deferred status is considered at all places of wait_for() and wait_until() calls

	//below is how to specify that the future will be run concurrently.
	auto future_concurrent = std::async(std::launch::async, &function_worker); //doing this no longer protects us from running out of software threads


	std::cin.get();
}