//Copy and swap idiom
//Matt Stone 7/18/16

#include<iostream>
#include<utility>

using namespace std;

//copy and swap replaces the need for an overloaded move assignment operator

struct CSclass {
	int value = 0;
	CSclass(int value) : value(value) { cout << "norm ctor" << endl; }
	CSclass(CSclass& cpy) : value(cpy.value) { cout << "copy ctro" << endl; }
	CSclass(CSclass&& mv) { cout << "mv ctor" << endl; value = move(mv.value); mv.reset(); }

	void reset() { this->value = 0; }
	void swap(CSclass& obj) { std::swap(this->value, obj.value); }

	//copy and swap
	CSclass& operator= (CSclass copiedByValue) {
		cout << "cpy & swap" << endl;
		//this->value = move(copiedByValue.value); // copied is temp, so don't need to reset
		swap(copiedByValue);
		return *this;	
	}
};


void copyandswap() {
	CSclass obj1(5);
	CSclass obj2(obj1);			//copy ctor
	CSclass obj3(move(obj1));	//move ctor

	cout << endl << endl << endl << "assignment operator" << endl;

	obj3 = obj1;
}

//self test
//write a copy and swap assignment operator

//questions
//How does copy and swap work?					<allow argument to make a copy, then swap for that data>
//Why is copy and swap efficent?				<it is essentially moving the copied data, rather than using it to make a 2nd copy>
//What other approach is there to the copy7swap?<1)pass by reference, then set each field, 2)pass by value, set each field, 3) copy ctor>
