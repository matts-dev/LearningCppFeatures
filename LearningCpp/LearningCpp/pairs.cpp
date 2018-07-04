// pairs
//Matt Stone 6/12/2015

#include<iostream>
#include<utility>
using namespace std;

void pairs(void){
	pair<int, string> numToStr = { 1, "one" };
	//Notice, you use fields (rather than methods) to access elements of the pair
	cout << numToStr.first << " is associated with \"" << numToStr.second.c_str() << "\"" << endl;

}

//make a pair that can hold a string and a double
//what must you include for pair?
