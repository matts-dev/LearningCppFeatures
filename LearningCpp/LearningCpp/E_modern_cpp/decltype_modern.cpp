#include<iostream>
#include <vector>

namespace
{

	void local_vars()
	{
		//decltype has different type deducing rules than template parameters (and thus auto).
		//where auto/template_parameters require the addition of reference symbols (and sometimes const modifiers), decltype does not
		//NOTE: the template_parameter/auto rules can be found in TEmplateTypeDeduction.cpp and AutoTypeDeduction.cpp

		int val = 5;
		int& ref = val;

		auto deduce1 = val;				//type: int
		decltype(ref) deduce2 = val;	//type: int&		//notice this is taking the type of ref, not of val!

		//we can get similar behavior for auto by introducing 
		auto& deduce0 = val;			//type: int&

		//we can force auto to use the decltype rules too! (if we're using cpp14)
		decltype(auto) cpp14_feature = ref;			//type: int&
		decltype(auto) cpp14_feature_gotcha = val;	//type: int		//this is because val is of type int!

		//essentially, the rules of decltype are: take the exact type of the lvalue! But there is one exception.
		//When an lvalue (such as val) is wrapped in parenthesis, it is still an lvalue.
		//However, if you use auto with a name wrapped in parenthesis, the deduced type is actually a reference to the lvalue type.
		//see below
		decltype(auto) as_expected = val;			//type: int
		decltype(auto) exception_to_rule = (val);   //type: int&
	}

	template <typename T, typename U>
	auto cpp11_trail_return(T a, U b) -> decltype(a - b)
	{
		//the trailing return type allows cpp to look up the type of the operator- for T and U!
		//it comes after the parameters so they're defined. 
		//Putting auto as the return type defers the type deduction until the trailing return type is evaluated.
		return a - b;
	}

	template <typename T, typename U>
	decltype(auto) cpp14_omits_trail(T a, U b) //we want to surround auto in decltype so that we use the decltype rules!
	{
		return (a - b);
	}

	void typededuction_in_functions()
	{
		auto value_cpp11 = cpp11_trail_return(5, 2.5); //type is deduced to double!
		auto value_cpp14 = cpp14_omits_trail(5, 2.5);  //type: double
	}


	//NOTE: accepting an rvalue and lvalue reference at the same time, is termed accepting universal references!
	template<typename A_Collection, typename Index>
	auto accept_r_and_l_values_cpp11(A_Collection&& c, Index i) -> decltype(c[i])
	{
		//by passing c as a reference, we cannot allow r values to be passed to the template function.
		//so, we pass by && because those will either be template instantiated to lvalue references, or rvalue references!
		//(see template type deduction)

		return c[i];
	}

	template<typename A_Collection, typename Index>
	decltype(auto) accept_r_and_l_values_cpp14(A_Collection&& c, Index i)
	{
		return c[i];
	}

	void accepting_rvalues_and_lvalues()
	{
		std::vector<float> collection;
		collection.push_back(4.1f);
		collection.push_back(2.5f);
		collection.push_back(3.3f);

		auto one = accept_r_and_l_values_cpp11(collection, 1); //accepting lvalue
		auto two = accept_r_and_l_values_cpp14(collection, 2); //accepting lvalue
		auto three = accept_r_and_l_values_cpp11(std::vector<int>(5, 4), 2); //accepting r value
		auto four = accept_r_and_l_values_cpp14(std::vector<int>(5, 4), 2); //accepting rvalues
	}
	
	template<typename A_Collection, typename Index>
	auto forward_universal_refs_cpp11(A_Collection&& c, Index i) -> decltype(std::forward<A_Collection>(c)[i])
	{
		//in general, foward universal refs and move rvalue refs
		return std::forward<A_Collection>(c)[i];
	}

	template<typename A_Collection, typename Index>
	decltype(auto) forward_universal_refs_cpp14(A_Collection&& c, Index i)
	{
		return std::forward<A_Collection>(c)[i];
	}

	void forwarding()
	{
		std::vector<float> collection;
		collection.push_back(4.1f);
		collection.push_back(2.5f);
		collection.push_back(3.3f);

		auto one = forward_universal_refs_cpp11(collection, 1); //accepting lvalue
		auto two = forward_universal_refs_cpp14(collection, 2); //accepting lvalue
		auto three = forward_universal_refs_cpp11(std::vector<int>(5, 4), 2); //accepting r value
		auto four = forward_universal_refs_cpp14(std::vector<int>(5, 4), 2); //accepting rvalues
	}

}; //end anyonomous namespace

static int main_v()
{
	local_vars();
	typededuction_in_functions();
	accepting_rvalues_and_lvalues();
	forwarding();

	std::cin.get();
}