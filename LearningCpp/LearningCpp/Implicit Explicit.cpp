//explicit modifier
//matt stone 6/24/16

#include<iostream>
using namespace std;

class expClass{
private:
	static const int maxSize = 1024;
	size_t _size = 0;
	expClass();
public:
	expClass(int);			//allow implicit conversions
	//expClass(char*);			//allow implicit conversions
	//explicit expClass(int);
	explicit expClass(char*);	//explicit keyword will FORCE the use of this constructo (cannot use assignment operators to find constructors)
	size_t size() const;
	
	//dont worry about the two constructors below
	//expClass(char);
	//explicit expClass(char);
};
expClass::expClass(int x){
	cout << "int constructor" << endl;
	this->_size = sizeof(x);		
}
expClass::expClass(char* array){
	cout << "char* constructor" << endl;
	//simple calculate size in bytes by counting # chars before '0'
	for (int i = 0; i < maxSize; ++i){	//size before 0 is reached (since '0' is equal to n+1, starting @ 0 works)
		if (array[i] == 0){
			_size = i;
			break;
		}
	}
}
//expClass::expClass(char onechar){
//	cout << "single char constructor" << endl;
//	_size = 1;
//}
size_t expClass::size() const{
	return this->_size;
}

void printSize(const expClass& obj){
	//an implicit obj creation will happen if passed a value that can be used with an assingment operator
	cout << "function obj size: " << obj.size() << endl;
}

void explicits(){
	/*how to use this file:*/
		//un comment each section, and see how it is affected when uncommenting the explicit constructors


	//works implicitly [uses integer]
	//expClass a1(9);		
	//cout << "a1 size: " << a1.size() << endl;

	//works implicity [uses char*]
	//expClass a2("a2");
	//cout << "a2 size: " << a2.size() << endl;

	//works implicitly [uses char];		even though char* constructor exists, with explicit you cannot infer this constructor with assignment operator
	//expClass a3 = "a3";	//assignment operator looks for constructor that has "char*" signature as param
	//cout << "a3 size: " << a3.size() << endl;

	//doesn't work implicitly, must use explicity keyword on constructor
	//expClass a4 = 'a';	//char promotes to integer, not string, so it finds the integer constructor
	//cout << "a4 size: " << a4.size() << endl;	//prints 4, because it used integer constructor (when it is not implicit)

	//this will stil use integer constructor, unless a char constructor is made
	//expClass a5('a');
	//cout << "a5 size: " << a5.size() << endl;
	
	//expClass a6("a");
	//cout << "a6 size: " << a6.size() << endl;

	//integer promotion (doesn't work with explicit)
	//printSize('x');		//promotes to integer, calls integer constructor, then calls size (without explicit keyword)
	
	//works with explicit
	//printSize(expClass('x'));	// you see, explicit simply stops implicit conversions, not type promotions

	//printSize("testing char* implicit conversion to constructor");	//doesn't work with explicit
	printSize(expClass("testing char* implicit conversion to constructor"));	//works with explicit

} 

//self test
//what does the explicit keyword do?						<it prevents implicit conversion>
//Does the explicity prevent intgeter promotion?			<no, 'x' will still promote to int if there is an integer constructor, EVEN IF ITI S EXPLICIT>	
//If explicit allows integer promotion, what good is it?	<it prevents certain types of conversions, such as assignment operators calling constructors, or constructing objects based on parameters>

