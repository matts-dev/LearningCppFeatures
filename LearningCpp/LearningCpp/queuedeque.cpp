//queue and deques
//Matt Stone 6/14/15

#include<queue>
#include<deque>
#include<list>
#include<iostream>

using namespace std;

void queuedeque(void){
	// -------------------------------------- QUEUE -------------------------------------- //
	//Making default queue (which is a deque)
	cout << "default queue (deque)" << endl;
	queue<int> defaultQueue;
	for (int i = 0; i < 5; ++i){
		defaultQueue.push(i + 1);
	}

	//prints out in FIFO mechanism
	while (!defaultQueue.empty()){	//could also use size() > 0
		cout << defaultQueue.front() << ' ';
		defaultQueue.pop();
	} cout << endl << endl;

	//create a queue using another container
	cout << "list initialized queue" << endl;
	list<int> intList = { 33, 44, 55, 66 };
	queue<int, list<int>> listQueue(intList);
	while (listQueue.size() > 0){
		cout << listQueue.front() << ' ';
		listQueue.pop();
	} cout << endl;
	//using a list to initialize a queue doens't affect original list
	cout << "list size:" << intList.size() << " queue size: " << listQueue.size();
	cout << endl << endl;
	
	// -------------------------------------- DEQUE -------------------------------------- //
	
	//Deque is a container, not a adapter/modifier
	deque<int> intDeque = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
	deque<int> deque2;
	while (!intDeque.empty()){
		deque2.push_front(intDeque.front());
		intDeque.pop_front();

		deque2.push_front(intDeque.back());
		intDeque.pop_back();
	}
	deque<int> deque3 = deque2;	//make copy
	deque<int> deque4 = deque3;
	
	//print deque from front
	cout << "printing deque from from" << endl;
	while (!deque2.empty()){
		cout << deque2.front() << ' ';	//must do this to get the value before popping
		deque2.pop_front();	//pop doesn't return the value
	} cout << endl << endl;

	cout << "printing a copy of the deque from back" << endl;
	while (deque3.size() > 0){
		cout << deque3.back() << ' ';
		deque3.pop_back();
	}cout << endl << endl;

	//deques can be accessed with a single iterators
	for (int i : deque4) cout << i << ' '; cout <<  endl;
	cout << "after iterator, deque size is: " << deque4.size() << endl << endl;

	//forward iterator
	cout << "printing deque forward with iterators" << endl;
	for (auto it = deque4.begin(); it != deque4.end(); ++it){	//se below for auto
		cout << *it << ' ';
	} cout << endl << endl;

	//backward iterator
	cout << "printing queue backward with iterators" << endl;
	//showing how to initialize reverse iterators, then how to do it with for
	deque<int>::reverse_iterator rit = deque4.rbegin();
	deque<int>::reverse_iterator rend = deque4.rend();
	//NOTICE: reverse iterators STILL USE INCREMENT
	for (auto rit = deque4.rbegin(); rit != deque4.rend(); rit++){
		cout << *rit << ' ';
	}cout << endl << endl;
	
}

//self test
//queue
//create a default queue
//create a queue from a lst
//get the first element of a que
//release first element of the que
//loop through a queue (ie getting rid of the front)

//deque - double ended queue
//create a deque
// push values to front of deque
// push values to back of deque
// loop through deque with for-each
// loop through deque with forward iterator
// loop through deque with reverse iterator 