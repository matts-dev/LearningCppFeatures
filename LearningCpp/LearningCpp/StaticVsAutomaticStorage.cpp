//Static and automatic storage
//Matt stone 6/19/16

#include<iostream>
#include<string>

using namespace std;

void staticAndAuto();
const string& returnStaticVar();

void storages(void){
	staticAndAuto();
	staticAndAuto();
	staticAndAuto();
	staticAndAuto();

	const string& ret = returnStaticVar(); //must use const

	cout << returnStaticVar() << endl;
}

void staticAndAuto(){
	//static storage - this variable persists for lifetime of program 
	static int x = 0; //static variables only initialize once, so this 0 is assigned only once

	//this is automatic storage
	int y = 0; //resets to zero every time it is called.

	x += 3;
	y += 3;
	cout << "x: " << x << " y: " << y << endl;
}

//since return value is const, the str variable doesn't need const qualifier; 
const string& returnStaticVar(){
	// static variables
	static string str = "returning references to static vars save space"; // doesn't have to be const
	return str;
}



//self test: automatic vs static storage

//write a method with static and automatic storage
//does the initialization of the static variable affect value each time function called?		-no, does not influence value
//		is it okay to assign it to 0?															-yes
//Benefits of returning a reference to static storage space variable?
//	-doesn't require much runtime stack space (since it is only returning an address)
//	-returning it as const ensures the variable is safe


