//typeid keyword
//Matt Stone - 7/10/16

#include<iostream>
#include<typeinfo>
using namespace std;


namespace j10 {
	//non-virtual class (using structures for public default access)
	struct base1 {};
	struct derv1 : public base1 {};

	//virtual class
	struct base2 { virtual ~base2() {} };
	struct derv2 : public base2 {};
}//end namespace j10

void typeids() {
	//stack instances of derived classes
	j10::derv1 d1;
	j10::derv2 d2;

	//make base class pointers point to derived
	j10::base1* b1ptr = &d1;
	j10::base2* b2ptr = &d2;

	cout << typeid(*b1ptr).name() << endl;	//prints base, not derived
	cout << typeid(*b2ptr).name() << endl;	//prints polymorphically

	//how to safe the type info
	const type_info& info = typeid(b2ptr);

	//using typeid
	if (typeid(*b2ptr) == typeid(j10::derv2)) {
		cout << "type is of the derived" << endl;
	}
	else {
		cout << "type is not of the derived" << endl;
	}
}

//typeid essentially reports what the pointer believes it points to, you need to make it virtual if you want it ot use a derived class.

//self test

//what will a non-polymorphic derefernced pointer return from the typeid.name() function?	<will return a type of hte pointer type>
//
