#include <iostream>
#include <string>
#pragma once
namespace polyTest {

	class super {
	public:
		virtual std::string getValue() { return "1super"; }
		virtual std::string compare(super* other) {
			return this->getValue() > other->getValue() ? this->getValue() : other->getValue();
		}
	};

	class A : public super {
	public:
		std::string getValue() { return "2A"; }
	};

	class B : public super {
	public:
		std::string getValue() { return "3B"; }
	};

	void testPolyCompare() {
		super* s = new super;
		A* a = new A;
		B* b = new B;

		std::cout << "s vs a: " << (s->compare(a)) << std::endl;
	}
}