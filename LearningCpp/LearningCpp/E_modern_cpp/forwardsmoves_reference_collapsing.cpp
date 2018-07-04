#include"log.h"

namespace rc
{
	class Type
	{
	public:
		void work() & { log("lvalue work overload"); } 
		void work() && { log("rvalue work overload"); } 
	};

	//adding const to a T&& by definition prevents it from being a forwarding reference (ie a universal reference)
	template<typename T> void func_explicit(const T&& rvalue) { log("rvalue deduced"); }
	template<typename T> void func_explicit(const T& lvalue) { log("lvalue deduced"); }

	template<typename T>
	void func_v(T&& uni_ref)
	{
		//ultimately makes the decision of which function to call by a conditional cast to lvalue or rvalue reference!
		//more on how this works...
		func_explicit(std::forward<T>(uni_ref));
	}

	void part2();
	void part3();
}

using namespace rc;
int main()
{
	Type lvalue;

	func_v(lvalue);
	func_v(Type{}); 

	//cpp11 adds rvalue_references, they're like lvalues references, but they can bind to temporary objects!
	Type& lvalue_ref = lvalue;	//legal
	Type&& rvalue_ref = Type{};     //legal
	 
	lvalue_ref.work();            // call the lvalue overload
	rvalue_ref.work();            // calls the lvalue overload too... this is because rvalue_ref itself is a lvalue... we can take its address!
	std::cout << "address is of rvalue ref means it is an lvalue! " << &rvalue_ref << std::endl; //this means that overloading on reference qualifiers doesn't take into account the reference type of the variable, it looks deep to see if your variable is a lvalue or rvalue; thus rvalue_refence still invokes the lvalue overload

	//std::move is effectively a cast that ALWAYS makes the compiler treat a value as an rvalue
	std::move(rvalue_ref).work(); //calls the rvalueoverload!
	std::move(lvalue_ref).work(); //wait... this also calls the rvalueoverload...

	//neverfear, there's a way to conditionally cast to rvalue or lvalue, and it is std::forward<T>
	//the decltype(var_name) reads the underlying type of the variable, which we need to specify in forwarding.
	std::forward<decltype(rvalue_ref)>(rvalue_ref).work();
	std::forward<decltype(lvalue_ref)>(lvalue_ref).work(); //this isn't really practical, but it shows that we can conditionally cast to an lvalue or rvalue; but how it does it do that? That's reference collapsing!


	//note: references to references_types are illegal in c++; they just become a reference to the type
	Type& ref_to_ref_qmark = lvalue_ref; //this is just a reference -- which this is intuitive to the programmer, but things become more complicated with templates

	//A template may deduce a reference to a reference type! ie, "T&& param" may instantiate to "type& && param"  or "Type&& && param"
	//This isn't legal code, so needs to make a decision about how to convert it; this decision is reference collapsing. There are 4 scenarios 
	//SCENARIO:			EVALUATION:
	//Type&& &&			Type&&
	//Type&& &			Type&
	//Type& &&			Type&
	//Type& &			Type&
	
	//Basically, this means if there is an lvalue reference in the type deduction, then reference collapse to a lvalue reference. 
	//Reference collapsing happens in 4 contexts: template instantiation, auto type deduction, decltype, and typedefs/aliases 
	{
		Type src{ };
		auto&& v1 = src;    //collapses to lvalue_reference
		auto&& v2 = Type{}; //collapses to rvalue_reference

		auto& v3 = src;		//collapses to lvalue_reference
		//auto& v4 = Type{};  //collapses to L-value reference; which doesn't compile because we cannot bind an lvalue reference to an rvalue

		//Type& v5 = Type{};  //remeber this doesn't compile
		const Type& v5 = Type{}; //but this does
	}

	//Reference collapsing is the basis for how std::forward deduces types; the template deduced types collapse to fill out a static cast!
	part2();
	part3();

	std::cin.get();
}
namespace rc
{


//This function will do collapsing!          (note, we probably would make this a constexpr in real code, but I'm trying not to distract from the reference collapsing functiuonality
template<typename REF_TYPE>
REF_TYPE&& my_forward(typename std::remove_reference<REF_TYPE>::type& param)
{
	return static_cast<REF_TYPE&&>(param);
}

/*
//lvalue instantiation: 
Type& my_forward(Type& param)
{
	return static_cast<Type&>(param);
}

//rvalue instantiation
Type&& my_forward(Type& param)
{
return static_cast<Type&&>(param);
}
*/

template<typename REF_TYPE>
REF_TYPE&&  my_forward_cpp14(std::remove_reference_t<REF_TYPE>& param)
{
	return static_cast<REF_TYPE&&>(param);
}

void part2()
{
	Type lvalue;
	Type& lvalue_ref = lvalue;
	Type&& rvalue_ref = Type{};

	log("");
	my_forward<decltype(lvalue_ref)>(lvalue_ref).work();
	my_forward<decltype(rvalue_ref)>(rvalue_ref).work();

	log("");
	my_forward_cpp14<decltype(lvalue_ref)>(lvalue_ref).work();
	my_forward_cpp14<decltype(rvalue_ref)>(rvalue_ref).work();

}

template<typename T>
struct TypedefExamples
{
	typedef T&& reference_collapsed_type;
	using reference_collapsed_type_v2 = T&&;
};

void part3()
{
	Type lvalue;
	Type& lvalue_ref = lvalue;
	Type&& rvalue_ref = Type{};

	//reference collapsing in typedefs/aliases 
	TypedefExamples<decltype(lvalue_ref)>::reference_collapsed_type	v1 = lvalue;	//collapses to lvalue (throws compile error when trying to bind to an rvalue)
	TypedefExamples<decltype(rvalue_ref)>::reference_collapsed_type	v2 = Type{};	//collapses to rvalue (will throw compile error if you try to bind an lvalue)
}

}