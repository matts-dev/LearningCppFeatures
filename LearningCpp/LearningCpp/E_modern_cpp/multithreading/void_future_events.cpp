#include<iostream>
#include <future>
#include<chrono>
using namespace std::chrono_literals;

namespace
{
	void sender_thread(std::promise<void>* event_source)
	{
		std::this_thread::sleep_for(3s);

		std::cout << "<S> I'm the event source, I'm ready to send an event in 1 second " << std::endl;
		std::this_thread::sleep_for(1s);
		//... doing some work
		event_source->set_value();
	}

	void receiver_thread(std::future<void>* event_destination)
	{
		std::cout << "<D>Hi, I'm the destination thread!" << std::endl;
		std::cout << "<D>I'm going to go asleep until I'm needed!" << std::endl;
		event_destination->get();

		std::cout << "<D>The event triggered me!" << std::endl;
	}

	std::mutex mut;
	std::condition_variable cond;
	std::atomic<bool> event_occured = false;

	bool read_event_flag()
	{
		return event_occured;
	}

	void sender_thread_cond()
	{
		std::this_thread::sleep_for(3s); //give time for receiver thread to fall asleep
		std::lock_guard<std::mutex> lock{mut};

		std::cout << "<S_COND> Hey, I'm the sender. I will send my event in 1 second" << std::endl;
		event_occured = true;
		std::this_thread::sleep_for(1s);
		cond.notify_all(); //could use notify_one() here
	}

	void receiver_thread_cond()
	{
		std::cout << "<D_COND> Hey, I'm the receiver thread; I'm going to sleep until my event wakes me up!" << std::endl;

		std::unique_lock<std::mutex> lock(mut); //notice that cond variables use unique_lock, not lockguards (I guess they need the ability to lock/unlock)
		cond.wait(lock, &read_event_flag); //the function pointer (which could be swapped with potentially a lambda) checks for spurious wakes
		lock.unlock();

		std::cout << "<D_COND> I'M AWAKE!" << std::endl;
	}
}

int main()
{
	{
		//you could perhaps define these in some namespace or static class scope
		std::promise<void> event_signaler;
		std::future<void> event_destination = event_signaler.get_future();


		//if we want to pass by reference, then thread arguments need to be wrapped with std::ref(ARGUMENT) because std::threads always make copies of their arguments
		std::thread t1(&sender_thread, &event_signaler);
		std::thread t2(&receiver_thread, &event_destination);


		//make sure threads are not joinable when their dtors are called.
		t1.join();
		t2.join();
	}
	//why not use a condition var?
	//condition vars suffer from:
	//	1. requiring a mutex
	//	2. waking from spurious wakes (they wake up without being signaled due to hardware implementations https://softwareengineering.stackexchange.com/questions/186842/spurious-wakeups-explanation-sounds-like-a-bug-that-just-isnt-worth-fixing-is )
	//	3. requiring a flag to handle spurious wakes
	//  4. if condition signals are broadcasted before the thread waits, then the signal will be lost and the thread will hang!
	
	//issues with using promise/future for event communication
	//	1. promise and futures communicate through a shared heap based structure, which has its own costs (and I believe there are atomic refernce counting for shared_futures)

	{
		std::cout << "\n\n\n\n\n" << std::endl;
		std::thread t1(&sender_thread_cond);
		std::thread t2(&receiver_thread_cond);

		t1.join();
		t2.join();
	}
	std::cin.get();
}