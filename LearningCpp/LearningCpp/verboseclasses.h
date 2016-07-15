//base class to use with smart pointers
//Matt Stone 7/14/16
#pragma once
#include <iostream>
using namespace std;
namespace sptrs {
	class Base {
	public:
		int id;
		Base() : id(++idcount) { cout << "\t+base ctor:" << id << endl; }
		virtual ~Base() { cout << "\t-base dtor:"<< id << endl; }
		virtual void speakV() { cout << "base:" << id << " speaking virtually" << endl; }
		static int idcount;
	};

	class Derived : public Base {
	public:
		Derived() { cout << "\t\t+derived ctor:"<< id << endl; }
		virtual ~Derived() { cout << "\t\t-derived dtor:"<< id << endl; }
		void speakV() { cout << "derived:" << id << " speaking virtually" << endl; }
	};

}// end namespace sptrs