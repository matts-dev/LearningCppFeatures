//Basic STD Threads
//Matt Stone
#include<iostream>
#include<thread>

using namespace std;
void putinthread() { cout << "function for thread" << endl; }

void threadsBasic() {
	thread td(&putinthread);

	//make THIS (main) thread wait on another thread
	if (td.joinable()) {
		td.join();	//main waits on td thread
	}

	//allow main thread to become completely independent from other thread
	//td.detach();	//main permanently abandons thread - thread is now daemon
	//notice, if detached the endl will process first
	cout << "main" << endl;
}
