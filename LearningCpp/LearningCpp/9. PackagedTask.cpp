//Packaged Tasks
//Matt Stone 7/27/16

#include<iostream>
#include<thread>
#include<mutex>
#include<future>

namespace j27 {
	int echoInt(int x) { return x; }
}
using namespace std;

// Packaged task are useful because they link callable object to a future
void packagetasks() {
	cout << "packaged tasks" << endl;

	//packaged tasks are created differently than threads, you canot pass arguments
	packaged_task<int(int)> package1(&j27::echoInt);
	
	//... do stuff

	//get future, then get value
	package1(10);	//this is how you pass an argument to a packaged_task
	int p1Val = package1.get_future().get();

	cout << "value from package1: " << p1Val << endl;
		
	//to pass an agument, bind a function with an argument
	packaged_task<int()> package2(bind(&j27::echoInt, 10));
	future<int> fu = package2.get_future();

	//... more work

	//... use future
	package2();
	cout << "value from package2: " << fu.get() << endl;
}