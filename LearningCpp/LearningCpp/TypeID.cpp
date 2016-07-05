//typeid operator (and mentioning of dynamic cast)
//Matt Stone 7/4/16

#include<iostream>
#include<typeinfo>	//must include for typeid

using namespace std;

void typeidex(){
	int x = 0;
	int y = 0;
	long z = 0;

	//typeid finds the the concrete classes type, it doesn't find superclasses.
	if (typeid(z) == typeid(y))
		cout << "z has same type as y" << endl;
	//note, type ID is checked at runtime
	if (typeid(z) == typeid(x))
		cout << "z has ame type as x" << endl;

	if (typeid(y) == typeid(x))
		cout << "y has same type as x" << endl;


	//this can be useful to determine a polymorphic pointer's type, but dynamic cast is better as it will check for any sublcasses
	//dynamic cast and typeid video: https://www.youtube.com/watch?v=QrDe8CK0x8U
}