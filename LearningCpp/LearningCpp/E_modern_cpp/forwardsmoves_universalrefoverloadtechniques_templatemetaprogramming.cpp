#include "log.h"
#include <type_traits>
#include <string>

namespace
{
	//NOTE: it's probably best to read the main function then come back to the top of the file and look at the implementations

	//PART 1: tag dispatch ------------------------------------------------------------------------------------------------------
	class TMPDemo
	{
	public:

	};

	template<typename T>
	void tag_demo_implementation(T&& param, std::false_type)
	{
		log("falsetype tag called!");
	}

	template<typename T>
	void tag_demo_implementation(T&& param, std::true_type)
	{
		log("truetype tag called!");
	}

	template<typename T>
	void tag_demo(T&& param)
	{
		//tag_demo_implementation(param, std::is_integral<T>()); //references are not considered to be integral types! this will cause int& to appear to be non-integral type
		tag_demo_implementation(param, std::is_integral<std::remove_reference<T>::type>()); //fix for references
	}


	//PART 2: enable_if ------------------------------------------------------------------------------------------------------

	//this is a start, but with references, we will have T and T& being passed to is_same, which will return  the false type.
	class TMP_ei
	{
	public:
		template
		<
			typename T, 
			typename = typename std::enable_if //disable some template instantiations via SFINAE
				<
					!std::is_same<TMP_ei, T>::value 
				>::type
		>
		explicit TMP_ei(T&& uni_ref) { log("uni ref ctor"); }
		explicit TMP_ei(const TMP_ei& copy) { log("copy ctor"); }
	};

	//this one is better, std::decay removes all references and cv qualifiers, think of it as std::remove_reference, but even stronger! (note: decay also decays arrays into pointers)
	class TMP_ei_better
	{
	public:
		template
			<
			typename T,
			typename = typename std::enable_if //SFINAE enabling of template instantiations under certain criteria
				<
					!std::is_same<TMP_ei_better, typename std::decay<T>::type>::value //treat references and nonreferences as teh same
				>::type
			>
			explicit TMP_ei_better(T&& uni_ref) { log("uni ref ctor"); }
			explicit TMP_ei_better(const TMP_ei_better& copy) { log("copy ctor"); }
	};

	class BaseClassBad : TMP_ei_better
	{
	public:
		BaseClassBad(int x) : TMP_ei_better(x) { /*irrelevant*/}
		BaseClassBad(const BaseClassBad& copy) : TMP_ei_better(copy) { log("child copy ctor"); } //passing "BaseClassBad" type to superclass ctor invokes universalref ctor, rather than copy ctor!
	};
	
	//fixes issues with inheritance
	class TMP_ei_inheritfix
	{
	public:
		template
			<
			typename T,
			typename = typename std::enable_if
				<
					!std::is_base_of	//note: if std::is_base_of<T, T> is true...; so this this meta returns true if the two are the same or the second is derived  from the first; we also put a ! in front of it all; effectively disabling any template instantiations of the same type and of a type that is derived.
					<
						TMP_ei_inheritfix,			
						typename std::decay<T>::type	//treat refereces and nonreferences as same
					>::value
				>::type
			>
			explicit TMP_ei_inheritfix(T&& uni_ref) { log("uni ref ctor"); }
			explicit TMP_ei_inheritfix(const TMP_ei_inheritfix& copy) { log("copy ctor"); }

	};

	class BaseClassGood : TMP_ei_inheritfix
	{
	public:
		BaseClassGood(int x) : TMP_ei_inheritfix(x) { /* irrelevant*/ }
		BaseClassGood(const BaseClassGood& copy) : TMP_ei_inheritfix(copy) { log("child copy ctor"); }
	};

	// ---------------------------------
	//I'm mostly showing this to show that you can use && in template metaprogramming
	class TMP_ei_best
	{
	public:
		template
		<
			typename T,
			typename = typename std::enable_if
			<
				!std::is_base_of	//note: if std::is_base_of<T, T> is true...; so this this meta returns true if the two are the same or the second is derived  from the first; we also put a ! in front of it all; effectively disabling any template instantiations of the same type and of a type that is derived.
				<
					TMP_ei_best,
					typename std::decay<T>::type	//treat refereces and nonreferences as same
				>::value
				&&
				!std::is_integral<std::remove_reference<T>>::value
			>::type
		>
		explicit TMP_ei_best(T&& uni_ref) { log("uni ref ctor"); }
		explicit TMP_ei_best(const TMP_ei_best& copy) { log("copy ctor"); }
		explicit TMP_ei_best(int x) { log("int ctor"); }
	};

	//--------------------------------- demo static_assert
	class TMP_staticassertdemo
	{
	public:
		template
		<
			typename T,
			typename = typename std::enable_if
			<
				!std::is_base_of	//note: if std::is_base_of<T, T> is true...; so this this meta returns true if the two are the same or the second is derived  from the first; we also put a ! in front of it all; effectively disabling any template instantiations of the same type and of a type that is derived.
				<
					TMP_staticassertdemo,
					typename std::decay<T>::type	//treat refereces and nonreferences as same
				>::value
				&&
				!std::is_integral<std::remove_reference<T>>::value
			>::type
		>
		explicit TMP_staticassertdemo(T&& uni_ref) { 
			//compile time assert!
			static_assert(std::is_constructible<std::string, T>::value,
				"this is how you can make more readable error messages, TMP error messages can get pretty nasty!");
			log("uni ref ctor");
		}
		explicit TMP_staticassertdemo(const TMP_staticassertdemo& copy) { log("copy ctor"); }
		explicit TMP_staticassertdemo(int x) { log("int ctor"); }
	};
}

static int main_v()
{
	//universal references are very greedy, especially when it comes to overloads (see forwardsmoves_avoidoverloadingonuniversalrefs.cpp).
	//however, there can be situations where overloading is necessary, and it is nice to overload on a function that takes a universal reference.
	//here are some approaches to overcoming the overloading of universal reference problem.

	//1. pass by const T&		: however, this isn't the most efficient because it can generate copies (such as passing cstring into a const string& parameter)
	//2. pass by value			: obviously this causes copying (the author notes that there are some cases where this can be optimized, but he discusses it later)
	//3. avoid overloading      : just use a slightly different name to avoid the universal reference from being called when it shouldn't (this is not possible to avoid with ctors!)
	//4. Tag dispatch (template meta programming technique)
	{
		tag_demo(6);
		tag_demo(TMPDemo());

		int primitive1;
		TMPDemo obj1;
		tag_demo(primitive1);
		tag_demo(obj1);
		log("");
	}
	//5. constraining templates instantiations with std::enable_if; that is, disable specific templates!
	{
		//by default, all possible templates are "enabled", which means they can be instantiated.
		//but you can disable certain template instantiations! This usings the enable_if Template meta programming (TMP) tool
		TMP_ei v1(5);
		TMP_ei v1_copy(v1); //no copy ctor... we're pasing a reference. T& != T
		log("------------------");

		TMP_ei_better v2(5);
		TMP_ei_better v2_copy(v2);  //yay copy ctor! we successfully disabled the universal reference instantiation that hijacks the copy ctor. :3 (but there's more work to be done! inheritance is still broken)
		log("");
		BaseClassBad v2_child(5);
		BaseClassBad v2_child_failcopy(v2_child);
		log("------------------");

		TMP_ei_inheritfix v3(5);
		TMP_ei_inheritfix v3_copy(v3);
		log("");

		BaseClassGood v3_child(5);
		BaseClassGood v3_copy_correctly_calls_super_copy(v3_child);

		log("------------------");
		TMP_ei_best v4(5);

		log("------------------");
		TMP_staticassertdemo("hi");
		TMP_staticassertdemo(5); //doesn't trigger universal reference, so doesn't hit static assert
		//TMP_staticassertdemo(5.0); //double triggers universal reference, and thus hits the static assert!
	}



	std::cin.get();
}
