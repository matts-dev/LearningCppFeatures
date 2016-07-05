// https://www.youtube.com/watch?v=VzM1GWUl8eI
// stringstreams Matt Stone 6/12/16
// this is mostly my research on parsing numbers from strings
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;


void stringstreams(void){
	//STRINGSTREAM
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
	double loadDouble = 0.0;
	vector<double> dvect;
	while (strm2 >> loadDouble){
		//cout << loadDouble << ' ';
		dvect.push_back(loadDouble);
	}
	for (double d : dvect) cout << d << ' ';
	cout << endl;

	//parsing a complicated string (such as comma delimiters) (another way would be to make substrings)
	string complicated = "5, 6, 7, 8";
	string holder;
	int value = 0;
	stringstream sourcestream(complicated);
	stringstream converter;
	vector<int> vect;
	while (getline(sourcestream, holder, ',')){	//getline needs a stream, not string
		converter << holder;
		converter >> value;
		converter.clear();
		vect.push_back(value);
	}
	for (int i : vect) cout << i << ' ';
	cout << endl;


	//BREAKING THE STREAM attempting to push a value from streamstream that isn't an integer
	string testStr = "1 2 3b 4";
	stringstream streamTest;
	streamTest << testStr;
	for (int i = 0; streamTest >> i;){
		cout << i << ' ';
	}
	cout << endl;
	streamTest.clear();	//reset

	streamTest.seekg(ios::beg);//start the streams pointer to beginning  (.seekg(0, ios::beg) too

	streamTest << testStr.substr(0, 3);
	for (int i = 0; streamTest >> i;){
		cout << i << ' ';
	}
	cout << endl;
}

//self test (stringstream)
//initialize a stringstream using the constructor (set it to numbers with spaces, to be used later)
//parse integers using a while loop from string (print them)
//parse doubels into a vector, then print content of the vector
//parsee a complicated string : "5, 6, 7, 8" into a vector		
//				hint: use getline (uses various streams), a holder string, and a converter stringstream
//what happens if you break a stringstream?	
//how can you break a stringstream? <try to parse non-int into an int>
//how can you clear the error flag?
//how can you restart the stringstream?
//clear a strings error, restart it, and print up to the point of the error
//if you clear an error, can you clear the error and continue? 		<no, it appears clear resets internal buffer>
