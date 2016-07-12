//Implmentation File for Stack Generic Class
#include"TemplateClassStack.hpp"

template<typename T>
j12::Stack<T>::Stack(int size = 10) : stackSize(size){
	if (stackSize > maxSize || stackSize < 1) 
		throw exception("invalid stack size");
	underArray = new T[stackSize];
};

template<typename T>
j12::Stack <T>::~Stack() {
	delete[] underArray;
};

template<typename T>
void j12::Stack<T>::push(T& element) {
	if (top < stackSize - 1) {			//this should be -1, but setting up hot-swaping (E&C)
		underArray[++top] = element;
	}
	else throw exception("stack full");
}

template<typename T>
T& j12::Stack<T>::pop() {
	if(top >= 0)
		return underArray[top--];
	else throw exception("stack empty");
}
