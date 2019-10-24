#include <iostream>

namespace
{
	class OneArg
	{
	public:
		explicit OneArg(int inX) : x(inX)
		{
			std::cout << "1arg ctor: " << x << std::endl;
		}
	private:
		int x;
	};

	/////////////////////////////////////////
	class ThreeArg
	{
	public:
		ThreeArg(int i, double d, char c) : x(i), y(d), z(c)
		{
			std::cout << "ctor called: " << x << " " << y << " " << z << std::endl;

		}
	private:
		int x;
		double y;
		char z;
	};

	////////////////////
	struct Base
	{
		Base() { std::cout << "base: no arg ctor" << std::endl; };
		Base(Base& copy) { std::cout << "Base Copy Ctor" << std::endl; }
		virtual void foo()
		{
			std::cout << "base: " << this << std::endl;
		}
	};

	struct Child : public Base
	{
		//Child() : Base() {}
		//Child(Child& copy) : Base(copy) { std::cout<<"Child copy ctor" << std::endl;}
		virtual void foo() override
		{
			std::cout << "Child: " << this << std::endl;
			Base::foo(); //proper way to call super method
			static_cast<Base>(*this).foo(); //inproper, constructs an object
			//static_cast<Base*>(this)->foo(); //copy a pointer but causes infinite polymorphic calls

		}
	};


	int true_main()
	{
		OneArg stackObj_1arg(5);
		OneArg x = OneArg(5); //effective c++ claims this is a function style cast eg "int(5.0)"
		static_cast<OneArg>(5); //this cast does in fact construct object

		ThreeArg stackObj(5, 4.0, 'c');
		//static_cast<ThreeArg>(5, 4.0, 'c'); //compile error: 3 arguments does not work; appears to think there are 3 arguments provided to static_cast 


		Child child;
		child.foo();

		return 0;
	}
}

//int main()
//{
//	true_main();
//}
