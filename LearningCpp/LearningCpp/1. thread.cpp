//Basic STD Threads
//Matt Stone
#include<iostream>
#include<thread>

using namespace std;
void putinthread() { cout << "function for thread" << endl; }

void threadsBasic() {
	thread td(&putinthread);	//you can pass functions, lambdas, and funct; variadic arguments after function adr are for parameters
	td.join();	//main thread will not wait on td thread

	//allow main thread to become completely independent from other thread
	//td.detach();	//main permanently abandons thread - thread is now daemon
	//notice, if detached the endl will process first
	cout << "main" << endl;

	//attempt to join a thread that has been detached
	if (td.joinable()) {
		td.join();	//main waits on td thread
	}
}
