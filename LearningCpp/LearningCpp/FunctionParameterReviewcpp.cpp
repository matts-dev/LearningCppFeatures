//Function parameter options review
//Matt Stone 6/18/16

#include<iostream>
#include<string>

using namespace std;

void printwxyz(const int& w, const int& x, const int& y, const int& z);
void reset(int& w, int& x, int& y, int& z);
void paramTest(int w, const int, int& y, int* z);
void refTest(int& w, const int& x, int& const y, const int& const z);
void ptrTest(int* w, const int* x, int* const y, const int* const z);

void parameters(void){
	int w = 1;
	int x = 2;
	int y = 3;
	int z = 4;

	printwxyz(w, x, y, z);
	cout << "attempting to change variables with parameters: (int, const int, int&, int*)" << endl;
	paramTest(w, x, y, &z);
	printwxyz(w, x, y, z);
	reset(w, x, y, z);

	//Pass large values to functions using constant references, creating large copies on stack is dangerous
	cout << "attempting to change vars with params: (int& w, const int& x, int& const y, const int& const z)" << endl;
	printwxyz(w, x, y, z);
	refTest(w, x, y, z);
	printwxyz(w, x, y, z);
	
	//prefer references to pointers, references a more limited, but that limitations adds safety. 
	//heres an example of using pointers anyways
	cout << "attempting to change vars with params: (int* w, const int* x, int* const y, const int* const z)" << endl;
	printwxyz(w, x, y, z);
	ptrTest(&w, &x, &y, &z);
	printwxyz(w, x, y, z);
}

void paramTest(int w, const int, int& y, int* z){
	w = 11;
	//x	= 22;		constant
	y = 33;
	*z = 44;	
}

void refTest(int& w, const int& x, int& const y, const int& const z){
	//parameters: y and z are redundant. References already are immutable
	w = 11;
	//x = 22;	//though ref value is mutable, what it poitns to is[CONSTANT INT] - therefore cannot change
	y = 33;		//ref is[const], but what it points to isnt.
	//z = 44;		//ref is [const] and what it points to is const.
}

void ptrTest(int* w, const int* x, int* const y, const int* const z){
	*w = 11;	//regular pointer
	//*x = 22;	//points to const integer, cannot change constant integer's val, can change address(adr)
	*y = 33;	//constant pointer (cannot change the value's adr it points to), but can change value
	//*z = 44;	//points to constant integer, it is also a constant pointer (cant change either)
}

void printwxyz(const int& w, const int& x, const int& y, const int& z){
	cout << "w: " << w;
	cout << " x: " << x;
	cout << " y: " << y;
	cout << " z: " << z;
	cout << endl;
}

void reset(int& w, int& x, int& y, int& z){
	w = 1;
	x = 2;
	y = 3;
	z = 4;
	cout << "reset variables to 1,2,3,4" << endl << endl;
}