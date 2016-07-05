//Inheritance
//Matt Stone 7/5/16
//This file should be read line by line, there are a lot of little notes on things that might not be thought of at first sight.

#include<iostream>
#include<string>
using namespace std;


class Animal {
private:
protected:
	string name;
	string msg;
	string extra;
	Animal(string name = "noname", string msg = "rawr") : name(name), msg(msg) { cout << "\tanimal constructor" << endl; };
public:
	void speak() const { cout << msg << endl; }
};

//the keyword public before animal specifices how the derived access modifiers will be changed, public leaves everything as it was set in the base class.
class Dog : public Animal {
private:
	string furColor;
public:	
	Dog(string name) : Animal(name), furColor("gray") //, msg("bark")	//cannot init list a inherited field - theoretically this has already been initialized during base class construction (even if nothing was assigned)
	{cout << "\tdog constructor" << endl; msg = "bark";}
};

class Cat : public Animal {
public: //below changes an inherited field using initializer list with inherited constructor
	Cat(string name) : Animal(name, "meow") { cout << "\tcat constructor" << endl; };
};

class Fish : public Animal {
private:
	string gillColor;
protected: //notice, you can type base constructor after child field inits, but base class constructor is called first
	Fish(string name = "no-name") : gillColor("gold"), Animal(name, "splash") { cout << "\tfish constructor" << endl; }
};

class Goldfish : public Fish {
public: //below changes a inherited field within constructor body
	Goldfish(string name) :Fish(name) { cout << "\tgoldfish constructor" << endl; msg = "blurb"; };
};

void simpleInheritance() {
	cout << "Creating a dog, look at constructor call order" << endl;
	Dog dog("ralph");
	cout << endl;

	cout << "Creating a cat, look at constructor list" << endl;
	Cat cat("maxy");
	cout << endl;

	cout << "Creating a goldfish, look at the constructor list" << endl;
	Goldfish goldfish("timmy");
	cout << endl;

	cout << "Making animals speak" << endl;
	cout << "\tdog says: ";
	dog.speak();

	cout << "\tcat says: ";
	cat.speak();

	cout << "\tgoldfish says: ";
	goldfish.speak();

	cout << endl;
}

//Self notes
/*
the public keyword before the base class (when inheriting) specifies how the class will be inherited.
public inheritance - means that the base public fields will be public, private will be private, and protected will be protected.
protected inheritance - means public = protected, protected = protected, and private = private
private inheritance - means public = private, protected = private, private = private (pretty much locks all the fields of the class

you cannot call a constructor in the body of a child class (java calls super at the first line, c++ calls "super" in init lists (ie first line :))
*/

//Self Test
//write a base class
//write a class to inherit from the base class
//what happens if you forget to inherit publically?						<it will inherit privately, which may mess up further inheritance>
//where do you call the base class constructor?						<in the initializer list of the derived(Child) class>
//Can you initialize a base class field from a child init list?			<no, this must be done either in the base constructor, or in the body of the child constructor (inside the body is an assignment, not initialization)





