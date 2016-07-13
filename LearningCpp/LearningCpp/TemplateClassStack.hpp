//Template Class Example
//Matt Stone 7/12/16

#include<iostream>
#include<exception>
using namespace std;

namespace j12 {
	template<typename T>
	class Stack {
	private:
		int stackSize = 0;		//valid c++11 assignments
		int top = -1;
		int maxSize = 100;
		T* underArray;
	public:
		explicit Stack(int size);
		~Stack();
		void push(T& element);
		T& pop();
	};


}; //end namespace j12

//STACK TESTING
void genericClassStack() {
	int x = 1;
	int y = 2;
	int z = 3;
	try {
		//j12::Stack<int> intStack(-1);		//invalid stack size (too small)
		//j12::Stack<int> intStack(1000);	//invalid stack size (too large)
		j12::Stack<int> intStack(3);
		intStack.push(x);
		intStack.push(y);
		intStack.push(z);
		//intStack.push(z);					//stack full
		cout << intStack.pop() << endl;
		cout << intStack.pop() << endl;
		cout << intStack.pop() << endl;
		//cout << intStack.pop() << endl;	//stack emtpy
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

}

//self test

//write a generic class that is separated into two files
//is the template declaration required before each generic method in the .cpp file?				<yes>
//is java, the generic type isn't need in the constructor; what about in c++? is it neede?		<yes>
