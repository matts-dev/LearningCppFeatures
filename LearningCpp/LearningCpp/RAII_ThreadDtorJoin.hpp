//Class that causes current thread to join a living thread on dtor
//Matt Stone 7/20/16
#include<thread>
#include<iostream>
using namespace std;
class RAIIThreadWrapper {
	thread* threadPtr = nullptr;
public:
	RAIIThreadWrapper(thread& td) : threadPtr(&td) {};
	~RAIIThreadWrapper() { cout << "RAII wrapper joining thread" << endl; threadPtr->join(); }
};