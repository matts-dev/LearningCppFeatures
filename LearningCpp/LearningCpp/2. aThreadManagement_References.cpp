//Thread Management 
//Matt Stone 7/20/16

#include<iostream>
#include<thread>
#include<string>
#include"RAII_ThreadDtorJoin.hpp"
using namespace std;

void printStr(string&);

//Example 2
void threadManagement() {
	string passThisByRef = "this is a message that should not be copied";

	//threads do not take references, so must be passed using std::ref
	thread t1(&printStr, std::ref(passThisByRef));	//alternatively, you can use ptr

	//thread t1(&printStr, passThisByRef);		 //<- does not pass by reference 
	//thread t1(&printStr, move(passThisByRef)); //<- moves using move symantics
	//thread t1(&printStr, &passThisByRef);		 //<-passing address, we can use pointers with thread args 

	//wrapper will call .join() on dtor to wait for thread to finish
	RAIIThreadWrapper wrapper(t1);

	printStr(passThisByRef);
	
}

void printStr(string& str) {
	cout << str << endl;
	cout << "adr is: " << &str << endl;
	
}
