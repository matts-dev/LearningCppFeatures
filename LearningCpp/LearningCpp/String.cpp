//String Matt Stone
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void strings(void){
	//String can be initialized this way
	string str1 = "abcdefghijklmnopqrstuvwxyz";
	string str2 = "check this memory location when assignment happens";
	string* ptr = &str2;

	//Strings work similar to vectors; internal memory management
	cout << "Before assignment: " << ptr << " size: " << sizeof(*ptr) << endl;
	//memory address of str2 stays same; 
	str2 = str1;
	cout << "After assignment:  " << ptr << " size: " << sizeof(*ptr) << endl;

	//size method 
	cout << "size: " << str1.size() << endl;
	//length is an alias for size
	cout << "length: " << str1.length() << endl;

	//Concatenation
	string str3 = str1 + " " + str2;
	string str4 = "abcccccccc";
	cout << "str3: " << str3 << endl;
	cout << "str4: " << str4 << "\n" << endl;

	//Comparison operators
	cout << "str1 == str2? :" << (str1 == str2) << endl;	//true
	cout << "str1 == str3? :" << (str1 == str3) << endl;	//false
	cout << "str3 > str4? :" << (str3 > str4) << endl;		//true	(greater means later)
	cout << "str3 < str4? :" << (str3 < str4) << endl;		//false
	cout << "str4 <= str4 :" << (str4 <= str4) << endl;		//true

	string numberStr = "0123456789";
	cout << "\nstring: " << numberStr << endl;


	//Strings are MUTABLE in C++
	numberStr.insert(4, "_INSERTED_");	//dangerous, check to know 4 is valid index
	cout << '\n' << "inserted @ 4 using index & string:  " << numberStr << endl; // 0123_INSERTED_456789

	//Strings have iterators (with characters)
	numberStr.insert(numberStr.begin() + 15, 'X'); //0123_INSERTED_4X56789
	cout << "inserted @ 2 using iterator & char: " << numberStr << endl;

	//Erasing
	numberStr.erase(4, 10);		//01234x56789
	cout << '\n' << "erase at 4, n = 10: " << numberStr << endl;

	//removes everything after index
	numberStr.erase(5);			//01234
	cout << "erase at 5:         " << numberStr << endl;

	//This assignment isnt limited to initizalizations
	numberStr = "0123456789";
	cout << '\n' << "reset str to: " << numberStr << endl;

	//Replace x amount of characters with a different # of chars
	int numCharsToReplace = 3;
	numberStr.replace(4, numCharsToReplace, "_REPLACED_");
	cout << numberStr << '\n' << endl;

	//Get a substring @ index for a number of characters 
	string substr = numberStr.substr(2, 4);
	cout << "substring @ 2, n = 4: " << substr << endl;

	//Find char; returns string::npos if no character is found

	//front position find
	size_t frontPosition = numberStr.find('E');	//size_t gaurantees ability to hold index value
	//back position find
	int backPosition = numberStr.rfind('E');	//can also use int, but not gauranteed
	cout << "front \'E\': " << (unsigned)frontPosition << " back \'E\': " << backPosition << endl;

	//find can be used to find substrings!
	size_t index = numberStr.find("REP", 1); //int specifies start index
	if (index != string::npos){
		cout << "Searching front for \"REP\" index:" << index << endl;
	}
	else if (index == string::npos) {
		cout << "npos found" << endl;
	}

	//STRINGSTREAM STUFF - useful for parsing numbers from string

	//pasring integers
	string numbers = "343 233 323 535 23 3 5";
	stringstream strm(numbers);
	while (strm){
		int n = 0;
		if (strm >> n){	//may but this in while loop
			cout << n << ' ';
		}
	} cout << endl;


	//parsing doubles (and storing them into a vector)
	string doubles = "5.5 4.4 3.3 2.22222 1.1111";
	stringstream strm2;
	strm2 << doubles;	//how to load string without using constructor
	double loadDouble= 0.0;
	vector<double> dvect;
	while (strm2 >> loadDouble){
		//cout << loadDouble << ' ';
		dvect.push_back(loadDouble);
	}
	for (double d : dvect) cout << d << ' ';
	cout << endl;
	//strm.swap();
}

//self test
//initialize string using "";
//get the memory size of a string value		(sizeof)
//how is string memory handled internall? (like vectors)
//get the size of a string (not memory, but internal indeces)
//get the length of a string. is this the same thing as size()?
//concatenate two strings
//use comparison operators to test which (of two strings) comes first lexographically
//are stl strings mutalble?			<yes>
//obtain a string iterator
//use iterator to insert a char
//use iterator to erase a sequence of chars (its mutable, so it is okay)
//use iterator to erase everything after a specific index
//can the "" assignment *only* be during initialization? 		<no>
//replace range of chars within a string, with a new string
//get a substring
//what is the second argument in the substr method? <number of elements>
//find a sequence within a string
//	what does find return?		<int location>
//what is the error if char or string cannot be found?	<returns 
//find a sequence within a string, but from the end (using an easy method without iterators)
//use find from a specific index of the string 	
//Parse to integers using stringstreams
//possible ways to load a string into stringstream?
//parse doubles from a stringstream