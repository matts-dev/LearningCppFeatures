//Linked Lists 
//Matt Stone 6/11/2016

#include<iostream>
#include<list>

using namespace std;

void lists(){
	//How to make a list, optional way of initializing it to the size
	list<int> intList = { 1, 2, 3, 4, 5 };

	//Adding variables to a list
	for (int i = 0; i < 5; ++i){ intList.push_back(i + 6); }

	//printing an entire list wit ha for-each loop
	for (int i : intList) { cout << i << ' '; }
	cout << endl << endl;

	//List have pointers to front and back
	cout << "Front element: " << intList.front() << endl;
	cout << "Back element: " << intList.back() << endl;
	cout << "Size: " << intList.size() << endl << endl;


	/*INSERTING*/
	//Inserting in a list requires iterators
	cout << "inserting 100 into the list before 5" << endl;
	list<int>::iterator it = intList.begin();

	//find the 5th element or the end
	while (*it != 5 && it != intList.end()){
		it++;
	}
	//check if iter is at the end
	if (it != intList.end()){
		// insert takes the postion of the iterator, pushing that position back
		intList.insert(it, 100);
	}
	//Print the list
	for (int i : intList) cout << i << ' ';
	cout << endl << endl;

	/*ERASING*/	
	cout << "erasing the 100 that was inserted" << endl;
	//move an iterator using a for loop (see while example earlier)
	for (it = intList.begin(); it != intList.end() && *it != 100; ++it);

	//check if list is at the end, don't want to remove element passed end
	if (it != intList.end()){
		intList.erase(it);
	}
	for (int i : intList){
		cout << i << ' ';
	} cout << endl << endl;

	//Erase a range
	cout << "Erasing a range [4,6] using two iterators; [inclusive, exclusive]" << endl;
	auto start = intList.begin();
	auto end = intList.end();		//this is 1 passed the last element

	//LOOP FROM START: best way to set iterators is to start from front (see reverse iteration next)
	while (*start != 4 && start != intList.end()){
		start++;
	}
	//LOOP FROM END: when looping from end, you cannot derefernce the n+1 pointer
	while (end != intList.begin()){// && *end != 6){ <- cannot check this because .end() isn't assignable; .end()-1 is assignable
		//make sure it is dereferencable, and then check if it is target value
		if (end != intList.end() && *end == 6){
			break;
		}
		//not there yet, decrement
		end--;
	}

	//intList.insert(end, 555);
	intList.erase(start, end);	//runtime exception if you mix these up
	for (int i : intList) cout << i << ' '; 
	cout << endl << endl;


	//You can insert at the end (instead of push_back)
	cout << "inserting with an iterator at .end(); " << endl;
	it = intList.end();
	intList.insert(it, 999);
	for (int i : intList) cout << i << ' '; cout << endl << endl;

	//quicker way to insert at the end
	intList.insert(intList.end(), 888);
	cout << "one line insert:\t list.insert(list.end(), 888); " << endl;
	for (int i : intList) cout << i << ' '; cout << endl << endl;

}