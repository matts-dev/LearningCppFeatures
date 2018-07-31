#include<iostream>
#include<tuple>
#include <typeinfo>


//DISCLAIMER: here are my notes on trying to create a mental model for understanding packaging of variadic templates, expect it to be strange. :)
//this is mostly a memory-aid/pseudo-methodology that helps understanding

namespace
{
	/*
		before we start, know the concepts.
		1. templates can accept a "pack" of arguments; sending a pack of arguments requires packaging up the arguments (to be more consistent with code, it requires a packing syntax at declaration)
				typename... Args	//creates a package to hold args
		2. to use arguments in an argument pack, you must unpack the arguments.
				args...				//unpacks the packaged arguments in arg.
				Args...				//unpacks the types of the arguments (used to instantitae containers, etc)

		3. If we expand something, it produces a comma delimited expansion;
			IE if Args contains a {int, double, char}
			then Args... is a text swap for 'int, double, char'

		DEFINITIONS: for the following examples,
			Args = This is a template parameter pack
			args = This is a function parameter pack
	*/
	//---------------------------------------------------------------------------------------------------------------------------------
	/*
		It's hard to just remember where ellipses go. I have a mental model to help with it.
		imagine that the ellipses signal a package operation is to be done
			... = package_operation()
		Now imagine that his operation is binary, it either packs things, or unpacks things!
		So, if we see 
			typename... Args
		It looks like we're doing a package operation on typename. 
			Would it make more sense that we are packaging up typenames or unpacking typenames?
			I think it is intuitive that we're packing up types. 
				If we're using typename, then we are defining a type. 
				With multiple types, it is kind of like we're defining a name for all of those types collectively 
		When we see 
				Args... args
			We're applying the packaging operation to Args, which is already packaged. So we therefore must be unpacking the arguments
				Args... args
					becomes
				int args_1, double args_2, char args_3
			But imagine that the collective of args_0, args_1, and args_2 are just called args

	//---------------------------------------------------------------------------------------------------------------------------------
	Before I talk through the steps of packing/unpacking, imagine what we want to do:
		1. We want to compress all the variadic types into a single type -- named Args
		2. We want to use Args to define the type of parameters a function accepts
			-note: we can't name these arguments at this step, so we will expand Args for the function signature, but we still will refer to the arguments collectively
		3. We want to an lvalue name for the arguments we were passed, but we need to do that collectively. So we will let the arguments be stored in a single varaible named args
		4. We want to use the contents of args for something, so we unpackage them into a container that can handle variadic arguments (alternatively we could forward the arguments to something.)
		5. We will use that container to the job done
		
	Now to talk through those steps
		template<typename... Args>						When we want to name a package of multiple types, we are creating a package. So the ... operating is packaging. 
		void variadic_function(Args... args)			Here we're applying ... to a packaged type, thus unpacking the types. However, we need a name for all of the types, which we will just call args
															It's as if we unpack Args into int, double, char; but then create a package named args. Here's where my mental model is a bit shaky.
															I think of it as explicitly unpackaging Args, and implicitly packaging args
		std::tuple<Args...> args_expanded_container;	Here we expand(unpackage) our Args package again to define a type -- ie the type of tuple that will be our container
		args_expanded_container = { args... };			Here we expand(unpackage) our package 'args' into the initializer list
	*/
	/*
		Here's another methodology. Imagine that the ... is a directional operator -- kind of like a unix pipe |. It pipes from left to right.
		So typename... Args pipes from typename into args. Now, knowing that the piping moves into the --> direction, there are two scenarios
			scenario 1: There exists a symbol on both sides of the pipe; e.g.		A... B			;So A pipes into B
			scenario 2: There exists a symbol only on the left side;	 e.g.		A...			;A pipes into nothing, so A is expanded
		When there's a symbol to the right, the packaging stores the entire contents piped into the symbol.
		When there's NO symbol to the right, the packaging unpacks the arguments.

			template<typename... Args>								Pipe whatever types are typed into the template into args
			void variadic_function(Args... args)					Pipe Args into args		//here again is where this method breaks down; and i prefer the first to this one
			std::tuple<Args...> args_expanded_container;			Pipe Args into nothing, this is an expansion
			args_expanded_container = { args... };					Pipe args into nothing, this is an expansion
	*/
	/*
		In all honesty, the best approach is probably just to view ... as an expansion operation. 
			by doing that, then first time you ever see ... is an exception, it is with typename... or class..., and it doesn't expand the pack.
			but in all other cases, this rule is true

		Whenever you see a pack without ..., you can view it as "packaging"
		std::forward<Args>(args)...
			Args is packed
			args is packed
			the whole expression is expanded
	
	*/
	//---------------------------------------------------------------------------------------------------------------------------------
	template<typename... Args> //to declare a parameter pack, the ellipses is attached to word typename (or class if using that); I think of this as creating a package. `
	void variadic_function(Args... args) //to unpackage a package, apply ... to the package name!
	{
		//we need a container that can accept a variadic number of arguments.
		//it so happens that tuple is such a container!
		//But there's a problem, how do we convey the types of the arguments we captured to tuple<>?
		//What we need to do is unpacked (ie expand) the arguments type!
		//So, with our mental model of ... meaning a packing operation, if we apply the packing operation to a packed type, it should unpack it!
		std::tuple<Args...> args_expanded_container;

		//Now that we have a container for our arguments, let's see what our compiler things the tuple's type is (remember though, that typeid is 100% reliable, see e_modern_cpp/ViewingDeducedTypes)
		std::cout << typeid(args_expanded_container).name() << std::endl; //MSVC: class std::tuple<int,double,char>		 gcc:St5tupleIJidcEE 

		args_expanded_container = { args... }; //unpack into an initializer list and use that for assignment

		size_t num_eles = std::tuple_size<decltype(args_expanded_container)>::value;
		std::cout << "there's " << num_eles << " elements unpacked in the tuple" << std::endl;
		
		//we can't iterate over a tuple at runtime, but we can access elements at compile time; one may be able to write a macro that simulates iteration over a tuple at compile time
		//or one could possibly write a recursive constexpr chain
		std::cout << std::get<0>(args_expanded_container) << std::endl;
		std::cout << std::get<1>(args_expanded_container) << std::endl;
		std::cout << std::get<2>(args_expanded_container) << std::endl;

	}

	//-----------------------------------------------------

	template<typename T>
	void variadic_print(T item)
	{
		//this is an overload that only prints a single item
		//it acts as the base case for recursive print
		std::cout << item << std::endl;
	}

	template<typename PRINTNEXT, typename... Ts>
	void variadic_print(PRINTNEXT next, Ts... args)
	{
		std::cout << next << std::endl;

		//this will expand args, the first will be captured in next, the rest will be packaged up into args
		variadic_print(args...);
	}

	template<typename... Args>
	void print_driver(Args... args)
	{
		//just demoing how you can expand a pack into a function with a mixture signature
		variadic_print(args...);
	}

	//-----------------------------------------------------

	template <typename FIRST, typename SECOND>
	void make_pairs(FIRST p1, SECOND p2)
	{
		//basecase function
		std::cout << "PAIR\t" << p1 << "\t" << p2 << std::endl;
	}

	template <typename FIRST, typename SECOND, typename... Ts>
	void make_pairs(FIRST p1, SECOND p2, Ts... remaining)
	{
		make_pairs(p1, p2);			//call basecase function on first two
		make_pairs(remaining...);	//expand into next call, this will either be base case or a recursive call
	}

	//-----------------------------------------------------------
	template <typename T>
	T operation(T arg)
	{
		return arg * arg / 2;
	}

	template <typename T>
	double expand_function(T arg)
	{
		//base case
		return operation(arg);
	}
	
	template <typename T, typename... Ts>
	double expand_function(T item, Ts... remaining)
	{
		//recursive call
		return operation(item) + expand_function(operation(remaining)...);
	}

}

int main()
{
	variadic_function(5, 5.5, 'c');

	//variadic_print("hello", "there", "this", "is", "variadic", "print", 65, 'a', 333.33f, true, 45.0); 
	print_driver("hello", "there", "this", "is", "variadic", "print", 65, 'a', 333.33f, true, 45.0);

	make_pairs("1", 1, 2, "2", 3.3, "3.3", 4, '4', 4.5, 4.5f);

	std::cout << expand_function(1.0, 2.0, 3.0, 4.0) << std::endl;

	std::cin.get();
}