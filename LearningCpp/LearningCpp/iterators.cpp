//iterators
//Matt Stone - 6/10/2016
#include <iostream>
#include <vector>
#include <string> 
#include <deque>

using namespace std;
void iters(void){
	//There are 5 types of iterators in STL, not all contains support every iterator type

	//Vectors support all 5, so I am using that as an example
	vector<int> intVector;
	for (int i = 1; i < 11; ++i){
		intVector.push_back(i);
	}

	//getting an general iterator - which is essentially a pointer
	vector<int>::iterator it; //could use auto if you get it from object

	//Input iterator - only gaurantees 1 pass through - ie it is not multipass safe.
	for (it = intVector.begin(); it < intVector.end(); ++it){
		cout << *it << ' ';
	}	
	cout << endl;
	
	//getting iterators - these will become invalid if container is changed
	vector<int>::iterator start = intVector.begin();
	auto end = intVector.end();	// has same type as above, but just demonstrating use of auto keyword
	
	//Output iterator - not multipass - allows writing to object in container
	for (it = intVector.begin(); it < intVector.end(); ++it){
		++(*it);	//change by 1
		cout << *it << ' ';
		--(*it);	//correct change
	}
	cout << endl;

	//Forward Iterator - multipass guarantee! - allows reading/writing
	for (it = intVector.begin(); it < intVector.end(); ++it){
		cout << *it << ' ';
	}
	for (it = intVector.begin(); it < intVector.end(); ++it){
		cout << *it << ' ';
	}
	cout << endl;

	//Bidirectional - foward or backward - multipass guarantee (BAD WAY; see reverse iterators)
	for (it = (intVector.end() - 1); it >= intVector.begin();){
		cout << *it << ' ';
		//last iteration crashes program becaues iterator cannot be decremeted
		if (it != intVector.begin()){
			--it;
		}
		else {
			//stop decrement on last iteration 
			break;
		}
	}
	cout << endl;



	//Random Access Iterator - multipass guarantee - allows indexing
	cout << "it[7] \t\t:" << it[7] << endl;

	//ptr arth
	it = start + 7;
	cout << "it = start + 7 \t:" << *it << endl;

	it -= 3;
	cout << "it -= 3 \t:" << *it << endl;


	//EXAMPLES:
	//REVERSE ITERATORS
	deque<int> deque4 = { 1, 2, 3, 4, 5 };
	//showing how to initialize reverse iterators, then how to do it with for
	deque<int>::reverse_iterator rit = deque4.rbegin();
	deque<int>::reverse_iterator rend = deque4.rend();
	cout << "using reverse iterators" << endl;
	//NOTICE: reverse iterators STILL USE INCREMENT
	for (auto rit = deque4.rbegin(); rit != deque4.rend(); rit++){
		cout << *rit << ' ';
	}cout << endl << endl;


}