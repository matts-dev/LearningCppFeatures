//Thread Management
//Matt Stone 7/20/16

#include<iostream>
#include<thread>
#include"RAII_ThreadDtorJoin.hpp"
using namespace std;

void print100(int start);
void print50(int start);

//Example 1 (see example 2)
void threadManagementTryCatch() {
	//threads must be joined or detached before thread goes out of scope!
	thread t1(&print100, 0);
	
	//We need t1 to finish if this thread throws exception, so we wrap in try-catch
	//The try catch will wait on t1 to finish, before re-throwing the exceptoin to be handled
	try {
		//alternative approach: RAII, having wrapper class that joins in dtor, see other file
		print50(100); 

	}
	catch (exception all) {
		t1.join();	//wait on other thread if this thread finishes
		throw;
	}
	t1.join(); 
}


//implmentations of functions
void print100(int start) {
	for (int i = 0; i < 100; ++i) {
		cout << i + start << endl;
	}
}

void print50(int start) {
	for (int i = 0; i < 50; ++i) {
		cout << i + start << endl;
	}
}