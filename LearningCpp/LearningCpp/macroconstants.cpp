//macro constants
//Matt Stone 6/21/2016

#include<iostream>
using namespace std;

//below is an example of the define directive
//macros should have no indentation, be all capitals, and lack semicolons
#define ONE 1
#define STRING "Hello World"

void macroconstants(){
	//warning, using macros can make debugging harder (these will not appear as variables)
	cout << ONE << endl;
	cout << STRING << endl;
}

//self test - macros
//where should the directive (#) symbol be placed?		<far left, no indentation>
//what is the naming convention of macros				<all capitals>
//in c++, what is the better option, MACRO or variable constants?		
//			<probably variable consts, provides better debugging>