//Unique Lock
//Matt Stone 7/22/16

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex mut;

//Unique cost more resources than lock guard.
void uniquelocks() {
	//unique locks allow you to lock and unlock the mutex, rather than relying on lock_guard to go out of scope
	unique_lock<mutex> uLocker(mut, defer_lock);	//defer_lock === wait to lock
	cout << "mutex no yet locked" << endl;

	uLocker.lock();
	cout << "mutex is now locked, use shared data" << endl;
	// ... shared data code
	uLocker.unlock();

	cout << "mutex is now unlocked, data is free" << endl;


	//later...

	// ... other threads working on data
	uLocker.lock();	//will attempt to lock thread, but will have to wait on other threads to unlock
	//... use data
	uLocker.unlock();






}