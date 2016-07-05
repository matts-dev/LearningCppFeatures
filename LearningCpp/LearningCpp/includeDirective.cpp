//Include directive
//Matt stone 6/21/2016

//angle brackets are uesd for system-level includes
#include<iostream>

//Quotation marks are included for project-level include files
#include"macros.hpp"	//this will include the file, include it's include directives


//TRANSLATION UNIT - all the include directives (including the nested directives) 


using namespace std;
void includeDirectives(){
	//these constants are defined in a header file that was included
	cout << _sOne << endl;
	cout << _iOne << endl;
	cout << ONE << endl;
}

//self test
//if your include file has defined macros, can you ues them?
//how can you find the macros?			<read the included header>
//What is a translation unit?
//what is the difference between #include<> and #include""?