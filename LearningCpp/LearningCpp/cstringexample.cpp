//cstring
//matt stone 6/30/16

#include<cstdio>

using namespace std;

void cstrings(){
	char cstring[] = "cstring";
	puts(cstring);
	for (unsigned int i = 0; cstring[i]; ++i)	//unsigned because string could be theoretically bigger than max sign value
	{//loop through until 0 is hit (which is end of string
		printf("#%d:%c  ",i, cstring[i]);
	} puts("");//new line

	printf("array size: %ld\n", sizeof(cstring));
	puts("\n\n");

	//concatenation at initialization
	char* cstring2 = "str1" "str2"
		"str3"
		"str4";
	puts(cstring2);
}

//Self test	
//why use a c-string?							<small, lightweight, no need for large library>
//how is a c-string ended?						<with literal int 0 value>
//initialize a cstring using array syntax
//initialize a cstring using pointer syntax
//concatenate a cstring with another at initialization
//print the size of a cstring, what is the underlying type of the typedef size_t	<long int, use this in printf>
