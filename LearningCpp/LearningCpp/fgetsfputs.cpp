//fputs and fgets
//Matt Stone 7/13/16

#include<cstdio>
using namespace std;

void fputsfgets() {
	fputs("enter a string to echo\n", stdout);
	fflush(stdout);	//not needed on this system, but on some systems fputs will not flush buffer.

	char buf[128];
	fgets(buf, 128, stdin);

	fputs(buf, stdout);
	fflush(stdout);
}