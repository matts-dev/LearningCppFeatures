//Thread Management 
//Matt Stone 7/20/16

#include<iostream>
#include<thread>
#include<string>
#include"RAII_ThreadDtorJoin.hpp"
using namespace std;

void printStr(string&);

//Example 2
void threadManagementHardWare() {
	string passThisByRef = "this is a message that should not be copied";

	//threads do not take references, so must be passed using std::ref
	thread t1(&printStr, std::ref(passThisByRef));	//alternatively, you can use ptr
	printStr(passThisByRef);

	cout <<  endl << "t1 id: " << t1.get_id() << endl;
	cout << "this id" << this_thread::get_id() << endl;
	cout << "hardware concurrency:" <<  thread::hardware_concurrency() << endl;
	t1.join();
}


