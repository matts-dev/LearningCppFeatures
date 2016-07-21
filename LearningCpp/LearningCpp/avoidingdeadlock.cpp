//avoiding deadlocks
//Matt Stone 7/21/16

#include<iostream>
#include<thread>
#include<mutex>
#include"verboseclasses.h"

using namespace std;
mutex mu1;
mutex mu2;

//in this example, assume cout is the shared resource
void avoidDeadlock() {
	 //1. SEQUENTIAL LOCKING
	{
		lock_guard<mutex> lock(mu1);
		cout << "mu1 is locked and will unlocked when } is reached" << endl;
	}
	//closed lock1, open locked 2
	{
		lock_guard<mutex> lock(mu2);
		cout << "mu2 locked, and will be freed when scope {} is left" << endl;
	}

	//2. LOCKING ORDER CONSISTENT
	{
		lock_guard<mutex> lockFirstAlways(mu1);
		lock_guard<mutex> lockSecondAlways(mu2);

		//if locks are always done in the above order, then mu2 can never be locked before mu1
		//this will make the locking deadloc safe, but it is hard to remember order of locks, so see 3.
	}


	//3. USING STANDARD LOCK - it uses algorithms to prevent deadlock
	{
		lock(mu1, mu2);	//think of this as ensuring a locking order to prevent deadock
		lock_guard<mutex> lock(mu1, adopt_lock);	//will adopt ownership of the lock
		lock_guard<mutex> lock(mu2, adopt_lock);	//will adopt ownership, and open lock on leaving scope
	}

}