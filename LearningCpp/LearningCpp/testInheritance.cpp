#include<iostream>

class parent {
private:
protected:
	int protVar = 0;
public:
	void talk() {

	}
};

class child : public parent {
private:
protected:
public:
	void talk() {
		std::cout << "protVar" << protVar << std::endl;
	}
};

class grandchild : public child {
private:
protected:
public:
	void talk() {

	}
};

