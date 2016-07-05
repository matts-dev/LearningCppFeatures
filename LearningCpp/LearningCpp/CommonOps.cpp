//Common operators
//Matt Stone 7/4/16

#include<iostream>
#include"IntegerW.hpp"
#include<string>
using namespace std;

//View this file not as primitive types, but as classes

void comops(){
	//Initialization 
	int x(0);					//call constructor with 0

	int y = 4;					//implicit call of copy constructor, I believe

	//Assignment operator
	x = 4;						//simply copies the literal into x

	x = x + y;					// (1)creates a temp object, (2) copies x, (3) adds y, (4) uses assignment operator with temp object to set x
	x += y;						// (1) x obj adds y to its value, (2) returns  reference of x

	cout << x << endl;
	x = x += y;				//compound operators can be chained (they return a reference)
	cout << x << endl;

	char a = 12;
	char b = 3;

	//operators
	y = x % 2;	//returns the remainder of dividing by 2
	y = x / 2;	//integer division
	b = b << 1;	//left bit shift operator
	b = b | a;	//bitwise or
	b >>= 1;	//compound bit shift (should do sign extension)
	a = b & a;	//bitwise and


	//compound operators are more efficient (they do not require as much copying as chaining other operators with teh assingment operator)
	y += x;
	x *= y;
	y /= x;
	y -= x;

	//Increment and decrement operators
	x++;	//increments x after it is returned
	++x;	//increments x before it is returned

	cout << x++ << endl;	//less efficient, requires making a temporary to return
	cout << ++x << endl;	//more efficient, simply returns the incremented value

	cout << "demonstrating overloaded increment operators" << endl;

	IntegerW wrapper(10);
	cout << "value: " << wrapper << endl;
	cout << "prefix" << ++wrapper << endl;
	cout << "postfix" << wrapper++ << endl;

	//ternary condition operator
	int zz = 40;
	int xx = 24;
	string result = zz > xx ? "zz greator" : "zz lesser";	//this cannot be overloaded, but just overload conditional operators to achieve overlaoding of this
	cout << '\n' << result << endl;
	

}

//self test
//how many copy operators are there in this expression: x = x + y ?			<2, one for the temporary object, the other to copy the tempory object into x>
// is a compound operator more efficient than a non-compound expression?	<yes, it requires essentially no copying> 
// why ist he preincrement most efficient than the post increment?			<preincrement does not require copying>
// what is the difference between conditional and logical operators?		<conditional: >,<,<=,etc.  logical: &&, ||>









