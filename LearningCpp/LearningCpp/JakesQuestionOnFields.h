#pragma once
#include<iostream>

//To answer the question: will the field be created twice without an initializer list 
//and setting it to a value in constructor body? 
//Yes it appears to create two objects! (unless you use an intializer list!)
class PrintOnCtor {
public:
	//print something on ctor
	PrintOnCtor() {
		std::cout << "ctor!" << std::endl;
	}
	//print something on dtor
	~PrintOnCtor() {
		std::cout << "dtor!" << std::endl;
	}

};


class HasFieldThatPrints{
	bool value = true;
	PrintOnCtor willIprintTwice_Qmark;
public:
	//prints:
	//ctor!
	//ctor!
	//dtor!
	//dtor!
	HasFieldThatPrints() {
		//1.ctor called before constructor entered
		//2.ctor called on assignment
		this->willIprintTwice_Qmark = PrintOnCtor();
	}

	//prints:
	//ctor!
	//dtor!
	HasFieldThatPrints(bool arg) : willIprintTwice_Qmark() {
	}
	~HasFieldThatPrints() {}
};