//this keyword
//matt stone 6/25/2016
#include<iostream>
using namespace std;


class A625{
	int value = 0;
	A625();
public:
	A625(int value){ this->value = value; }
	void setValue(int value){ this->value = value; }
	void prtAdr(){ cout << this << endl; }
	void prtValue(){ cout << (*this).value << endl; }
};

void theThis(){
	A625 a1(10);
	//set value
	a1.setValue(20);
	//print value (internally uses the this keyword)
	a1.prtValue();
	//print address (intenrally users this keyword)s
	a1.prtAdr();
}