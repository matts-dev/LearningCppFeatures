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
#include <cstdint>
#include <climits>

using namespace std;
using sptrs::Base;

void printBytes(char* start, int numBytes);

//This is how you foward declare functions in namespaces
namespace polyTest {
	void testPolyCompare();
}

void sketch() {
	polyTest::testPolyCompare();
}

void printBytes(char* ptr, int numBytes) {
	for (int i = 0; i < numBytes; ++i, ++ptr) {
		printf("%.2x ", *ptr);
	}
	printf("\n");
}

