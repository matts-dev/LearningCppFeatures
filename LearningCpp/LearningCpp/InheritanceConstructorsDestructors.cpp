//Analyzing constructors and destructor behavior using inheritance
//Matt Stone 7/6/16

#include <iostream>
using namespace std;

class BaseClass {
public:
	BaseClass() { cout << "Base Constructor" << endl; }
	~BaseClass() { cout << "Base dtor" << endl; }
};

class Derv1 : public BaseClass {
public:
	Derv1() : BaseClass() { cout << "Middle Class Constructor" << endl; }	//showing constructor calls for practice
	~Derv1() { cout << "Middle Class dtor" << endl; }
};

class Derv2 : public Derv1 {
public:
	Derv2() : Derv1() { cout << "Bottom Class Constructor" << endl; }	
	~Derv2() { cout << "Bottom Class dtor" << endl; }
};

void inhertConstrDtor() {
	cout << "creating a 3 time inherited object to analyze constructor order, and dtor order" << endl << endl;

	Derv2 test;
	cout << endl;	//newline
}

//self test
//What constructor is called first in the inheritance hierarchy?			<The base constructor>
//What is the order of the constructors called in an inheritance hierarchy	<Starts at base, and calls constructors towards bottom most derived>
//What destructor is called first?											<the most derved class is called first>
//What order are destructors called?		<starting at the derived, moving towards base>
//		This makes sense because additional resources should be cleared before the base resources
