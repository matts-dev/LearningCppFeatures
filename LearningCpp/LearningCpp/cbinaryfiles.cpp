//binary file writing
//Matt Stone 7/12/16

#include<cstdio>
#include"DummyClass.h"
#include<string>
using namespace std;


void binaryfiles() {
	// -------------------------------- CREATING OBJECTS --------------------------------

	// C binary files are useful for POD
	struct POD {
		char* name = "DEFAULT";
	} obj;
	obj.name = "MATT";
	//DummyClass obj(false);	//while it is attractive to save an obj in a binary file, it causes weird behavior and ultimately a crash.
	//string name = "Matt";		//It appears to work (I can read the name), but the best way is to create a a save and load function within the class that usinsg istream and ostream
	//obj.setName(name);		//the ostream and istream will have non-member friend overloads within that serialize objects


	// -------------------------------- WRITING FILE --------------------------------
	const char* filename = "testbinaryfile.file";
	FILE* fp;
	fp = fopen(filename, "wb");	//wb means write in binary mode
	fwrite(&obj, sizeof(obj), 1, fp);		//3rd argument is number of elements
	fclose(fp);

	// -------------------------------- READING FILE --------------------------------
	fp = fopen(filename, "rb");
	POD loadObj;
	fread(&loadObj, sizeof(DummyClass), 1, fp);
	fclose(fp);

	// -------------------------------- USING LOADED OBJ --------------------------------
	cout << "if you do not see DEFAULT after colon, the load was successful:\n" << loadObj.name << endl << endl;


	// -------------------------------- MULTIPLE OBJS TO FILE --------------------------------
	cout << "saving two objs to a file" << endl;

	//make data
	POD objs[2];
	objs[0].name = "MATT";
	objs[1].name = "STACEY";

	//save data
	const char* fname = "twoobjs.file";
	FILE* filePointer = fopen(fname, "wb");
	for (int i = 0; i < 2; ++i) {
		fwrite(&objs[i], sizeof(POD), 1, filePointer);
	}
	fclose(filePointer);

	//load data
	filePointer = fopen(fname, "rb");
	for (int i = 0; fread(&objs[i], sizeof(POD), 1, filePointer); ) {
		//use data that was just loaded
		puts(objs[i].name);
	}
}

//self test
//save and read a structure to a binary file



//should you use binary files to save instances of objects?		
//		<no, classes should define their own load and save funtions that provide istream and ostream objects (using overloads of << and >>)
//what is the difference betwen a binary file and a text file?		binary files can be used to save values, text files may do some translations
//
