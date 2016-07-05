//Qualifiers
//Matt Stone6/30/16

#include <cstdio>

class constSafeClassWithMut{
	mutable int x = 0;	//const safe changable
	mutable volatile int y = 0;	//volatile is superfluous, just showing that two qualifiers can be used (order doens't matter)
	volatile int z = 0;
public:
	constSafeClassWithMut(int x) : x(x){};
	void changeX(int x) const {	//demonstrate mutable
		this->x = x; y = x;
		//z = 0; even though this is volitile, it isn't mutable; therefore it cannot be changed in constsafe method.
	}
	int staticVar() const { static int stat = 0; return ++stat; }
};

void qualifiers(){
	const int canontChangevar = 0;
	volatile int threadChangableVariable = 0;		//volatile allows thread changes
	//mutable constUnlessInConstSafeFunction = 0;
	static int staticDurationBetweenFunctionCalls = 0;
	register int x = 0;			// register asks processor to store variable in register, it may or may not use this request.
	//extern int y = 0;			// extern is outside translation unit, and added at linker phase



	const constSafeClassWithMut obj(10);
	obj.changeX(20);

	constSafeClassWithMut obj2(10);
	
	//static variables in member functions are the same for all instances (as expected)
	printf("%d\n", obj.staticVar());
	printf("%d\n", obj2.staticVar());

	printf("%d\n", obj.staticVar());
	printf("%d\n", obj2.staticVar());

	printf("%d\n", obj.staticVar());
	printf("%d\n", obj2.staticVar());
}