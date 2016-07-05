//Matt Stone
#include <iostream>
#include <vector>
#include "DummyClass.h"
using namespace std;

void vectors(void){
	//std namespace for vectors
	vector<int> intVect;

	//changes the underlying array - does not reserve intVect[9]
	intVect.reserve(20);

	//resizes vector, allows intVect[9] to be used without crash
	intVect.resize(15);

	cout << "reserved 20, resized 15" << endl;
	//Tells the the amount of indeces (size is 15)
	cout << "however, size: " << intVect.size() << '\n' << endl;

	//set [0] to [9]
	for (int i = 0; i < 10; ++i){
		//resize(10) is must; otherwise crash with bad index
		intVect[i] = i;
	}

	//to surpase reserved indeces
	for (int i = 10; i < 20; ++i){
		//Adds to the end of the vector, regardless of index - skips reserved
		intVect.push_back(i);
	}

	//Elements can be also access wit the at
	intVect.at(5) = 100;	//returns dereferenced ptr

	//Get front and back elements
	cout << "front element: " << intVect.front() << endl;
	cout << "back element: " << intVect.back() << endl;

	//for each works on vectors
	cout << "Vector 1:";
	for (int& i : intVect){
		cout << i << " ";
	}
	cout << endl;

	//Iterators
	vector<int>::iterator itbegin = intVect.begin();
	vector<int>::iterator itend = intVect.end();
	auto itbegin2 = intVect.begin();
	auto itend2 = intVect.end();

	cout << "using iterator ";
	for (auto it = itbegin; it < itend; ++it){
		//Changing contents in vector
		*it = 1;
	}
	for (auto it = itbegin; it < itend; ++it){
		//printing contents in vector
		cout << *it;	//could have been done in first loop (it is a ptr) but this was done for clairty
	}
	cout << endl;
	//iterators can be used with pointer arthimetic
	intVect.insert(itbegin + 5, 99);
	intVect.erase(itbegin + 4);	//warning, I think end iterator is now invalid
	
	//will call destructor, unless it's a pointer
	intVect.erase(itbegin + 1);	
	
	// to delete pointers, a manual loop is necessary
	// delete intVect[i] //etc. 
	// intVect.clear();		//does not call delete, just destructors of static objs

	//reset iterators, old iterators invalid due to modifying vector - will throw incomplete iterator error 
	auto itend3 = intVect.end();
	cout << "iterator after inserts using ptr arthimetic ";
	for (auto it = intVect.begin(); it < itend3; ++it){
		// ++it is pointer arthmetic too
		cout << *it;
	}
	cout << endl;

	//clearing the vector 1
	intVect.resize(0);		//may or maynot clear memory

	//clearing the vector 2 - perhaps best option  -CLEAR DOES NOT CALL DELETE ON POINTERS
	intVect.clear();		//WARNING: this will DELETE non-dynamic objects within (they're by value)
	intVect.shrink_to_fit();//cleared (deleted objs), now release memory
	cout << "Vector 1:";
	for (int& i : intVect){
		cout << i << " ";
	}
	cout << endl;

	//Vectors are internally dynamic, thus below is unnecessary
	vector<int>* dynamicVec = new vector<int>();
	dynamicVec->resize(10);
	delete dynamicVec;
	//Don't need to make these dynamic, but that is how.

	//ptr vector
	int x1, x2, x3;
	int x4 = x3 = x2 = x1 = 3;

	//Vectors can be initialized similar to arrays
	vector<int*> ptrVector = { &x1, &x2, &x3, &x4 };
	cout << "\npointer vector dereferences ";
	for (int*i : ptrVector){
		cout << *i << " ";
	}
	cout << endl;

	//Cannot make a vector of references - vectors must be assignable
	//vector<int&> intVector2; //error

	//prior c++ 11 vectors init
	const int size = 3;	//must be const for array safety 
	char a[size] = { 'a', 'b', 'c' };
	vector<char> charVect(a, a + size);

	cout << endl;
	//Looking at vector of objects and how destructors are used
	
	//Make vector
	vector<DummyClass> objVect1;

	//Make objects to contain
	DummyClass test;

	//pass by value
	objVect1.push_back(test);	//makes a copy (with copy constructor?)

	//Show object memory locations
	test.saySomething();
	objVect1.front().saySomething();

	//Delete the objects stored in the array 
	objVect1.clear();

	cout << "\tcleared vector, destructor should be read above" << endl;
	test.~DummyClass();	//normally delete automatically does this, plus this is on the stack.
	cout << "\tcalled destructor on actual object\n" << endl;
	objVect1.~vector();

	//Dynamic doesn't call delete automatically
	DummyClass* dptr = new DummyClass;

	//show memory location of ptr
	dptr->saySomething();

	//create vector and add ptr to it
	vector<DummyClass*> ptrVect2;
	ptrVect2.push_back(dptr);

	//show memory location of item in vector
	ptrVect2.front()->saySomething();

	//call deconstructors
	ptrVect2.clear();
	cout << "Dynamic Object is still alive, though vector was cleared" << endl;
	delete dptr;

	cout << "\n\n Below are end-of-function destructors." << endl;




}


//Self test concepts:
//declare a vector
//set the space of the underlying array
//set the accessable portion of the array
//get the size of the array
//assign something to every active index of the array
//increase the size of an array by adding something
//access elements using .at()
//access elements using[]
//obtain vectors start and end iterators (without using auto)
//insert an element in the middle of an array									(hint: iterators)
//what happened to vector size?
//erase an element from the middle of the
//what happened to vector size?
//loop through a vector using an iterator
//-bonus: loop through using size()
//clear the array
//-using resize()
//-using .clear()
//clear() does what to contained objects?
//clear calls destructor on stack objects, but does not call delete on heap objects
//use a for-each to print the vector
//init pointer vector with {}
//old vectors (before cpp11) - init these
//access teh front of an array
//access the back of an array
