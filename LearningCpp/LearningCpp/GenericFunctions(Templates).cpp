//Function Templates (ie generic functions
//Matt Stone 7/11/2016

#include <iostream>
#include "inhert.hpp"
using namespace std;


template <typename T> 
T getMax(T left, T right) {	//you can use typename, or class
	if (left > right)
		return left;
	else
		return right;
}

//you can use the word class instead of typename
template <class T> T getMin(T left, T right) {return (left < right) ? left : right;}

//using two generic types
template <typename T, typename U> 
T getSum(T left, U right){ return left + right; }	//should implicitly cast to T


void genericFunctions() {
	int x = 50;
	int y = 100;
	cout << "x = " << x << ". y = " << y << ". " << endl;
	cout << "max is " << getMax<int>(x, y) << endl;
	cout << "min is " << getMin<int>(x, y) << endl << endl;

	cout << "5.5 sumed with 4 is: " << getSum(5.5, 4) << endl;


	//demonstrating what happens when a generic is called where no overload exists for its operators
	//Inherit::Base baseobj;
	//cout << getSum(5.5, baseobj) << endl;	//no operator for +
}

//Side Notes
//it seems template specification is filled in at compile time, I'm not sure how this handles RTTI
//T, U, etc. are type names, not variable names. You need to give a parameter a name (eg T right) and use the identifier "right" not "T" in the implmentaiton


//Self Test
//Declare a template function that finds the max of two values of the same type
//Declare a template functio that finds the min of two different types

