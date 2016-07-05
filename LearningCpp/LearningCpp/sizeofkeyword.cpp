//sizeof operator and sizeof function
//Matt stone 7/4/16

#include<iostream>
#include<cstdio>

using namespace std;

void sizofop(){
	int x = 0;
	cout << "sizeof operator doesn't require parenthesis" <<  sizeof x << endl;
	cout << "sizeof() function on types requires parenthsis" << sizeof(int) << endl << endl;

	//you can include the parenthesis on variables, but it is redundant
	cout << "redunant parenthesis: sizeof(x) " << sizeof(x) << endl;
}