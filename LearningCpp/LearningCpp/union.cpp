//unions
//Matt Stone 7/3/2016
//Note: this is the examlpe given from the course, usually I come up with my own examples, but I remade this one only lsighlty differently.

#include<iostream>
#include<cstdio>
#include<cstdint>
using namespace std;

union ipv4{
	//union uses the same memory for all its fields
	uint32_t i32;
	//this structure will share memory components with the i32
	struct {
		uint8_t a;
		uint8_t b;
		uint8_t c;
		uint8_t d;
	} octets;			//placing name of structure here creates a variable, rather than a type
};

void unions(){
	ipv4 unionTest;
	unionTest.octets = { (uint8_t)111, (uint8_t)163, (uint8_t)333, (uint8_t)444 };
	cout << "i32: " << hex << unionTest.i32 << dec << endl;
	cout << "8bits: " << (int)unionTest.octets.a << " "
		<< (int)unionTest.octets.b << " "
		<< (int)unionTest.octets.c << " "
		<< (int)unionTest.octets.d << endl;
}

//self test
//what is special about unions?			<they use the same memory for all the fields, so there is only really 1 field>
//write a union
//what happens if a structure has identifier typed after the word "structure"		<that is the type of the new structure>
//what happens if a structure only has an identifier after the } brace?				<that is a varaible created>
