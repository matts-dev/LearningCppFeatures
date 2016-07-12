//binary file writing
//Matt Stone 7/12/16

#include<cstdio>
#include"DummyClass.h"
#include<string>
using namespace std;


void binaryfiles() {
	// -------------------------------- CREATING OBJECTS --------------------------------
	DummyClass obj(false);
	string name = "Matt";
	obj.setName(name);

	// -------------------------------- WRITING FILE --------------------------------
	const char* filename = "testbinaryfile.file";
	FILE* fp;
	fp = fopen(filename, "wb");	//wb means write in binary mode
	fwrite(&obj, sizeof(obj), 1, fp);		//3rd argument is number of elements
	fclose(fp);

	// -------------------------------- READING FILE --------------------------------
	fp = fopen(filename, "rb");
	DummyClass loadObj(false);
	fread(&loadObj, sizeof(DummyClass), 1, fp);
	fclose(fp);

	cout << loadObj.getName() << endl;
}