//Constructors (initilizers lists, assigment operators, copy constructors, destructors)
//Matt Stone 6/23/16
#include<iostream>
#include<string>
#include"DummyClass.h"

using namespace std;

class A623{
private:
	string name;
	int age;
	DummyClass* heapVar = nullptr;
protected:
public:
	A623();
	A623(string name, int age);
	A623(A623& obj);
	~A623();

	A623& operator = (A623& obj);
	void printNameAge() const;
};

A623::A623() : name("unkn"), age(-1), heapVar(new DummyClass(false)) {	//if a no-arg constructor is not defined, there is a default made
	cout << "\tno arg-constructor" << endl;
}

A623::A623(string name, int age) : age(age), name(name), heapVar(new DummyClass(false)){
	cout << "\targ constructor called " << endl;
}


A623::A623(A623& obj):name(obj.name), age(obj.age) , heapVar(new DummyClass(*(obj.heapVar))){
	//usesd DummyClass implicit copy constructor since I KNOW there is no heap fields. 
	cout << "\tcopy constructor called " << endl;
	//heapVar = new DummyClass(*(obj.heapVar)); //another way to do it 
}

A623::~A623(){
	cout << "\tdesturctor called" << endl;
}

A623& A623::operator= (A623& obj){
	this->name = obj.name;	//notice no accessors, just like in java
	this->age = obj.age;	//since this is within the same class, accessors not needed
	return *this;	
}
void A623::printNameAge() const{
	cout << "Name: " << name << ". Age: " << age
		<<". status: " << heapVar->alive() << ". ADR:" << this << endl;
}


void constructors(){
	//Stack variables
	A623 a1;				//default constructor (requires no paraenthesis)

	//Rule of 3 - implicit C++ methods will create shallow copies with pointers, 
	//overload the 3(copy const, destruct, and assigment) to protect from shallow copies (thus making deep copies)
	A623 a2("Matt", 24);	//arg constructor
	A623 a3 = a2;			//calls implicit copy constructor before assignment [well, now I have defined my own so it calls the explicit]
	A623 a4(a2);


	a1.printNameAge();
	a2.printNameAge();
	a3.printNameAge();
	a4.printNameAge();

	cout << endl << endl << "dynamic objs" << endl << endl;
							
	//creating objects dynamically

	A623* b1 = new A623();
	A623* b2 = new A623("Matt", 24);
	A623* b3 = new A623("Stac", 22);

	delete b3;
	b3 = new A623(*b2);

	b1->printNameAge();
	b2->printNameAge();
	b3->printNameAge();

	delete b1;
	delete b2;
	delete b3;
}

//self test constructors
//what is the rule of 3?						<general rule of overloads, helps protect from shallow copies>
//what are overloaded in the rule of 3?			<implicit copy constructor, assignment operator, and destructor>
//how might a copy constructor change?			<it will call a copy constructor on any heap-stored objects/arrays>
//how might the assignment operator change?		<it will call a copy constructor for heap objs, rather than just copying pointer address>
//how might the destructor operator change?		<it will call 'delete' on the pointer objects, to prevent garbage>

//practical
//write a class that contains a field that points to a heap object
//write an operator overload for the assignment operator (=)
//write a copy constructor using references
//write a destructor that cleans up a pointer
//write a constructor that uses an initializer list to make field assignments
//make sure to include heap objects in one initializer list, and one in the constructor body

