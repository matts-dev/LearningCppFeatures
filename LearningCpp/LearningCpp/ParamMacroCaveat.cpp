//Parameter Macro Cautions
//Matt Stone
#include <iostream>
#define MAX(a,b)(a>b?a:b)

using namespace std;

int xfer(int a){
	static int x = 0;
	x += 1;
	cout << "called " << x << "times" << endl;
	return a;
}

void macroCaveats(){
	int a = 10;
	int b = 20;
	cout << "max is: " << MAX(a, xfer(b)) << endl;	//calls xfer twice, whereas function would only call once
}

