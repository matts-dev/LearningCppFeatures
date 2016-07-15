#pragma once
#include<iostream>
#include<string>
//this class was written before I had officially learned how to write classes, hence no initializer lists
class DummyClass
{
	static int id;
protected:
	int value = 0;
	int thisId = 0;
	std::string name = "";
public:
	bool verbose = true;
	DummyClass();
	DummyClass(bool verbose);
	DummyClass(int value);
	DummyClass(int, bool);
	~DummyClass();
	void intializer();
	void saySomething();		//not const safe because of function pointers file, made that before leanrning of const safe
	int echoInt(int echo);		//not const safe because of above note:
	int getValue();				//note const safe because of above note:
	const std::string& alive() const;
	void setName(std::string& name);
	const std::string& getName() const;
	static void staticmethod();	//doesn't make sense to have const-safe static method, no instances made 

	//non member overloads
	//friend DummyClass operator+(DummyClass& lhs, DummyClass&rhs);
};



