//renaming and deleting cfiles
//Matt Stone 7/13/15

#include<cstdio>
using namespace std;

void nameanddelete() {
	const char* name1 = "testfilename1.txt";
	const char* name2 = "testfilename2.txt";
	FILE* fp = fopen(name1, "w");

	char buffer[124] = "writing to file 1";
	fwrite(buffer, 124, 1, fp);

	//close the file before attempting to rename
	fclose(fp);
	
	rename(name1, name2);
	//printf("renamed\n");
}