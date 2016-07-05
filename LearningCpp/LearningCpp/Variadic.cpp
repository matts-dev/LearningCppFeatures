//Variable argument parameters - ie variadic functions
//Matt Stone - 6/20/2016
#include<iostream>
#include<cstdarg>

using namespace std;

//prototypes
void printFirst(const int numberArgs, ...);
void print(const int numberArgs, ...);
double averageWithSpacer(const int numArgs, char spacerVar, ...);
void doItTwice(int numargs, ...);

void variadic(){
	printFirst(2, 1.1, 3.3);
	print(3, 1.1, 2.2, 3.3);
	cout << "average is " << averageWithSpacer(5, 's', 1.0, 2.0, 3.0, 4.0, 5.0) << endl << endl;
	doItTwice(3, 1.1, 2.2, 3.3);
}

void printFirst(const int numberArgs, ...){
	double val = 0;
	//How to use va_list
	va_list args;					//create the list
	va_start(args, numberArgs);		//start list (type of iterator?) [second param is variable BEFORE START]
	val = va_arg(args, double);		//get first argument (similar to java's next())
	va_end(args);					//signify that list is done
}

void print(const int numberArgs, ...){
	va_list args;
	va_start(args, numberArgs);		//note, this takes last argument before ...
	for (int i = 0; i < numberArgs; ++i){
		cout << va_arg(args, double) << " ";
	} cout << endl;
	va_end(args);
}

//Added space to show that you must pass the last variadic argument into va_start
double averageWithSpacer(const int numArgs, char spacerVar, ...){
	double total = 0.0;
	va_list args;
	va_start(args, spacerVar);	//must choose last variable before ...
	for (int i = 0; i < numArgs; ++i){
		total += va_arg(args, double);
	} cout << endl;
	va_end(args);

	return total / numArgs;
}

void doItTwice(int numargs, ...){
	//first time
	cout << "printing twice in a single method (1):" << endl;
	va_list args;
	va_start(args, numargs);
	for (int i = 0; i < numargs; ++i){
		cout << va_arg(args, double) << ' ';
	}cout << endl;
	va_end(args);
	
	//second time
	cout << "printing twice in a single method (2):" << endl;
	va_start(args, numargs);		//recycling va_list variable
	for (int i = 0; i < numargs; ++i){
		cout << va_arg(args, double) << ' ';
	}cout << endl;
	va_end(args);
}

//self test

//create a variadic argument function
//What are the steps in handling variadic argments?
//	create the list
//	star the list
//	collect the arguments
//	close the list





