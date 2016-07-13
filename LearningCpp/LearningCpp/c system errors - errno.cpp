// c errors
// Matt Stone 7/13/16

#include<cstdio>
#include<cerrno>
#include<cstring>	//for strerror
using namespace std;

//errno is the number of the last error
void errnos() {
	//so far, no errors are set 
	printf("errno - last error number is: %d\n", errno);

	//erase a file that does not exist
	remove("thisfiledoesnotexist.txt");

	//error 2 reports failure in removing the file
	printf("errno - last error number is: %d\n", errno);	

	//print error with an error message
	perror("user message before error message");

	//you can get error string using strerror (within <cstring>)
	printf("%s", strerror(errno));

}