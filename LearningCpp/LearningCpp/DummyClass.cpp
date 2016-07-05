#include "DummyClass.h"


DummyClass::DummyClass()
{
	//if (verbose)
	std::cout << this << " was constructed" << std::endl;
	intializer();
}

DummyClass::DummyClass(bool verbose) :verbose(verbose){
	if (verbose)
		std::cout << this << " was constructed" << std::endl;
	intializer();
}

DummyClass::DummyClass(int value){
	verbose = false;
	this->value = value;
	intializer();
}



DummyClass::~DummyClass()
{
	if (verbose)
		std::cout << this << " was destructed" << std::endl;
	intializer();
}

void DummyClass::intializer(){
	id++;
	thisId = id;
}

void DummyClass::saySomething(){
	std::cout << this << " is talking " << std::endl;
}

int DummyClass::echoInt(int echo){
	return echo;
}

int DummyClass::getValue(){
	return value;
}

const std::string& DummyClass::alive() const{
	//testing static variables in a class context.
	static std::string a = ("alive" + std::to_string(thisId));//normally, this might have been a field.
	return (a);// + thisId);
}

//think of .hpp as applying a static filter to this method 
//similar to how returning a const string& (when source is mutable string) applies a constant filter to return value
void DummyClass::staticmethod(){
	std::cout << "this is a static method" << std::endl;
}

//static initializations
int DummyClass::id = 0;		//notice that the type still needs to be defined

//operator overloads (non-member overloads)
//DummyClass operator+(DummyClass& lhs, DummyClass&rhs){
//	int value = lhs.value + rhs.value;
//	bool verbose = lhs.verbose && rhs.verbose;
//	return DummyClass(value);
//}
