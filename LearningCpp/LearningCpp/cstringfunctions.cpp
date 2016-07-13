//c string functions
//Matt Stone 7/13/16

#include<cstdio>
#include<cstring>
using namespace std;

void cstringfuncts() {
	//create c strings
	char str1[] = { 's', 't', 'r', 'i', 'n', 'g', '1',  0 };		//can use '\0' for 0
	char str2[] = "string2";		//implicit \0
	const char* str3 = "string3";	//since this is pointer to literal value in memory, it needs to be const
	const static size_t maxbuf = 128;

	//create two buffers
	char buffer1[maxbuf];
	char buffer2[maxbuf];

	//string copy function
	strncpy(buffer1, str1, maxbuf);		//second argument is the number of elements to copy, 
	strncpy(buffer2, str2, maxbuf);
	puts(buffer1);
	puts(buffer2);

	//string concatenation		//TODO: test buffer and concat with null 0
	strncat(buffer1, " + ", sizeof(buffer1) - strnlen(buffer1, 128) - 1);	//I believe -1 reserve space for null terminating 0
	strncat(buffer1, buffer2, sizeof(buffer1) - strnlen(buffer1, sizeof(buffer1)) - 1); //refernce says null 0 will always be placed on end
	puts(buffer1);

	//string compare
	int compare = strcmp(buffer1, buffer2);
	printf("string one is \"%d\" to string two\n", compare);

	//get pointer to char
	char c = 'n';			// string "string1 + string2" has 2 ns
	char* cpfront = strchr(buffer1, c);
	char* cpback = strrchr(buffer1, c);	//serachs in reverse

	//you can get index by subtracting pointer values
	printf("First pointer index is: %d\n", cpfront - buffer1);	//pointer arthimetic using adrs
	printf("Last pointer index is: %d\n", cpback - buffer1);	//array == pointer

	//finding substrings
	char* substringPointer = strstr(buffer1, "+ str");	//note: this will include the "ing" 
	puts(substringPointer);								// after the substring "+ str"

}