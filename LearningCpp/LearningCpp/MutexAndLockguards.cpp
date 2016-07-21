//Mutexes and basic lock gaurd 
//Matt Stone 7/21/16

#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include"RAII_ThreadDtorJoin.hpp"

using namespace std;

//global mutex (generally want to bundle mu with resources to prevent un-intended data races)
mutex mu;	//could make this a field in a class

void function1(void(*fptr)(string&), string& msg);
void sharePrintRawMutex(string& msg);
void sharedPrintLockGuard(string& msg);

void mutexes() {
	//function pointers:
	//	&sharePrintRawMutex
	//	&sharedPrintLockGuard

	string t1msg = "thread: hi";
	//pass the version of the function as second parameter (it is a function pointer too since first arg of function1 is such)
	thread t1(&function1, &sharedPrintLockGuard, ref(t1msg));
	RAIIThreadWrapper t1wrapper(t1);

	string mainmsg = "main: hey";
	function1(&sharedPrintLockGuard, mainmsg);


}

//accepts a function pointer that uses a mutex. 
void function1(void(*fptr)(string&), string& msg) {
	for (int i = 0; i < 100; ++i) {
		fptr(msg);
	}
}

//Raw mutex usage
void sharePrintRawMutex(string& msg) {
	//generally a bad idea to use a raw mutex
	//if exception is thrown between lock/unlock it will stay locked indefinitely
	mu.lock();
	cout << msg << endl;
	mu.unlock();
	//this_thread::sleep_for(chrono::milliseconds(10)); //add a pause
}

//RAII lockgaurd on mutex
void sharedPrintLockGuard(string& msg) {
	lock_guard<mutex> lockguard(mu);
	cout << msg << endl;
	//leaving scope will - lockgaurd dtor will free mu;

}

