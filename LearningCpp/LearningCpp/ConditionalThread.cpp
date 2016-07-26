//Conditional Variable
//Matt Stone 7/22/16

//todo: incomplete

#include<iostream>
#include<thread>
#include<mutex>
#include<deque>

using namespace std;

namespace j24 {
	void pusher();
	void puller();
	deque<int> que;
	mutex mu;
	condition_variable cond;
	bool dataPushComplete = false;
	bool threadShouldLive = true;
}//end namespace

void ThreadConds() {
	thread t1(&j24::pusher);
	thread t2(&j24::puller);

	//surious waker
	while (j24::threadShouldLive) {
		this_thread::sleep_for(chrono::seconds(3));
		j24::cond.notify_all();
		cout << "awaking threads" << endl;
	}
	cout << "spurious waker completed" << endl;

	t1.join();
	t2.join();

}


void j24::pusher() {
	unique_lock<mutex> locker(j24::mu, defer_lock);
	for (int i = 0; i < 10; ++i) {
		locker.lock();
		j24::que.push_back(i);
		locker.unlock();
		cond.notify_all();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	j24::dataPushComplete = true;
	cond.notify_all();
}


void j24::puller() {
	unique_lock<mutex> locker(j24::mu, defer_lock);
	while (threadShouldLive) {
		locker.lock();
		//wake check function = que has elements OR que has no elements and other thread finished
		cond.wait(locker, []() {return j24::que.size() > 0 || (dataPushComplete && que.size() == 0); });	//will unlock mutex until notified, stops busy waiting
		while (j24::que.size() > 0) {
			cout << que.front() << endl;
			que.pop_front();
		}
		if (dataPushComplete) {
			threadShouldLive = false;
		}
		locker.unlock();
	}
}