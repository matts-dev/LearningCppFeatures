//Matt Stone
#include <iostream>
void pointers(void){
	//Normal Variables
	int x = 1;
	int y = 2;
	int z = 3;

	//Pointer variable stores address of a normal variable
	int* ptr = &x;	// get the address for variable x

	//pointers are dangerous, reset them otherwise they can leave allowed memory
	int array[3]{0, 0, 0};
	ptr = &array[0];

	//pointers can be used like arrays
	for (int i = 0; i < 3; ++i){
		ptr[i] = 10;
		//No dereference required
		std::cout << ptr[i] << std::endl;
	}

	//Assigning a pointer to an array (arrays are pointers)
	ptr = array;
	ptr = &array[0];
	ptr = &array[1];
	ptr = &array[2];

	//Becareful when using pointers, it is easy to get into non-target memory

	//This is why pointer arthimetic won't work if variables are not in array
	std::cout << &x << ", " << &y << " ptr:" << ptr << ", " << (ptr - 1) << std::endl;
}