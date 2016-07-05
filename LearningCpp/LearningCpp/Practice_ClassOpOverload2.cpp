//Class Op Overload 2
//Matt Stone 6/26/16

#include<iostream>
#include<string>

using namespace std;

class ovld2{
private:
	int _n = 0;
	int _d = 1;
public:
	explicit ovld2(int numer = 0, int denom = 1) : _n(numer), _d(denom){};
	~ovld2(){ cout << *this << " dtor" << endl; };
	ovld2 operator+(const ovld2& obj) const;
	friend ostream& operator<< (ostream& o, const ovld2& obj);//non-member

};

ovld2 ovld2::operator+(const ovld2& obj) const {
	int numerator = obj._n*this->_d + this->_n*obj._d;
	int denominator = obj._d*this->_d;
	return ovld2(numerator, denominator);
}

ostream& operator<< (ostream& o, const ovld2& obj){
	o << obj._n << '\\' << obj._d;
	return o;
}

void classoverloads2(){
	ovld2 ol(1, 2);
	ovld2 ok(1, 2);
	ovld2 temp = ol + ok;
	cout << temp << endl;
}