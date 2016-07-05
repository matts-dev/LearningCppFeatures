//functors
//matt stone

#include<iostream>

using namespace std;

class functor{
	int multby;
public:
	functor(int x = 1) : multby(x){}
	int operator () (const int x) const { return multby*x; }
};

void functors(){
	functor multby10(10);
	cout << multby10(10) << endl;	//use paranthesis overload to make this appear as a function

	functor multby4(4);
	cout << multby4(10) << endl;
}

//self test
//functors overload the parenthesis operators to make objects appear as functions, this can keep state information 