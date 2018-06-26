#pragma once
#include <memory>
class Upimpl
{
private:
	//having a implementation defined in the .cpp

	//forward declaration allows us to defer defining this until we're in the private .cpp file
	struct Implementation;
	std::unique_ptr<Upimpl::Implementation> pimpl;

public:
	Upimpl() noexcept;
	//~Upimpl() { /*dtor called here, which instantiates the template function dtor, imple is an incomplete type*/}; //will cause error because Upimpl::Implementation is still an incomplete type at this level
	//note, the default dtor is also inlined in the class header, so the dtor of uptr will still not be able to see the size of the implementation (it will be incomplete type), so the default dtor doesn't work either.
	~Upimpl(); 

	//moving the implementation also requries being able to see the full type of Implementation, because move deletes the ptr of the destination before moving!
	//this means you must define the move functions in the .cpp
	//Upimpl(Upimpl&& move) {};
	//Upimpl& operator=(Upimpl&& move) {};
	Upimpl(Upimpl&& move) noexcept;
	Upimpl& operator=(Upimpl&& move) noexcept;

	//copy semantics
	Upimpl(const Upimpl& copy) noexcept;
	Upimpl& operator=(const Upimpl& copy) noexcept;


	void foo();
	int getX();
	void setX(int newX);
};

