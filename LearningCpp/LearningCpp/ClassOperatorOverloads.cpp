//Class Operator Overloads
//Matt Stone 6/25/16

#include<iostream>
using namespace std;

class fraction{
private:
	int numerator = 0;
	int denominator = 0;
	fraction();
public:
	fraction(int num, int den);			//allows implicit assignment of non-fraction value to create object
	fraction(const fraction& obj);
	~fraction(){ cout << '\t' << *this << " destructed " << endl; }
	double result() const;
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
	fraction operator+ (const fraction& rhs) const;	//notice member operators assume lhs is of the same class type
	//fraction operator- (fraction& rhs); 
	//fraction operator* (fraction& rhs);
	//fraction operator/ (fraction& rhs);
	fraction& operator= (const fraction& rhs);

	void print(int x = 10){ cout << x << endl; }
	//fraction operator+ (DummyClass& lhs, fraction&rhs){};	//cannot define non-member overloads in class
	//however, you can put them in the cpp

	friend std::ostream& operator<< (ostream& ostream, fraction& rhs);
	friend fraction operator- (const fraction& rhs, const fraction& lhs);
};

//be careful, if a function overload and a member overload exist, the compiler will not know which to use
fraction fraction::operator+ (const fraction& rhs) const{
	//cout << "rhs: numerator: " << rhs.getNumerator() << endl;
	int numRHS = rhs.numerator*this->denominator;
	int numLHS = this->numerator * rhs.denominator;
	int newDenominator = this->denominator * rhs.denominator;
	return fraction(numRHS + numLHS, newDenominator);
}
//fraction operator + (fraction&lhs, fraction &rhs){ return fraction(0, 0); }

fraction::fraction(const fraction& obj)
	: numerator(obj.numerator),
	denominator(obj.denominator){
	cout << "copy constructor called " << endl;
	//you can try catch/block in an init list, to check for null ptrs (even though we'ren ot using pointers inthis case)
}

fraction& fraction::operator= (const fraction& rhs){
	if (&rhs != this){
		this->numerator = rhs.numerator;
		this->denominator = rhs.denominator;
	}
	cout << "assignment operater" << endl;
	//must return a value for chain assignment operators
	return *this;
}


//DEFAULT VALUES USED IN CONSTRUCTOR
fraction::fraction(int num = 0, int den = 1) : numerator(num), denominator(den){
}

double fraction::result() const{
	if (denominator != 0)
		return (double)numerator / denominator;
	else return 0;	// not valid mathematically, 
}

std::ostream& operator<< (ostream& ostream, fraction& rhs){
	ostream << rhs.numerator << '/' << rhs.denominator;
	return ostream;
}

//non member overload to allow certain implicit conversions
fraction operator- (const fraction& rhs, const fraction& lhs){
	int numer = rhs.numerator*lhs.denominator - lhs.numerator*rhs.denominator;
	int denom = rhs.denominator * lhs.denominator;
	return fraction(numer, denom);
}


//---------------------------------------------MAIN-----------------------------//

void classoverloads(){
	cout << "making fraction: 5/3" << endl;
	fraction a1(5, 3);
	//cout << a1.result() << endl;

	cout << "making fration 8/4" << endl << endl;
	const fraction a2(8, 4);

	cout << "adding the two fractions with an operator overload" << endl;
	fraction a3 = a1 + a2;		//not overoaded, justing implicit assigment
	cout << "a3 values after operator. " << a3.getNumerator()
		<< "/" << a3.getDenominator() << endl;

	//seeing destructor on tempory object
	cout << "\ndestructor of temporary objects is called before function is over" << endl;
	a1 + a2;

	//space break
	cout << endl << endl << endl;

	fraction b1 = 4;	//use second arg as default value [use explicit to prevent this]
	fraction b2(4, 2);	// 4/2
	fraction b1c = b1;	//uses copy constructor
	fraction b2c(b2);	//uses copy constructor

	b1c = b1 = b1 = b1;	//assignment operator

	cout << b1 << endl;
	cout << b1c << endl;
	cout << b2 << endl;
	cout << b2c << endl;

	fraction a12(1, 2);
	//using implicit conversion
	cout << "overload esoterics, 1/2 - 10: " << a12 - 10 << endl;
	//no implicit convesion for 10 using member overloads, must switch to non-member overload
	cout << "overload esoterics, 10 - 1/2 " << 10 - a12 << endl;
}

//self test
//write an opeator over load to add two member functions
//write operator overload to subtract two member functions
//write operator overlaod to multiply to member functions
//write operator overload to divide two memember functions

//are the overloaded opeators const safe (if they should be const safe)?

//write an overload for the assigment operator 

//write a friend operator overload
//write an operator overload that allows the usage of cout (stream operator)

//what does a friend function have access to? <it has access to member variables in the class,
//		^^^which is necessary if if overloading a non-same class lhv that doesn't use accessors 

//write a function (or constructor) that uses default arguments if no arguments are supplied. 

//analyze the temporary objects using destructors

