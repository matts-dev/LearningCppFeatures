#include <stdio.h>

void referenceParameter(int& ref);
int& returnsRef(int& ref);
int& returnStaticRef();
int* returnStaticPtr();

/*  README
*	This file is from my previous looking at c++. That is why it doesn't follow my new convention.
*
*
*
*/
int refAndPtrs(void){
	//Some integers to play with.
	int x = 10;
	int y = 20;
	printf("x is %d and y is %d\n", x, y);
	puts("");

	//Declaring a reference variable; 
	//I read as int-ref a; must initialize because references are **immutable**
	int& changeableReference = x;	/*notice the assignment does not use address opreater, though it is taking an address*/
	int* changeablePointer = &x;
	//Declaring a constant reference;
	//this prevents changing what it is referencing to value
	//I read as const int ref (or const int pointer) <note: to make a constant address pointer (i.e. reference) you say "int pointer constant"
	const int& notChangeableRef = x;
	const int* notChangeablePtr = &x;

	/* You cannot change a reference's target (address)*/
	puts("Attempting to change xRef's address to variable y's address<failed - not a ptr>");
	changeableReference = y; /*This changes x's value to y's value. */
	changeablePointer = &y;	/* The pointer can now reference (point) to something else. this is not how references work*/
	printf("x is %d and y is %d\n", x, y);
	puts("");

	/* Using a reference is just like using a normal variable */
	puts("Assinging xRef = 2");
	changeableReference = 2;
	//notChangeableRef = 10;		/*cannot be changed; use this when all you want to do is read from ref*/
	printf("x is %d and y is %d\n", x, y);
	puts("");
	
	/* You can implicitly make(pass) references to functions; just make the function with reference parameter*/
	puts("Made implicit reference - passing VAR-arg into a REF-parameter");
	referenceParameter(x);
	printf("x is %d and y is %d\n", x, y);
	puts("");

	puts("Now passing REF-arg into REF-parameter");
	referenceParameter(changeableReference);
	printf("x is %d and y is %d\n", x, y);
	puts("");




	/* returning a reference will automatically convert a normal-type to reference*/
	y = returnsRef(x);
	int& newRef = returnsRef(x);
	newRef = 1;
	puts("Returned a reference from a function");
	puts("Then used reference to assign y, and initilize a newRef");
	printf("x is %d and y is %d\n", x, y);
	puts("");

	
	/* you can return a reference, which can be used for lvalues (lefthand values)*/
	puts("static variables can be change via ref (or pointers)");
	printf("Static Function Variable: %d\n", returnStaticRef());
	returnStaticRef() = 10;
	printf("Static Function Variable: %d\n", returnStaticRef());
	int& staticAccessor = returnStaticRef();
	staticAccessor = 999;
	printf("Static Function Variable: %d\n", returnStaticRef());
	puts("");






	/* below to give a reminder on how to do this as a pointer*/
	puts("The same can be down by returning pointers, see code for reminder");
	int* ptr = returnStaticPtr();
	*ptr = *ptr << 2;
	printf("static variable init to 1, changed via ptr to: %d\n", *(returnStaticPtr()));
	puts("");

	return 0;
}

void referenceParameter(int& ref){
	ref <<= 1;
}

int& returnsRef(int& ref){
	//ref >> 1;
	return ref;		//You could return a normal int here, see next method <returnStaticRef>
}

int& returnStaticRef(){
	static int livesThroughoutFunctCall = 5;
	return livesThroughoutFunctCall; //this is turned into a reference. 
}

int* returnStaticPtr(){
	static int lives = 1; //this is only initialized once. 
	return &lives;
}