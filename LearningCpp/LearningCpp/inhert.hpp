//A header file containing classes for including basic inheritance testing in other files
//Matt Stone 7/10/16

#include <iostream>
using namespace std;

//functions are NOT CONST SAFE for the const_cast file
namespace Inherit {
	class Base { 
	public:
		virtual ~Base() {};
		virtual void speakV() {	cout << "base with virtual" << endl;}
		void speak() { cout << "base non-virtual" << endl; }
	};


	class Middle : public Base {
	public:
		void speakV() {	cout << "middle with virtual" << endl;	}	//virtual declared in base class
		void speak() { cout << "middle non-virtual" << endl; }

	};

	class Bottom : public Middle {
	public:
		void speakV() {	cout << "bottom virtual" << endl;	}		//virtual declared in base class
		void speak() { cout << "bottom non-virtual" << endl; }
		void botOnly() {cout << "this is only available in the bottom subclass" << endl;}
	};
}// end namespace inherit