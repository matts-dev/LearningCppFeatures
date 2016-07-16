//custom deleters
//Matt Stone 7/16/16

#include<iostream>
#include<memory>
#include"verboseclasses.h"

using namespace std;
using sptrs::Base;
using sptrs::Derived;

//Deleters can be helpful in deleting an array of pointers -- ie delete[]
void deletefunc(Base* rawPtr) { cout << "function deleter" << endl; delete rawPtr; }
struct deletefunctor {
	void operator() (Base* rawPtr) { cout << "functor deleter" << endl; delete rawPtr; }
};

void customDeleters() {
	//custom deleters can be functions, functors, lambdas				I do not think these are exception safe, but I am not sure
	shared_ptr<Base> shared1(new Base, &deletefunc);//function
	shared_ptr<Base> shared2(new Base, deletefunctor());//functor 
	shared_ptr<Base> shared3(new Base, [=](Base* ptr) {cout << "lambda deleter" << endl; delete ptr; });


	//heres a note on the functor deleter
	deletefunctor explicitfunctor;	//creating the functor on the stack
	shared_ptr<Base> shared4(new Base, explicitfunctor); // will call the functor
}