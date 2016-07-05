//Files
//Matt Stone 6/9/2016
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


void ioFiles(void){
	static const char* fileName = "testFile.txt";
	static const char* textString = "Testing a file!";

	//BASIC FILES - better options in following functions
	cout << "write to file\n" << endl;
	ofstream outFile(fileName);
	if (outFile.is_open()){
		outFile << "This should overwrite the contents of the file by default" << endl;
		outFile << "outfile is on trunct mode not append" << endl;
		outFile << "this is the third line" << endl;
	}
	outFile.close();

	ifstream inFile(fileName);
	if (inFile.is_open()){
		char buff[10000];
		while (inFile.good()){
			inFile.getline(buff, sizeof(buff));
			cout << buff << endl;
		}
	}
}

void ioFilesBetter(void){
	//Creat the file name
	static const char* filename = "test.txt";

	//create outfile stream object
	ofstream oFile;

	//open a file and truncate it (erase) - trunct creates new file
	oFile.open(filename, ios::trunc);

	if (oFile.is_open()){
		for (int i = 0; i < 10; ++i){
			//WRITE to the file
			oFile << "filling file with lines" << endl;
		}
		//RESETING FILE

		//clear errors (EOF, etc.)
		oFile.clear();

		//start over
		oFile.seekp(0, ios::beg);

		//writing something to the beginning 
		oFile << "attemp to insert at beginning" << endl;

		//CLOSE THE FILE
		oFile.close();
	}
	else {
		cout << "error in opening file" << endl;
	}

	//OPENING A FILE
	ifstream iFile;
	iFile.open(filename);
	if (iFile.is_open()){
		bool readAgain = false;
		do{
			string str;
			while (iFile.good()){
				getline(iFile, str);			//using std::getline allows use of strings
				cout << str << endl;			//using strings prevents array out of bounds checking :)
				//char buffer[128];
				//iFile.getline(buffer, sizeof(buffer)); //another way of doing it, may result in error
				//cout << buffer << endl;
			}
			cout << "Read again? yes(1), no(0)" << endl;
			cin >> readAgain;	//will put number (bools act like conditional statements in c; 0 = false)
			if (readAgain){
				//clear EOF setting
				iFile.clear();
				//start over
				iFile.seekg(0, ios::beg);
			}
		} while (readAgain);
	}
	else {
		cout << "error in opening file" << endl;
	}
}

//STOP QUIZ AFTER THIS POINT


void ioFstream(void){
	//fstream objects have modes: -in, -out, -app(append), -binary
	//fstream other modes: -trunc (truncation, ie delete all contents), -ate(at end)
	fstream file;	//allows reading OR writing

	//open a file (if one doesn't exist, add trunc to create a new one)
	file.open("test.txt", ios::in | ios::out | ios::trunc);	//file is on default modes: in and out, but specified anyways

	if (!file.is_open()){
		cout << "failed to open file" << endl;
	}

	file << "hello my friend" << endl;
	file.clear();	//clear errors (EOF etc.) no errors in this example.

	//set the file input seq position
	file.seekg(0, ios::beg); //0 is offset; offset is index of input stream (of characters)
	//offset of 3 yeilds: "lo my friends"; ie it lost hel (position 0, 1, and 2)

	char buffer[128];
	file.getline(buffer, sizeof(buffer)); //unsafe, check for errors with if
	cout << buffer << endl;

	file.close();
}

void ioOfstream(void){
	ofstream file("test.txt");
	if (!file.is_open()){
		cout << "file failed to open" << endl;
	}
	//this will erase the current contents of the file
	file << "hi, this is a test output" << endl;
	file.close();
}

void ioIfstream(void){
	ifstream file;
	file.open("test.txt");
	if (!file.is_open()){
		cout << "error opening file" << endl;
	}
	else {
		string str;
		while (file.good()){
			getline(file, str);  	//must #include<string>
			cout << str << endl;
		}
		file.clear();
		file.seekg(0, ios::beg);	//resets to the beginning
		file.close();
	}
}