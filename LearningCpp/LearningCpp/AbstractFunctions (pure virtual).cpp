//Pure Virtual Functions (that is, abstract functiosn to be defined by derived classes)
//Matt Stone

#include<iostream>
using namespace std;


namespace j7z {
	//abstract class - cannot be instantiated
	class Base {
	public:
		//setting a virtual function to 0 is how to define a pure virtual (ie abstract) function
		virtual void abstractSpeak() const = 0;	//this is an abstract function
	};

	//class that inherts an abstract class
	class Derived : public Base {
	public:
		void abstractSpeak() const {
			cout << "abstract (pure virtual function) " << endl;
		}
	};

}; // j7z end namespace

class j7z::Base;		//note: this is how you do prototypes of classes (aka forward declarations)
class j7z::Derived;		// class prototype isn't necessary here, I just showed because I just learned about it.

void pureVirtual() {
	//j7z::Base b1;		//cannot instantiate a class of abstract type
	j7z::Derived d1;
	j7z::Base* basePtr = &d1;		//base pointer, base is an abstract type.

	basePtr->abstractSpeak();	//this a pointer of abstract type, using a subclasses version of the virtual(abstract) pointer.
}








//self test
//define a function as abstract	(pure virutal)					<do this by setting a virtual function equal to 0>
//can you instantiate abstract class?							<nope, so I guess you don't need to hide the constructor>




