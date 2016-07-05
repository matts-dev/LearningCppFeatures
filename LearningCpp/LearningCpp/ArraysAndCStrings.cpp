//Matt Stone
#include<iostream>
using std::cout;
using std::endl;

void arrays(void){
	int a[4] = { 3, 2, 1, 0 };
	int* prt = a;

	// C++ can use C style conditions
	for (int i = 0; a[i]; ++i)
		// Doesn't print 0 because 0 = false
		// False condition stops 
		cout << a[i] << endl;

	//You can initialize like this [it is an int]
	int c1[5] = { 's', 't', 'r', '1', 0 };

	for (int i = 0; c1[i]; ++i){
		//notice the array was declared as int
		cout << (char)c1[i] << " = " << c1[i] << endl;
		// chars are really integers (short)
		// this is inefficenit because int reserves more bytes memory than necessary
	}
	cout << "int  size: " << sizeof(int) << " bytes" << endl;
	cout << "char size: " << sizeof(char) << " bytes" << endl;


	//be sure to leave room for a 0 to terminate
	char c2[5] = "str2";

	//again, loop condition waits for 0 (false)
	for (int i = 0; c2[i]; ++i){
		cout << c2[i];
	}

	//This does not use terminating 0, internal saves array size
	cout << "For each loop" << endl;
	for (char c : c2){
		cout << c << endl;;
	}
	cout << "notice space where terminating 0 was placed" << endl;

}

