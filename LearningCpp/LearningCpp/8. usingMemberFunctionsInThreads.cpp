//member functions in threads
//Matt Stone 7/26/15

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

namespace j26 {
	mutex mu;
	struct test {
		void f(int a, char c) { lock_guard<mutex> lock(mu); cout << a << ", " << c << endl; }
		void operator()(int a, char c) { lock_guard<mutex> lock(mu); cout << "functor usage" << a << ", " << c << endl; }
	};

}//end j26

void memFunctsInThread() {
	j26::test obj;

	thread t1(&j26::test::f, obj, 1, 'c');		//obj by value
	thread t2(&j26::test::f, &obj, 1, 'c');		//obj by pointer
	thread t3(ref(obj), 1, 'c');				//obj by reference
	thread t4(obj, 2, 'd');						//obj by functor
	thread t5(move(obj), 2, 'c');

	//note: you can also send callable functions as: function ptrs, lambdas, etc.

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}