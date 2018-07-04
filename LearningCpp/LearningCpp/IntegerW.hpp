//An integer wrapper to explicitly show how operators are defined and when constructors are called
//Matt Stone 7/4/16

#include <iostream>
using namespace std;

class IntegerW{
private:
	int value;
public:
	IntegerW(int x);		//place default argument in the implmentation
	~IntegerW();
	void setValue(int val);
	int getValue();
	IntegerW& operator++ ();		//prefix
	IntegerW operator++ (int x);	//postfixf
	friend ostream& operator<< (ostream& ostrm, IntegerW& obj);
	friend ostream& operator<< (ostream& ostrm, IntegerW&& obj);
};

//friend IntegerW osperator+ (IntegerW&lhs, IntegerW&rhs);
//friend IntegerW operator+= (IntegerW&lhs, IntegerW&rhs);
