//Once Flag
//Matt Stone 7/22/16

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

namespace j22 {
	once_flag flag;
}

void onceflags() {
	//this will only be called once, useful for opening files in thread situations
	call_once(j22::flag, []() {cout << "lambda function" << endl; });
	//will save having to lock and unlock mutexes https://www.youtube.com/watch?v=IBu5ka1MQ7w

}