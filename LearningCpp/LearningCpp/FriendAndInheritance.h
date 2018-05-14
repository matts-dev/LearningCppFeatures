// Example program
#include <iostream>
#include <string>

class Factory;
struct FriendCheat;

class Top {
	friend class Factory;
protected:
	Top() {}
	virtual void talk() { std::cout << "top" << std::endl; }
};

class Mid : public Top {
protected:
	Mid() {}
	virtual void talk() { std::cout << "mid" << std::endl; }
};

class Bottom : public Mid {
	friend struct FriendCheat;
protected:
	Bottom() {}
	virtual void talk() { std::cout << "bottom" << std::endl; }
};

class Factory {
public:
	void talk(Top* instance) {
		//if friend persists, all private constructors below can be called without error
		Top top;
		//Mid mid; //friend declaration (in top) does not move to subclass MID, so this causes compile error
		//Bottom bottom; //friend declaration (in top) does not move to subclass MID or BOTTOM, so this causes compile error
		instance->talk(); //can be used to access private functions if super class instance is friend towards this class
	}
};

struct FriendCheat {
	static Bottom* getInstance() { return new Bottom(); }

};

int main() {
	Factory factory;
	Bottom* bottom = FriendCheat::getInstance();

	//factory can dynamically access a private method if it can obtain a handle on where it has access to a super class
	factory.talk(bottom);
}
