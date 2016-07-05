//Matt Stone

#include<stdio.h>
#include<iostream>
void tertiary(){
	int trueValue = 1;
	int falseValue = 0;
	printf("1 is greater than 0? %d\n", trueValue > falseValue ? trueValue : falseValue);
	printf("1 is less than 0?: %d\n", trueValue < falseValue ? trueValue : falseValue);
	
	//c++ added bool values; but true is 1, false is 0; thus compatible with c
	std::cout << "bool true  is: " << true << std::endl;
	std::cout << "bool false is: " << false << std::endl;
}