//Structures
//Matt Stone 6/16/2016
#include<cstdio>

using namespace std;

struct A{
	//members default to public
	int suba = 0;
	int subb = 0;
	int subc = 0; 
};

struct B{
	int sa;
	int sb;
	int sc;
};	//structs need semi colons also

struct pub{
	int publica;
	int publicb;
};

class priv{
	int priva;
	int privb;
};

class pubClass{
public:
	int puba;
	int pubb;
};

struct complex{
	void maths(){
		printf("4\n");
	}
private:
	void maths2(){
		printf("5\n");
	}
};

typedef struct {	//you may, or may not leave out structure identifier because of the way typedef works
	int a;
} struct_t;

void structs(void){

	//if structure doesn't have initialized values, you can use this notation
	B a = { 1, 2, 3 };
	printf("%i, %i, %i \n", a.sa, a.sb, a.sc);

	//This structure initialized to 0 in definition, therefore  {} initializtion doesn't work
	A a2;
	a2.suba = 1;
	a2.subb = 2;
	a2.subc = 3;
	//A a2 = { 1, 2, 3 };	//can only be done in iniitailziation, if there isn't defaults
	printf("%i, %i, %i \n", a2.suba, a2.subb, a2.subc);


	struct_t test = { 99 };
	struct_t* ptr = &test;
	printf("typedef: %i \n", test.a);
	printf("pointers use -> %i \n", ptr->a);

	pub pub = { 1, 1 };			//structure; =s can be left out
	//priv priv = { 1, 1 };		// classes default to private
	pubClass pubC = { 1, 1 };	//you can use initializers like this with classes 

	//structures can use methods too; THIS IS NOT IN C!!!
	complex struc;
	struc.maths();		//prints out 4
	//struc.maths2();	//private structure variables
	
}

//self test
//Structures - write a basic structure containing integers
//set the values of an non-default initialized structure
//set the values of a default initalized structure
//create a structure that contains methods
//create a typedef of a structure
//note: structures in c++ do NOT need keyword struct before their declaration (as they do in C [avoided w/ typedef])