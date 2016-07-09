//https://www.youtube.com/watch?v=wcKXGvi1JRk&list=PLRwVmtr-pp05motkiTlDIuU5ZfoRr-kWC
//reinterpret cast
//Matt stone 7/9/16

#include<iostream>
using namespace std;

class basicj9 {
public:
	int zeroth = 123;
	int first = 10;
	char second = 'a';
	bool third = false;
	//virtual void speak() { cout << "hi" << endl; } // will be a pointer in first 4 bytes
};

void reinterpretcasts() {
	basicj9 test;

	basicj9* classPtr = &test;
	int* intPtr = reinterpret_cast<int*>(classPtr);

	//show that the pointers point to the same address 
	cout << "class ptr adr      " << classPtr << endl;
	cout << "casted int ptr adr " << intPtr << endl << endl;

	//use int pointer to access the public fields
	cout << "first 4 bytes are: " << *intPtr << endl;
	cout << "second 4 bytes are: " << *(++intPtr) << endl;

	cout << "third 4 bytes are: " << *(++intPtr) << " but, the next field is a char so 3 bytes too many" << endl << endl;

	//change to char pointer for the next field
	char* charPtr = reinterpret_cast<char*>(intPtr);	//memory start location is correct, int pointer just takes up 4 bytes, we only need 1
	cout << "third field (9th byte): " << *charPtr << endl;

	//change char pointer to bool pointer
	bool* boolPtr = reinterpret_cast<bool*>(charPtr);
	boolPtr++;
	cout << "bool pointer points to : " << ((*boolPtr) == 0 ? "false" : "true" ) << endl;

}



