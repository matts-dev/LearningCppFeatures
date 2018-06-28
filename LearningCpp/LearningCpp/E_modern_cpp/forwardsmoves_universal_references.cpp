#include<iostream>
#include <vector>

namespace
{
	class Exp
	{
	public:

	};

	//universal references are only applicable where types must be deduced!
	//universal references are not really a thing, they're just a convenient name for references that will undergo reference collapsing.

	//rvalue references
	void funcv(Exp&& rvalue_ref){}				//no type deduction
	Exp&& rvalue_ref = Exp();					//no type deduction
	template<typename T>		void funv(std::vector<T>&& rvalue_ref) {} //no type deduction

	//universal references (ie forwarding references)
	template<typename T>		void funv(T&& universal_ref) {}
	auto&& universal_ref = Exp();

	void functionv(Exp&& rvalue)
	{
		std::cout << "r-value function" << std::endl;
	}
	void functionv(Exp& lvalue)
	{
		std::cout << "l-value function" << std::endl;
	}

	template <typename T>
	void determine_ref_type(T&& universal_reftype)
	{
		//have template figure out which function to call!
		//this isn't the best example because it requires a forward (since technically all parameters are lvalue references)
		//really, the type is encoded in T, which std::foward leverages reference collapsing to cast the universal_ref to what ever it's original reference type was
		//for this item, look at the examples that will not compile when using lvalues, because those are cases where templates do not become universal references, but instead become rvalue references
		functionv(std::forward<T>(universal_reftype));
	}

	template <typename T>
	void const_changes_to_rvalue_notuniversalref(const T&& rvaluereftype)
	{
		//try compiling this with an lvalue
	}

	template <typename T>
	class DeduceAtInstantiate
	{
	public:
		void no_type_deduced(const T&& rvaluereftype)
		{
			//try compiling this with lvalue...
		}
		
		//note: this also workswith packed arguments (ie Args&&... args) as in std::vector's emplace back
		template<typename Arg>
		void deduced_type(Arg&& universalref_because_unrelated_to_T)
		{
			//try compiling this with an lvalue, it will work!
		}
	};


	
}


int main()
{
	//universal references can determine whether they're looking at an rvalue reference or an lvalue reference
	Exp obj;
	determine_ref_type(obj);			//should call lvalue function internally
	determine_ref_type(std::move(obj)); //should call rvalue function internally
	std::cout << "Hello world" << std::endl;

	//const_changes_to_rvalue_notuniversalref(obj);
	DeduceAtInstantiate<Exp> templateclassobj;
	//templateclassobj.no_type_deduced(obj); //cannlot bind lvalue reference to rvalue reference
	templateclassobj.deduced_type(obj); //accepts unviersal reference, so this will compile!


	//cpp14 leverages the fact that auto&& can be used in lambda parameters, which can become an universal reference
	auto lambda = [](auto&& universal_ref) {
		//basically: look at the type of universal ref(with decltype) and see if that is an lvalue
		if (std::is_lvalue_reference<decltype(universal_ref)>::value)
			std::cout << "lvalue ref" << std::endl;
		else
			std::cout << "rvalue ref" << std::endl;
	};

	lambda(obj);
	lambda(std::move(obj));

	//note, the templates that determine if something is an rvalue_reference or lvalue_reference work by defining only the correct type to be true, and provide a catch-all else to be defined as false (which happens to use a non-reference)
	auto&& rval_ref = std::move(obj);
	if (std::is_rvalue_reference<decltype(rval_ref)>::value)
	{
		std::cout << "the auto evaluates to a rvalue" << std::endl;
	}
	else
	{
		std::cout << "the auto evaluates to a lvalue" << std::endl;
	}

	//for reference:
	/*
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

		// TEMPLATE CLASS is_lvalue_reference
template<class _Ty>
	struct is_lvalue_reference
		: false_type
	{	// determine whether _Ty is an lvalue reference
	};

template<class _Ty>
	struct is_lvalue_reference<_Ty&>
		: true_type
	{	// determine whether _Ty is an lvalue reference
	};

	// TEMPLATE CLASS is_rvalue_reference
template<class _Ty>
	struct is_rvalue_reference
		: false_type
	{	// determine whether _Ty is an rvalue reference
	};

template<class _Ty>
	struct is_rvalue_reference<_Ty&&>
		: true_type
	{	// determine whether _Ty is an rvalue reference
	};

	*/

	std::cin.get();
}