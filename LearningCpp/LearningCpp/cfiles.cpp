//cfiles (not file streams)
//Matt Stone 7/12/16

#include<cstdio>
using namespace std;

void cfiles() {
	//file name
	const char* fileName = "testfile.txt";

	//file mode strings
	// w = write
	// w+ = write and read
	// r = read
	// r+ = read nad write
	// a = append to a file's end
	// a = append to a file, and read
	// b = binary mode (write values rather than text file) - used in conjunction with other mode strings
	//		 wb, rb, ab	 = write binary, read binary, append binary


	// -------------------------------- FILE WRITING --------------------------------

	//open a file for writing
	FILE* fp;
	fp = fopen(fileName, "w");		//w+ will allow writing and reading
	for (int i = 0; i < 3; ++i)
		fprintf(fp, "test line in cfiles.cpp\n");
	fclose(fp);


	// -------------------------------- FILE READING --------------------------------
	//open a file for reading
	int bufsize = 150;
	char buffer[150];

	FILE* fp2;	//could use same one, but doing this for completeness 
	fp2 = fopen(fileName, "r");		//r+ will allow read and writing
	while (fgets(buffer, bufsize, fp2)){ 
		fputs(buffer, stdout); // does not add a new line, does not flush buffer
	}

	fclose(fp2);

	// -------------------------------- Deleting file --------------------------------
	remove(fileName);		//deletes file based on cstring name
}

//save and read strings to a text file
// what are all the file mode strings?			<w, r, a, wb, rb, ab, w+, r+, a+, etc.>
//should you always close a file				<yes, whether reading or writing, close the file!>
//how can you delete a file?					<		remove(const char* filename);		>
