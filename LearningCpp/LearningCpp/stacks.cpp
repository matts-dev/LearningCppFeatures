//stacks, queues, deques
//Matt Stone
#include<iostream>
#include<stack>
#include<queue>
#include<deque>
#include<list>

using namespace std;
void stacks(void){

	//Generall stack (uses underlying deque)
	stack<int> intStack;

	//populate stack
	for (int i = 0; i < 5; ++i) intStack.push(i);

	//read stack
	while (intStack.size() > 0) {
		//must look at top to access variable
		cout << intStack.top() << ' ';
		//poping a stack doesn't return the variable popped
		intStack.pop();
	} cout << endl << endl;

	//Stacks is a container adapter - it uses a different underlying container
	list<int> intList = { 1, 2, 3, 4, 5 };

	//uses underlying list to be modified
	stack<int, list<int>> stackList(intList);

	//read stack using empty method
	while (!stackList.empty()) {
		cout << stackList.top() << ' ';	//uses tail of list
		stackList.pop();
	} cout << endl;

	//original list isn't affected by poping stack (they're separate objects)
	cout << "list size: " << intList.size() << endl;
	cout << "stack size: " << stackList.size() << endl;

}



//self test
//stacks - stacks are container adapter, not containers themselves 
//make a default stack (default uses deque)
//make a stack using a list container
//check if stack is empty
//add an element to the top of a stack
//remove an element from the top of stack (does this return value in c++?)
//get the top of the stack without popping 

//queues

//deques
