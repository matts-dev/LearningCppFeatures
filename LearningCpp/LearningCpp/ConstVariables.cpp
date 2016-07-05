void constVar(void){
	//This variable can be modified
	int x = 0;
	x = 10;

	//This variable cannot be modified
	const int y = 10;
	
	//lvalue represents the left hand value; ie name
	//rvalue represents right hand value; ie the literal

	//Pointers
	int a1 = 1;
	int a2 = 2;


	int* ptr = &a1;								//int pointer
	const int* ptrToConst = &a1;				//const int pointer
	int * const constPtr = &a1;					//int pointer that is constant (int - const pointer)
	const int * const constPtrToConst = &a1;	//const int pointer that is constant (const int - const pointer)

	//Normal pointer
	*ptr = -1;
	ptr = &a2;

	/*pointing to constant (may or may not actually be constant)*/
	//*ptrToConst = 4;	//pointed value cannot be change (atleast, using the pointer)
	ptrToConst = &a2;

	/*constant pointer to normal reference*/
	*constPtr = 4;
	//constPtr = &b1;

	/*constant pointer to constant*/
	//*constPtrToConst = 4
	//constPtrToConst = &a2;



}

