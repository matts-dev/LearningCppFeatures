#include<iostream>
#include<functional>
static int main_v()
{
	//default captures should be avoided; they lead to dangling references and give illusion of being completely self sufficient.

	//dangling lambda example
	{
		std::function<int(int)> f_obj;
		{	//simulate function call or something that begins a new scope
			int local_variable = 5;

			//create a default reference capture object
			f_obj = [&](int x) { return local_variable; }; //local variable's scope will not live as long as f_obj!!!
		}
		{//simulate new function call with new scope
			int new_var = 100;
			std::cout << "captured reference value is " << f_obj(0) << std::endl; //we probably will get lucky and the value will be correct, but it is a dangling reference!
		}
		//explicit captures make it easy to see that there will be variable lifetime issues (ie the closure will have a longer lifetime than lambda)
		{
			int localvariable = 5;
			auto explicit_capture = [&localvariable]() {}; //can easily see that we're capturing a local variable, where as the default capture may capture a local variable and we may use it without us realizing the issue
		}
	}

	//default capture by value silently captures by reference example
	{
		int* ptr = new int(33);
		auto dangle_lambda = [=]() {std::cout << *ptr << std::endl; }; //makes a copy of the pointer... not the contents! 
		dangle_lambda();
		delete ptr; //the lambda now dangles, because it only made a copy of a pointer!
		//dangle_lambda(); //undefined behavior of deferencing a deleted pointer

		//so in general, don'y use default capture by value either; specify you captures explicitly and you will avoid small bugs.
	}

	//be aware of how lambda's may capture class fields (hint: it captures the this pointer)
	class Airplane
	{
		int field = 0;

		void method()
		{
			//remember, captures generally only apply to nonstatic local variables (and parameters); field is a member field!
			auto closure1 = [=]() {std::cout << field << std::endl; }; //captures 'this' pointer and accesses field through the pointer (imagine 'this' being passed as a parameter if that makes you uncomfortable)
			//auto closure2 = [field]() {std::cout << field << std::endl; }; //doesn't compile
			auto closure3 = [this]() {std::cout << field << std::endl; };

			//if you only want to capture a copy of the field, you can make a local varaible that is a copy; then capture that local variable (see the cpp14_method below for a better way)
		}

		void cpp14_method()
		{
			auto closure1 = [field = field]() { std::cout << field << std::endl; }; //captures only the field by copy!
		}
	};

	std::cin.get();
	return 0;
}