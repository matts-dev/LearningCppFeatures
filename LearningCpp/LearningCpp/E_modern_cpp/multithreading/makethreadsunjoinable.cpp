#include<iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace{
	void worker_func(){
		std::cout << "working" << std::endl;
	}
}
//Handling the dtor termination.
class RAII_thread
{
public:
	enum class DtorAction { JOIN, DETATCH };

	RAII_thread(std::thread&& inThread, DtorAction action = DtorAction::JOIN) :
		action(action),
		t(std::move(inThread))
	{
	}

	~RAII_thread()
	{
		if (t.joinable())
		{
			if (action == DtorAction::DETATCH)
				t.detach();
			else
				t.join();
		}
	}
	std::thread& get_thread() { return t; }

private:
	DtorAction action;
	std::thread t; //last because it's good practice to put members dependent on other members... after the member they dependent on. 
}; //end RAII thread class

int main()
{
	//joinable threads: 
	//	1. thread that could be running 
	//	2. thread that is blocked/waiting or 
	//	3. a thread that has ran to completion
	//unjoinable threads:
	//	1.	default constructed threads (no function object passed)
	//	2.  threads moved FROM (this passes underlying handle to software thead, basically making the thread as if it didn't have a function to run)
	//  3.  thread that have been joined, because now the PC is passed the join call and the thread is complete
	//  4. threads that have been detached

	/*
		Why joinability matters:
			When the dtor of a std::thread object is called, if the thread is joinable then the entire program terminates!
	*/
	{
		std::thread t(&worker_func);

		bool ifvaluefalse_programcrashes = true; //this isn't a race condition, threads that complete are still considered joinable!
		//completed threads should be joinable... because if we're wanting to join a thread we wouldn't want there to be a race condition on joining (ie joining after it completed exiting the program)
		if (ifvaluefalse_programcrashes)
		{
			t.join();
		}
		else
		{
			//no join called, so thread t dtor will be called while thread t is still joinable (even if it already completed)
		}
	}//t's dtor called here! 

	//Why do threads terminate the program if their dtor is called while they're still joinable?
		//because if it didn't, it would have to choose between the two scenarios
		//option 1: have the dtor call join
		//		this would cause use to wait on a thread we don't care about, like in the above scoped example; perhaps we don't want to wait on t.
		//		however, if we did wait on t, then it could potentially cause the program to hang at the spot of its dtor call, causing weird performance things.
		//option 2: have the dtor call detach
		//		this would allow a thread to continue even when the scope is exited...
		//			if that thread is modifying local variables of the previous scope(through pointers or with lambndas), then we get undefined behavior!
	//So, this is basically a choice to be made. detach or join, and the thread dtor does not make this decision.
	{
		RAII_thread t_detach(std::thread(&worker_func), RAII_thread::DtorAction::DETATCH);
		RAII_thread t_join(std::thread(&worker_func), RAII_thread::DtorAction::JOIN);
	} //t will leave scope, and join/detach -- not crashing this program!

	std::cout << "program over" << std::endl;
	std::cin.get();
}

