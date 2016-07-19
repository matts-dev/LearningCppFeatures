//Move assignmnet operator
//Matt Stone

#include<iostream>
#include<utility>

using namespace std;


struct MvClass {
	int value = 0;
	MvClass(int value) : value(value) {}
	MvClass(MvClass& obj) : value(obj.value) { cout << "copy ctor" << endl; }
	MvClass(MvClass&& obj) noexcept { this->value = move(obj.value); obj.reset(); cout << "move ctor" << endl; }	 //move ctor
	void reset() { this->value = 0; }

	MvClass& operator= (MvClass&& obj) noexcept {
		cout << "move asn operator" << endl;
		this->value = move(obj.value);
		obj.reset();
		return *this;	
	}
	MvClass& operator= (MvClass& obj) { cout << "ref asn operator" << endl; value = obj.value; return *this; }
};

void moveAsn() {
	//todo: use the move assignment operator and analyze output
	MvClass obj1(10);
	MvClass obj2 = obj1;			//copy constructor				//this passes & to obj2
	MvClass obj3 = move(obj1);		//move constructor				//this passes && to obj3
	obj3 = obj1;					//normal assigment operator
	obj3 = move(obj1);				//**move assignment operator**	//requires the overload

}

//selftest
//write a move assingment operator



