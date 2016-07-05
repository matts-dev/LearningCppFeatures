//Structures and bitfields
//Matt Stone 7/1/16
#include<cstdio>
using namespace std;

//bitfields are supposed to limit bits used for memory, but it appears not to exactly behave this way. (wil read 8 when values addup to 9)
struct values{
	bool topFlag : 1;
	bool bottomFlag : 1;
	bool yellowFlag : 1;
	bool redFlag : 1;
	unsigned int num : 4;//act like mod (2^4), max num is 15 when field is set to 4
};

void structsAndBitfields(){
	values test;
	test.topFlag = true;
	test.bottomFlag = true;
	test.yellowFlag = true;
	test.redFlag = true;
	test.num = 15;
	printf("%d\n", test.num);
	printf("sizeof struct: %ld\n", sizeof(values));
}