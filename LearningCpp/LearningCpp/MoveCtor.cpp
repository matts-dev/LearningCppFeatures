//move ctor
//Matt Stone 7/17/16

#include<iostream>
#include<utility>	//std::move();

using namespace std;

struct MovCtorClass {
	int value = 0;
	MovCtorClass(int value) : value(value) { cout << "normal ctor" << endl; }
	//move constructor
	MovCtorClass(MovCtorClass&&) noexcept;	//move ctor
	void reset() { this->value = 0; }		//reset method for move ctor

	//copy constructor (needed for passing by value)
	MovCtorClass(MovCtorClass& toBeCopied) : value(toBeCopied.value) { cout << "copy ctor" << endl; }
};

MovCtorClass returnAndAllByValue(MovCtorClass byValue);

// ----------------------------------------- MAIN -----------------------------------------
void movectors() {
	MovCtorClass obj1(5);
	cout << "obj1 value is: " << obj1.value << endl << endl;

	//move constructor call 
	MovCtorClass obj2 = move(obj1);
	cout << "obj1 value is: " << obj1.value << endl;
	cout << "obj2 value is: " << obj2.value << endl << endl;

	//move construct from function
	MovCtorClass obj3 = returnAndAllByValue(obj2);	//requires a copy constructor for passing argument


}

// ------------------------------------ definitions  ------------------------------------
MovCtorClass::MovCtorClass(MovCtorClass&& movable) noexcept {	//noexcept is required for move contor 
	//include noexcept in .cpp file too
	cout << "move constructor" << endl;
	this->value = move(movable.value);
	movable.reset();	//put the moved object in a valid state <IMPORTANT>
}


MovCtorClass returnAndAllByValue(MovCtorClass byValue) {
	return byValue;
}
