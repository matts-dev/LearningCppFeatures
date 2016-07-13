//printf, fprintf, snprintf
//Matt Stone 7/13/16

#include<cstdio>
using namespace std;

void printfs() {
	int x = 5;
	long int lg = 10;
	const char* str = "string";
	char buffer[128] = "BUFFER - this text should be overwritten by snprintf";

	//prints to stdout
	printf("int: %d, long: %ld, string: %s\n", x, lg, str);

	//prints to a file handler (just sending it to stdout in this case)
	fprintf(stdout,"int: %d, long: %ld, string: %s\n", x, lg, str);	

	//
	snprintf(buffer, 128, "int: %d, long: %ld, string: %s\n", x, lg, str);
	puts(buffer);

}