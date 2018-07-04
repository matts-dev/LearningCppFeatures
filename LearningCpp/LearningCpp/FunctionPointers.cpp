//Function Pointers
//Matt Stone 6/19/2016

#include<iostream>
#include<string>
#include"DummyClass.h"

using namespace std;

//functions to make pointers to
void talk(){ cout << "hi" << endl; }
void talk2(){ cout << "hey" << endl; }
void talk3(){ cout << "hello" << endl; }
void talk4(){ cout << "howdy" << endl; }
int returnInt(){ return 1; }
int returnInt(int x, double y, float z){ return (int)(x*y*z); }
const string returnStrConst(){ return "Const STR"; }
int returnInt(int x){ return x; }
double returnDouble(){ return 1.0; }
double returnThis(double x){ return x; }

//function pointer as parameter
void printFromFunctPtr(double(*fptr)(double), double usethis);
void PrintFromInstanceWithfptr(DummyClass& obj, int(DummyClass::*fptr)(int), int echoThis);

void funcptrs(){
	// ------------------------------------ Regular Functions ------------------------------------
	cout << "--------------------- Normal(C) Function Ptrs ---------------------" << endl;

	//Explicit way of doing function pointers (easier to read)
	void(*voidptr)() = &talk;
	(*voidptr)();

	//More implicit way of doing function pointers
	void(*voitptr2)() = talk;		//no address operator show	[ALSO no paranethesis]
	voidptr();					//no dereference shown

	//function pointer to int with no arguments (explicit style)
	int(*intret)() = &returnInt;
	cout << "int return funct ptr: " << (*intret)() << endl << endl;

	//function point to ret: const string, no arguments
	const string(*cifptr)() = returnStrConst;
	cout << "const int from fptr: " << (*cifptr)() << endl;

	//function pointer to overloaded [int return] with [int] parameter (explicit style)
	int(*intret2)(int) = &returnInt;
	cout << "using function pointer on overload: " << (*intret2)(5) << endl << endl;

	//function pointer to double return (implicit)
	double(*retdubptr)() = returnDouble;
	cout << "function pointer that returns double: " << retdubptr() << endl;

	double(*fptr)(double) = returnThis; //	double(*fptr)(double x) also works, but no need for 'x' identifier
	cout << "using funct ptr with dub arg " << returnThis(76.7) << endl;

	int(*multiparamptr)(int, double, float) = &returnInt;
	cout << "multiparameter fptr: " << (*multiparamptr)(5, 5.0, 5.0) << endl << endl;

	//using a function that takes a functions pointer as an argument
	printFromFunctPtr(fptr, 5.5);
	printFromFunctPtr(&returnThis, 5.5);
	printFromFunctPtr(returnThis, 5.5);

	//array of function pointers
	void(*arrayptr[])() = { &talk, &talk2, talk3, talk4 };
	void(*arrayptr2[4])();
	arrayptr2[0] = &talk;
	arrayptr2[1] = talk2;	//operator symbol is optional
	arrayptr2[2] = talk3;
	arrayptr2[3] = &talk4;
	for (int i = 0; i < 4; ++i) { (*arrayptr[i])(); }	//explicitly showing funct ptr
	for (int i = 0; i < 4; ++i) { arrayptr[i](); }		//cryptically using funct ptr

	// ---------------------------------- Classes Function Ptrs ------------------------------------
	cout << "--------------------- Classes Function Ptrs ---------------------" << endl;

	//using a function pointer to a classes member function
	DummyClass obj(false);
	void(DummyClass::*speak)() = nullptr;	//speak is NOT IN DUMMY CLASS 
	speak = &DummyClass::saySomething;
	(obj.*speak)();

	// implicit way of doing function pointers on classes doesn't seem to work (ie implicit = no & and lacking de-references)
	int(DummyClass::*fptrI)(int) = &DummyClass::echoInt;
	//need to de-reference ptrs object's member functions, not good implicit way with this.
	cout << "instance function pointer that echos int" << (obj.*fptrI)(99) << endl;

	//using array with object methods
	int(DummyClass::*fptrArray[])(int) = { &DummyClass::echoInt, fptrI };	//add method, and use another ptr
	int(DummyClass::*objfptrA[2])(int);
	objfptrA[0] = &DummyClass::echoInt;
	objfptrA[1] = fptrI;
	for (int i = 0; i < 2; ++i){ cout << "array fptrs on objs" << (obj.*fptrArray[i])(5) << endl; }
	for (int i = 0; i < 2; ++i){ cout << "2ndarray fptrs on objs" << (obj.*objfptrA[i])(5) << endl; }

	//using a function and function pointers as arguments
	PrintFromInstanceWithfptr(obj, nullptr, 1234);
	PrintFromInstanceWithfptr(obj, NULL, 1234);
	PrintFromInstanceWithfptr(obj, 0, 1234);
	PrintFromInstanceWithfptr(obj, fptrI, 4321);
	cout << endl << endl;

	//static member functions
	void(*staticPtr)() = &DummyClass::staticmethod; //first method
	(*staticPtr)(); 	//You can treat static methods in a class almost like normal function pointers

	//void(DummyClass::*staticPtr2)() = &DummyClass::staticmethod;
}

void printFromFunctPtr(double(*fptr)(double), double usethis){
	cout << "F(FPTR,ARG): " << (*fptr)(usethis) << endl;
}

void PrintFromInstanceWithfptr(DummyClass& obj, int(DummyClass::*fptr)(int), int echoThis){
	// should be known if function ptr is already pointing or not, other use if
	if (fptr != nullptr){
		cout << "F(O,FPTR,ARG): ";
		cout << (obj.*fptr)(echoThis) << endl;
		//Think about what's happening in first parenthesis, and what's happening in second. My interpreation follows
		// (go to memory location within instance's reserved memor) (pass this argument)
	}
	else {
		//make the function pointer and use it 
		fptr = &DummyClass::echoInt;
		(obj.*fptr)(echoThis);
		cout << "nullptr, had to assign ptr" << "F(O,FPTR,ARG): ";
		cout << (obj.*fptr)(echoThis) << endl;
	}
}


//create a function pointer that points to:
//use the following functions to make function pointers:

//void talk(){ cout << "hi" << endl; }
//void talk2(){ cout << "hey" << endl; }
//void talk3(){ cout << "hello" << endl; }
//void talk4(){ cout << "howdy" << endl; }
//int returnInt(){ return 1; }
//const string returnStrConst(){ return "Const STR"; }
//int returnInt(int x){ return x; }
//int returnInt(int x, double y, float z){ return (int)(x*y*z); }
//double returnDouble(){ return 1.0; }
//double returnThis(double x){ return x; }


// ret:void, void parameters
// ret:void, int ,float, double parameter
// ret: int, param: int
// ret: doub, param: doub

// create a function that accepts a function pointer as a parameter

// create a function pointer to a classes member function

// create a function pointer to a static class member function

//create an array of function pointers (similar to jump table's implementation
