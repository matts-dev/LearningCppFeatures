// Matt Stone
#include<iostream>

void customDeleters();
int main (int argc, char** argv){
	customDeleters();

	std::cout << "\nenter chars to close" << std::endl;

	std::cin.get();
	
	return 0;
}