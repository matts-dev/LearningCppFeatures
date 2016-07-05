//Refernce data type
//Matt Stone 7/1/16

#include<cstdio>
using namespace std;

//use constant references to prevent side effets on original value
const int& funct(const int& ref){
	static int y = ref;	//const ref shows programmer that this value will not change ref, 
	return ++y;	//using y instead, allows us to use the ref's value. 
	//We might have passed by value, but this provides benefit for large classes 
}

void refs(){
	int value = 1;
	printf("value: %d\n", value);
	printf("value: %d\n", funct(value));
	printf("value: %d\n", value);
}

//self test
// references cannot be null, they cannot be pointed to, etc. 