//typedef
//Matt Stone 7/3/16

#include<cstdio>
using namespace std;

typedef char byte_t;
typedef struct twobytes{ char bytes[2]; } word_t;			//16bit word
//typedef char wordBad[2];		//bad to typedef arrays because the user will not see

void typedefs(){
	printf("size of byte typedef: %ld\n", sizeof(byte_t));
	printf("size of word typedef: %ld\n", sizeof(word_t));
}