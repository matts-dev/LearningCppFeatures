#include <iostream>
using namespace std;

//looking through this code, you see j1 followed by j2, followed by j3, folowed by j4.
//the goto keyword will allow us to skip around in code, rather than let this execute sequentially.
//this is similar to assembly, and can be used as an intermediate step in assisting in the reverse engineering of assembly. 
//WARNING: this is considered bad practice to use in programming.
void gotoDemo() {
	int x = 1;
	x = 5;
	goto j3; //jump to the j3 label
j1:
	cout << "j1" << endl;
	goto j4;
j2:
	cout << "j2" << endl;
	x = 7;
	goto done;
j3:
	cout << "j3" << endl;
	x = 4;
	goto j1;
j4:
	cout << "j4" << endl;
	x = 6;
	goto j2;
done:
	cout << "done" << endl;
}