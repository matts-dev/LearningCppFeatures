//int data type
//Matt stone 6/29/16

#include<cstdio>
#include<cstdint>

using namespace std;

void inttype(){
	//The amount of bytes for int is not guaranteed to be the same across platforms
	printf("Size of char is: ----------h %ld bits\n", (8 * sizeof(char)));
	//int is the default type, you may omit putting it behind long or short
	printf("Size of short is: --------- %ld bits\n", (8 * sizeof(short)));
	printf("Size of int is: ----------- %ld bits\n", (8 * sizeof(int)));
	printf("Size of long int is: ------ %ld bits\n", (8 * sizeof(long int)));
	printf("Size of long long int is:-- %ld bits\n", (8 * sizeof(long long)));

	printf("\n\nUsing c standrard int:\n");
	printf("Size of int8_t is:  %ld bits\n", (8 * sizeof(int8_t)));
	printf("Size of int16_t is: %ld bits\n", (8 * sizeof(int16_t)));
	printf("Size of int32_t is: %ld bits\n", (8 * sizeof(int32_t)));
	printf("Size of int64_t is: %ld bits\n", (8 * sizeof(int64_t)));

	printf("\n\nLiteral values; different ways of entering provides different values:\n");
	printf("x = 42; this is a decimal integer: %ld\n", 42);
	printf("x = 42L; this is a long integer: %ld\n", 42L);
	printf("x = 42LL; this is a long integer: %lld\n", 42LL);
	printf("x = 42U; this is an unsigned integer: %ld\n", 42U);
	printf("x = 42LU; this is an unsigned long integer: %ld\n", 42LU);
	printf("x = 0x42; this is a hex number: %ld\n", 0x42);
	printf("x = 042; this is a oct number: %ld\n", 042);
	printf("0b0100101 doesn't work on msvs studio yet (c++14)\n");

	//float
	printf("\n\nYou can enter scientific notation for floats. 623E-4%f", 623E-4);
}