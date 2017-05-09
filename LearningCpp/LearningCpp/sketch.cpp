//file for quick testing

#include<iostream>
#include<memory>
#include<string>
#include<thread>
#include<mutex>
#include<deque>
#include"verboseclasses.h"
#include"DummyClass.h"
#include"inhert.hpp"
#include"JakesQuestionOnFields.h"
#include <cstdint>
#include <climits>
#include <bitset>

using namespace std;
using sptrs::Base;


//This is how you foward declare functions in namespaces
namespace polyTest {
	void testPolyCompare();

	//added something to test diff on commits
}


void internetCheckSum();
void crc();

void sketch() {

	//internetCheckSum();
	{
		cout << "\n\nnoarg" << endl;
		HasFieldThatPrints y;
	}

	{
		cout << "\n\narg" << endl;
		HasFieldThatPrints x(true);
	}
}

void internetCheckSum() {
	string data = "Link Layer";

	int sum = 0;
	for (unsigned int i = 0; i < data.length(); i += 2) {
		if (i + 1 < data.length()) {
			sum += ((data[i] << 8) + data[i + 1]);
		}
		else {
			sum += data[i] << 8;
		}
	}

	int mask = ~(-1 << 16);
	int sigBits = sum >> 16;

	//add over the carry 
	while (sigBits > 0) {

		cout << bitset<16>(sum) << endl;
		int carry = sum >> 16;

		//clear off what was carried
		sum &= mask;

		// add back what was carried 
		sum += carry;

		sigBits = sum >> 16;

	}

	sum = ~sum & mask;

	cout << bitset<16>(sum) << endl;
}

void crc()
{

}

