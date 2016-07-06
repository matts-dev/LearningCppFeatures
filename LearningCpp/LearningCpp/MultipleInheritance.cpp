//Multiple Inheritance
//Matt Stone 7/6/16

#include<iostream>
using namespace std;

namespace J6 {

	class A {
	public:
		A() { cout << "A construct" << endl; }
		~A() { cout << "A dtor" << endl; }
	};

	class B {
	public:
		B() { cout << "B construct" << endl; }
		~B() { cout << "B dtor" << endl; }
	};

	class C {
	public:
		C() { cout << "C construct" << endl; }
		~C() { cout << "C dtor" << endl; }
	};

	class Derived : public B, public A, private C {			//constructors called in order
	public:
		Derived() { cout << "Derived construct" << endl; }
		Derived(int x) { cout << "Derived construct" << endl; }
		~Derived() { cout << "Derived dtor" << endl; }
	};


}; //end namespace


void multInhert() {
	J6::Derived derv;
}