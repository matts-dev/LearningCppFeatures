//Thread Management RAII to join thread on completion
//Matt Stone 7/20/16

#include<iostream>
#include<thread>
#include"RAII_ThreadDtorJoin.hpp"
using namespace std;

void print100(int start);
void print50(int start);

//Example 2
void threadManagementTryCatchRAII() {
	thread t1(&print100, 0);

	//wrapper will call .join() on dtor to wait for thread to finish
	RAIIThreadWrapper wrapper(t1);

	print50(100);
}

