//Auto Keyword
//Matt Stone 7/3/16

#include<cstdio>
#include<typeinfo>
using namespace std;

int functInt(){ return 5; }
double functDouble() { return 5.5; }

void autokeyword(){
	//auto asks the COMPILER to fill in the type
	auto x = functInt();	//will be of int type		
	auto y = functDouble();	//will be of double type
	printf("type info: %s\n", typeid(y).name());
}

//self test 
//does auto happen at compile time or run time?					<compile time>
//are auto variables strongly typed?					<yes, the still a type, it is just delgated to the compiler to figure out by the return type of a function>
