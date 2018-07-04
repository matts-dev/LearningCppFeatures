//Static cast (compile time cast)
//Matt Stone 7/9/16

#include<iostream>
#include<cstdlib>
using namespace std;

namespace j9 {
	class yin { public:	int value = 700; };	// similar classes, but no inheritance relationsihp
	class yang { public: int value = 600; };

	class base {public: virtual ~base() {}; void speak() { cout << "base" << endl; }};
	class mid : public base { public: void speak() { cout << "mid" << endl; } };
	class bot : public mid { public: void speak() { cout << "bottom" << endl; } };

} //end j9 namespace

void staticcasts() {
	//probably should be using dynamic casts since this is inheritance, nevertheless it shows how static casts work
	j9::base* baseptr = new j9::bot;
	baseptr->speak();	//non-virtual function, should use base's overload

	j9::bot* bottomPtr = static_cast<j9::bot*>(baseptr);
	bottomPtr->speak();	

	j9::mid* middlePtr = static_cast<j9::mid*> (baseptr);
	middlePtr->speak();

	delete baseptr;


	//primitive type
	int i9 = 25;
	double d9 = sqrt(static_cast<double>(i9));
	cout << d9 << endl;

}

void reinterpretcasts2() {
	j9::yin yn;			//since this is unsafe, probably should use reinterpret cast
	j9::yang yg;

	j9::yin* yinptr = &yn;
	cout << "yinptr's value: " << yinptr->value << endl;
	//j9::yang* yangptr = static_cast<j9::yang*>(yinptr);		//compiler will not do a static cast because this isn't safe.
	//j9::yang* yangptr = reinterpret_cast<j9::yang*>(yinptr);
	j9::yang* yangptr = (j9::yang*) yinptr;
	cout << "reinterpret cast to yang ptr: " << yangptr->value << endl;
}

//static casts are different from reinterpret casts. reinterpret casts should be used when the cast is expected to be unsafe (such as casting a double ptr to an int ptr)
//the c style casts essentially trys a static_cast, then a re_interpret cast, and a const_cast if necessary.
//const_cast can remove the constant flag
