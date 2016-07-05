//Exceptoins
//Matt Stone 6/15/2016

#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>	//random
#include <ctime>	//random seed

using namespace std;

//You can define your own exceptions and give them behavior
class MyException : public exception {
private:
	char* msg;
	MyException() { };	//privitizes no-arg constructor
public:
	//constructor that takes in an c_str error message
	MyException(char* msg) : msg(msg){ /*this->msg = msg; */ };
	//return the message
	const char* what(){ return msg; };
};
//Prototypes
void broken(void);
void brokenWrapper(void);
void idontexcept(void);
void customException(void) throw(MyException, exception);

//You can make specific error message objets
const MyException A("premade exception: A");
const MyException B("premade exception: B");

// ----------------------------------------- MAIN -----------------------------------------
void exceptions(void){
	//customException();	//even thow throw(a,b) used; compiler doens't force try/catch block
	try{
		//broken();
		brokenWrapper();
		customException();
		cout << "\nYou shouldn't see this message if an exception was throw " << endl;
	}
	catch (MyException& specific){	
		cout << "custom exception found: " << specific.what() << endl;
	}
	//exception order matter, put more general last
	catch (exception& all){		//notice reference used, more efficient 
		cout << "exception.what(): " << all.what() << endl;
	}
}


//throw() is an exception specification; empty means this method doesn't throw an exception
void idontexcept(void) throw(){
	//no arguments in throw, this method shouldn't throw an exception
	//the throw() can be populated with exception arguments e.g. throw(a, b ,c)

	//the throw() is an exception specification 
}

//Mehod *suggests* throws 2 exceptions; other exceptions could be thrown
void customException(void) throw(MyException, exception) {
	srand((int) time(0));
	int x = (int)(rand() % 4);
	if (x == 2){
		throw MyException("custom exception newly made");
	}
	else if (x == 1){
		throw exception("default exception");
	}
	else if (!x){	//x == 0   :)
		throw A;
	}
	else {
		throw B;
	}

}

void broken(void){
	//I dislike microsoft visual studio because it doesn't clue to errors
}

void brokenWrapper(void){
	cout << "wrapper: before exception calling method" << endl;
	broken();
	cout << "wrapper: after exception calling method" << endl;
}


//Exception specifications are bad...
//http://www.gotw.ca/publications/mill22.htm


//Why? article summarized drastically
//Exception specifications do not guarantee the listed exceptions, they just suggest
//	-many compilers (including ms vistual studio) do not have good implmentaitons of handling exceptions
//  shadow types (messing up c's strongly typed system)
//		-typedefs do not allow exception specifications
// <more stuff in the article>

//self test
//write an exception call that must be constructed with a string arguement
//throw an exception
//throw a specific exception object 
//catch differnt type of exceptions
//how to write xception specification
//what does the specification throw() do?
//Should exception specifications be written?