// Matt Stone
#include<iostream>

void avoidDeadlock();
int main (int argc, char** argv){
	avoidDeadlock();

	std::cout << "\nenter chars to close" << std::endl;

	std::cin.get();
	
	return 0;
}