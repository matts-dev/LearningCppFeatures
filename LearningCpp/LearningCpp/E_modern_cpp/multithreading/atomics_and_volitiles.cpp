#include<iostream>
#include <atomic>
#include <thread>

namespace
{
	//atomics not only ensure atomic operations, but they prevent compiler reordering of statements around the atomic (and it writes assembly that prevents hardware reordering)
	//no code preceeding an atomic may be reordered before the atomic is used
	std::atomic<int> atomic_int = 0;
	int just_a_int = 0;

	void atomic_threadfunc_A(){
		for (int i = 0; i < 5000000; ++i)
			//increment is normally 3 operations: read, increment, store; which has issues with concurrency!
			atomic_int++;
	}
	void atomic_threadfunc_B() {
		for (int i = 0; i < 5000000; ++i)
			//increment is normally 3 operations: read, increment, store; which has issues with concurrency!
			atomic_int++;
	}

	void not_atomic_threadfunc_A(){
		for (int i = 0; i < 5000000; ++i)
			//increment is normally 3 operations: read, increment, store; which has issues with concurrency!
			just_a_int++;
	}
	void not_atomic_threadfunc_B(){
		for (int i = 0; i < 5000000; ++i)
			//increment is normally 3 operations: read, increment, store; which has issues with concurrency!
			just_a_int++;
	}

	//volatile just prevents certain optimizations from removing special memory calls
}

static int main_v()
{
	{
		std::cout << "not using atomics" << std::endl;
		std::thread t1(&not_atomic_threadfunc_A);
		std::thread t2(&not_atomic_threadfunc_B);
		t1.join();
		t2.join();
		std::cout << "the value should be 10000000 if everything each increment happened atomically, the value is:" << just_a_int << std::endl;
	}
	{
		std::cout << "using atomics" << std::endl;
		std::thread t1(&atomic_threadfunc_A);
		std::thread t2(&atomic_threadfunc_B);
		t1.join();
		t2.join();
		std::cout << "the value should be 10000000 if everything each increment happened atomically, the value is:" << atomic_int << std::endl;
	}

	//-------------------------------------- volatile
	volatile char special_memory[256]; //this may communicate to a monitor and by updating memory you send messages, so you don't want those updates to be optimized out!
	char normal_memory[256]; //optimizations are allowed to be made on this!

	special_memory[6] = 'a';
	special_memory[6] = 'b'; //not allowed for thsi to be optimized out since we're dealing with "volatile" memory, such memory assignments (or reads) can be used for communication with devices!

	normal_memory[4] = 'a'; //this can be optimized out since we immediately overwrite it (it doesn't seem like the assmebly overwrites it however)
	normal_memory[4] = 'b'; 

	std::cin.get();
}