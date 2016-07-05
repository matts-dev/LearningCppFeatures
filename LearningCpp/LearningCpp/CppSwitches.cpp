//Matt Stone
#include<iostream>
using namespace std;
void switches(void){
	//C++ requries constant variables (or literals) in switches
	const int one = 1; //C must use literals, no const variabes
	const int two = 2; 
	const int three = 3;
	int four = 4;

	//Varriable to use
	int x = 3;

	//constants prevent changes in switch behavior.
	switch (x){
		case one:
			cout << "one" << endl;
			break;
		case two:
			cout << "two" << endl;
			break;
		case three:
			cout << "three" << endl;
			break;
		//case four:			//non constant
		//	cout << "four" << endl;
		//	break;
		case 4:					//using literal value
			cout << "four " << endl;
			break;
		default:
			cout << "None of the above" << endl; 
	}





}