//cpp interfaces - cpp does not have interfaces, so the equivalent is to have a class of nothing but pure virtual functions
//Matt Stone 7/7/16
#include<iostream>
using namespace std;


class Interface_J7 {	
public:
	virtual void speak() const = 0;
	virtual void speak2() const = 0;
	virtual void speak3() const = 0;
	//virtual ~Interface_J7() = 0;		//virtual destructor is important in an interface, will need to define
	virtual ~Interface_J7() {};			//virtual destructor give an implmentation
};

class InterfaceUsingClassJuly7 : public Interface_J7 {
public:
	//make sure to include const, const is part of the signature
	void speak() const { cout << "speak()" << endl; }
	void speak2() const { cout << "speak2()" << endl; }
	void speak3() const { cout << "speak3()" << endl; }
};

void interfaces() {
	InterfaceUsingClassJuly7 obj;
	InterfaceUsingClassJuly7* ptr = &obj;
	Interface_J7* interfacePtr = &obj;

	interfacePtr->speak2();	//using an interface to call something that inherits from it
}
