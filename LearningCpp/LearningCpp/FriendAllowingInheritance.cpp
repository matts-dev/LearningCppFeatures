//Friend keyword
//Matt Stone 7/6/16

#include<iostream>
#include<string>
using namespace std;



namespace J6A {
	class Base {
	private:
		Base() { cout << "private constructor" << endl; }
		string msg = "private message";		
	public:
		friend class Derived;
		friend class Outsider;
		friend void speak(J6A::Base& obj);		
	};

	class Derived : public Base {
	public:
		Derived() : Base() { cout << "derived created\n" << endl; }
	};

	class Outsider {
	public:
		void friendClassFunct(J6A::Base& obj) { cout << obj.msg << endl; }
	};
	
} //end J6 namespace 

//this is part of J6A namespace, did this to show how things may be added to namespaces outside of curly braces
void J6A::speak(J6A::Base& obj) {		//this is put in the namespace
	cout << obj.msg << endl;
}

void friendInheritance() {
	//uses the friend class keyword to access the private constructor
	J6A::Derived derv;	

	//notice, derived references can be inserted into function accepting base without conversion
	J6A::speak(derv);	//friend function

	//outside class that is a friend using a private variable of anothe class
	J6A::Outsider out;
	out.friendClassFunct(derv);
}