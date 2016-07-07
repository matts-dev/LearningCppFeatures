//Virtual Functions
//Matt Stone 7/7/16

#include<iostream>

using namespace std;

/*
Adding virtual to a class adds a 4 byte vpointer (hidden).
vpointers point to a vtable. a vtable is essentially a table of pointers to virtual functions.
the vpointer is typically the first value of the class (using reinterpret cast on class for int pointer to see this adr)

vtables are unique to types, not instances. thinking of it as a static variable (java's version of static fields)
*/

namespace j7 {
	class Base1 {
	public: //implicit default constructor will be used
		virtual void speakV() const { cout << "\tbase1 virtual speak" << endl; }
		void speakO() const { cout << "\tbase1 overload speak" << endl; }
		virtual ~Base1() {};
	};

	class Middle1 :public Base1 {
	public:
		void speakV() const { cout << "\tmiddle1 virtual speak" << endl; }
		void speakO() const { cout << "\tmiddle1 overload speak" << endl; }
	};

	class Bottom1 : public Middle1 {
	public:
		void speakV() const { cout << "\tbottom1 virtual speak" << endl; }
		void speakO() const { cout << "\tbottom1 overload speak" << endl; }
	};
}//j7 namespace end


namespace j7b {
	//This namespace differs in that virtual was placed only on the middle class.
	class Base1 {
	public:
		void speakV() const { cout << "\tbase1 virtual speak" << endl; }
		//I would place a virtual dtor here, just so that I know my pointers will call the correct dtor
	};

	class Middle1 :public Base1 {
	public:
		virtual void speakV() const { cout << "\tmiddle1 virtual speak" << endl; }
		virtual ~Middle1() {};
	};

	class Bottom1 : public Middle1 {
	public:
		void speakV() const { cout << "\tbottom1 virtual speak" << endl; }
	};
}// end j7b namespace

void virtualFunctions() {
	j7::Base1 base1;
	j7::Middle1 mid1;
	j7::Bottom1 bot1;

	j7::Base1* basPtr = &base1;
	j7::Middle1* midPtr = &mid1;
	j7::Bottom1* botPtr = &bot1;

	cout << "Below will call a non-virtual function, then a"
		<< "virtual function for each of the pointers\n" << endl;

	//BASE POINTER
	cout << "base ptr -> base obj: " << endl;
	basPtr->speakO();
	basPtr->speakV();

	cout << "base ptr -> middle obj: " << endl;
	basPtr = &mid1;
	basPtr->speakO();
	basPtr->speakV();

	cout << "base ptr -> bottom obj: " << endl;
	basPtr = &bot1;
	basPtr->speakO();
	basPtr->speakV();

	//MID POINTER
	cout << "mid ptr -> mid obj: " << endl;
	midPtr->speakO();
	midPtr->speakV();

	//because virtual is not in the mid class, the pointer doesn't know that it shoudl call bottom
	cout << "mid ptr -> bottom obj: " << endl;
	midPtr = &bot1;
	midPtr->speakO();
	midPtr->speakV();
	cout << "***** " << endl << "notice, mid did not declare speakV() as virtual, but since its base class did declare it as virtual "
		<< endl << "the virtual was inherited (applied) to all subclasses"
		<< "\n***** " << endl << endl;

	cout << "Below examples: base class does not use virtual, but middle class uses virtual" << endl;
	j7b::Base1 base2;
	j7b::Middle1 mid2;
	j7b::Bottom1 bot2;
	j7b::Base1* basPtr2 = &base2;
	j7b::Middle1* midPtr2 = &mid2;
	j7b::Bottom1* botPtr2 = &bot2;

	cout << "only calling virtual functions in the below examples" << endl;

	//base ptr where virtual was declared in middle class
	cout << "\nbase pointer" << endl;
	basPtr2->speakV();
	basPtr2 = &mid2;
	basPtr2->speakV();
	basPtr2 = &bot2;
	basPtr2->speakV();	

	//mid pointer where virtual was declared in middle class
	cout << endl << "middle pointer" << endl;
	midPtr2->speakV();	
	midPtr2 = &bot2;
	midPtr2->speakV();

	cout << "******" << endl
		<<"notice in the base ptr section, the middle class did not propogate the virtual upward in the inheritance tree"
		<< endl << "but then again, why would it? a subclass shouldn't change base class itself" 
		<< endl << "******"  << endl << endl;

	//Once virtual, always virtual
	cout << "Once a virtual function is encountered in a class tree, then all lower subclasses will be virtual" << endl;
	cout << "ie once virtual, always virtual" << endl;
}