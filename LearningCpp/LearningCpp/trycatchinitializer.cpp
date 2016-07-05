#include <iostream>
#include <exception>

class initTryCatch{
	int integer;
	double longfloat;
public:
	initTryCatch(int, double);
	void printvals(){ std::cout << integer << ' ' << longfloat << std::endl; }
};

initTryCatch::initTryCatch(int x = 0, double y = 0.0)
try : integer(x), longfloat(y)
{
	std::cout << "init list sucessful "<< std::endl;
}
catch (std::exception& e)
{
	e.what();
	std::cout << "init list failed " << std::endl;
}





//Below is from the stack overflow resource http://stackoverflow.com/questions/697026/exception-handling-in-constructor-s-initializer-list
class C
{
	int i;
	double d;
public:
	C(int, double);
};

C::C(int ii, double id)
try : i((ii)), d(id)
{
	//constructor function body  
}
catch (...)
{
	//handles exceptions thrown from the ctor-initializer  
	//and from the constructor functionbody  
}


void initTryCatchMain(){
	initTryCatch x(5, 5.5);
}