#include<iostream>
#include <unordered_map>
#include <memory>
#include <type_traits>

namespace
{
	void func(int x) { std::cout << "hello world: " << x << std::endl; }


	struct M
	{
		int x;
		M() { x = counter++; }
	private:
		static int counter;
	};

	struct K
	{
	};

	int M::counter = 0; //initializing static member must be done outside of class
}

template<typename T>
using sp_ud = std::shared_ptr<T>;

//template<typename T>
//typedef std::shared_ptr<T> type; //error c2823: a typedef template is illegal

template<typename T>
struct sp_td		//work around for getting a template typedef (c++98)
{
	typedef std::shared_ptr<T> type;
};


template <typename T>
class PointerManager
{
public:
	//using an old typedef in a class requires use of typename!
	//this is a "dependent type" because ::type ultimately depends on T, 
	//specializations of sp_td<T> may redefine ::type to actually be a variable... so we must enforce it is a type with typename
	typename sp_td<T>::type old_style;
	sp_ud<T> new_style;
	//the using declarations (ie sp_ud<T>) can only ever be a type, (because 'using' can't be used with variables)
	//so it is not a dependent type, but rather it is a non-dependent type of T, because it can only ever name a type! so we don't need typename.
};

//demoing a specialization that redefines ::type!
template<>
struct sp_td<K>
{
	//this will contradict the typedef in PointerManager, and is why compilers require you type "typename" before the template dependent types.
	int type = -1;
};

//type_traits allow declaring some types useful in metaprogramming, they're interesting because cpp11 didn't define them with using declarations, despite type traits being introduced in cpp11
template<typename T>
void meta_programming_utils(T arg)
{
	//cpp11 actually uses the old typedef way of defining types!
	std::remove_reference<T>::type no_ref; // T from T& (or T&&)
	std::remove_const<T>::type no_const;
	std::add_lvalue_reference<T>::type lvalue_ref = arg;

	//cpp14 uses using declarations instead of typedefs, but you need to append a _t
	std::remove_reference_t<T> no_ref2; // T from T& (or T&&)
	std::remove_const_t<T> no_const2;
	std::add_lvalue_reference_t<T> lvalue_ref2 = arg;
}

int main()
{
	typedef std::unordered_map<std::string, int> WordCountMap_td; //old c++ 98 typedef
	using WordCountMap_ud = std::unordered_map<std::string, int>; //using declaration
	
	//examples using simplified types
	WordCountMap_td map0; 
	WordCountMap_ud map1;

	//function pointers are more readable with using declarations
	typedef void(*fptr1_t)(int);
	using fptr2_t = void(*)(int);

	fptr1_t ptr1 = &func;
	fptr2_t ptr2 = &func;
	ptr1(1);
	ptr2(2);

	// alias declarations can be templatized, where as typedefs require wrapping in struct to introduce typename T
	// look in global space above
	sp_ud<M> smart_ptr1 = std::make_shared<M>();
	sp_td<M>::type smart_ptr2 = std::make_shared<M>();
		
	PointerManager<M> MManager;
	MManager.old_style = std::make_shared<M>(); //VAX plugin gets confused on variable names even when typename is used
	MManager.new_style = std::make_shared<M>();

	//PointerManager<K> KManager; //errors because ...::type is redefined in a specialization for the class K!
	//KManager.old_style = std::make_shared<K>(); //this gives an error! because we have specialized this to be a variable name in sp_td<int>! error C3646: 'old_style': unknown override specifier
	//KManager.new_style = std::make_shared<K>();

	
	meta_programming_utils(std::move(M{}));

	std::cin.get();
}