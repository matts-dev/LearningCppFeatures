//new and delete
//Matt Stone 6/27/16
#include<iostream>
#include<string>
#include<exception>

using namespace std;

class character{
	string name = "";
public:
	character(string name = "noname") : name(name){};
	operator string () { return name; }		//conversion operator for string
	string getName(){ return name; }
};

void newdel(){
	// ------------------------------- SINGLE OBJECT ------------------------------- //
	character* bob = new character("bob");
	bob->getName();	//doens't check if pointer is null
	delete bob;

	character* joe = new (nothrow)character("joe");
	if (joe != nullptr) cout << joe->getName() << endl << endl;
	delete joe;	//delete has a nullptr  check, so it doesn't need to be in if statemnet

	// ---------------------- DYNAMIC ARRAYS OF OBJECTS ---------------------- //

	//The contents of this array will also be stored on heap

	//dynamic arrays use the default constructor unless else specified (below only changes 2 objects
	character* dwarfs = new character[4]{{"dwarf1"}, { "dwarf2" }};	//initialized only 2

	for (int i = 0; i < 4; ++i)	cout << dwarfs[i].operator std::string() << endl;
	cout << endl;
	delete[] dwarfs;

	//create an array that will return nullptr if the new is not sucessful
	dwarfs = new (nothrow)character[4];	//will use default constructor
	for (int i = 0; i < 4; ++i) cout << dwarfs[i].getName() << endl;		//arrays are like de-referenced ptrs
	cout << endl;
	delete[] dwarfs;

	//you CANNOT initialize to null pointers like below (this points to stack objects, not pointers)
	dwarfs = new (nothrow)character[4](); //dwarf itself can be a null pointer, but it cannot contain null pointers since its contents are NOT POINTERS
	delete[]dwarfs;




	// ---------------------- DYNAMIC ARRAY OF DYNAMIC OBJECTS ---------------------- //
	//I believe this to be superfluous, if an array is on the heap, so are the objects it contains 

	//creating a array of pointers to pointers (be sure to inclue parenthesis)
	character** elves = new character*[5]();	//parenthesis cause nullptr initialization, otherwise it will give non-sense pointers (what ever value was left in memory I believe)
	for (int i = 0; i < 5; ++i){
		//if (elves[i] == nullptr) cout << "null ptr in elves, creating" << endl; //use this to see that you can initialize to nullptr
		elves[i] = new character("elf:" + to_string(i));
	}
	for (int i = 0; i < 5; ++i){	//put this in a different loop for readability
		cout << (*elves[i]).getName() << endl;
	}
	for (int i = 0; i < 5; ++i){
		delete elves[i];	//clear object
	}
	delete[] elves;		//will delete the array, and call the destructor on pointers





	// ---------------------- DYNAMIC ARRAY OF DYNAMIC ARRAYS OF POINTERS ---------------------- //

	//WARNING: complicated memory managment in multidimensional dynamic arrays, this code is simply for curiosity and should be avoided

	//Make the underlying arrays (without default constructor calls)
	character*** legions = new character**[5]();	//()sets contents pointers to nullptr(NULL), rather than non-sense pointers
	for (int i = 0; i < 5; ++i){
		legions[i] = new character*[5]();			//() sets contents to nullptr(NULL), rather than non-sense pointers
	}

	//At this point, we have a clean multidimensional array [that doesn't need deleting]

	//populating the multidimensional array
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j){
			legions[i][j] = new character("V:" + to_string(i) + "," + to_string(j) + ". ");
		}
	}

	//print the contents of the populated multidimensional array
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j)
			if (legions[i][j] != nullptr){
				cout << legions[i][j]->getName() << ' ';
			}
			else {
				cout << i << ',' << j << " is nullptr";
			}
			cout << endl; //format: separate row
	}
	cout << endl; //format: add space 

	//get an instance to check if deleted
	character* testptr = legions[4][2];

	//clean up the memory of the multidimensional array
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j){
			delete legions[i][j];		//deletes individual obj	[deletes contents, arrays still stand]
		}
		delete[] legions[i];			//dtor on dynamic array obj	[deletes the j arrays]
	}
	delete[] legions;					//dtor on dynamic array obj [deletes the i array]

	try{
		string name = testptr->getName();
		cout << "if you're reading this, testptr dwas not deleted: " << name << endl << endl;
	}
	catch (exception e){
		cout << "testptr was deleted" << endl << endl;
	}

	// ---------- DYNAMIC MULTIDIMENSIONAL ARRAYS USING SINGLE ARRAY ---------- //

	/* Using a single array, but treating it like a multidimension array, provides easy cleanup.*/
	int columns = 5;
	int rows = 5;
	int columnsSize = 5;		//could have used columns variable, but did this for explicity
	character** leagues = new character*[columns*rows]();	//make array of pointers, cols*rows gives the total number of elements
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j){
			leagues[i*columnsSize + j] = new character("league" + to_string(i) + ',' + to_string(j));
		}

	//Cleaning up the array
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			delete leagues[i*columnsSize + j];
	delete[] leagues;	
	

	// ----------------------- DEFAULT INITIALIZING BASE TYPES ---------------------- //
	int* x;
	x = new int[4];		//does not initialize
	for (int i = 0; i < 4; ++i) 
		cout << x[i] << ", ";
	cout << endl;

	x = new int[4]();	//initializes to 0
	for (int i = 0; i < 4; ++i)
		cout << x[i] << ", ";
	cout << endl;

	//x = new int[4](10);	//THIS IS NOT VALID, you may not use this. instead use std::fill


	//note, you can call delete on null ptr, and it will not crash the program.
	character* nulltest = nullptr;
	delete nulltest;		//no exception
}


//Self-test
//Create a dynamic object using new
//delete the dynamic object useing delete
//create a dynamic object that will, instead of throwing an exception on creation, use a null pointer if creation fails
//create a dynamic array[] 
//delete the dynamic array[]
//should you creat dynamic objects within a dynamic array?	<no, I believe anything stored in a heap array is also heap storage>


