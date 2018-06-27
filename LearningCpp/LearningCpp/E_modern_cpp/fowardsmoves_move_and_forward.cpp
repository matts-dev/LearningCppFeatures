#include <iostream>


namespace
{
	class DemoT
	{
	public:
		DemoT() {};
		DemoT(const DemoT& copy) { std::cout << "copy ctor" << std::endl; };
		DemoT(DemoT&& move) { std::cout << "move ctor" << std::endl; };

		~DemoT() {};

		void work() { std::cout << "work" << std::endl; }
	};

	void foo(DemoT&& this_is_still_an_lvalue)
	{
		//this parameter is still an lvalue, so it will need to be cast! (either std::move or forward)
	}
}

//std::move and std::forward are casts (forward will be explained later), I've pasted their defintions below for reference

//MOVE DEFINTION
/*
template<class _Ty> inline constexpr 
typename remove_reference<_Ty>::type&& move(_Ty&& _Arg) _NOEXCEPT
{	// forward _Arg as movable
	return (static_cast<typename remove_reference<_Ty>::type&&>(_Arg));
}
*/

/*
//FORWARD DEFINTION (this uses reference collapsing to do a conditional cast, in a explained later .cpp)
template<class _Ty> inline
constexpr _Ty&& forward(
	typename remove_reference<_Ty>::type& _Arg) _NOEXCEPT
{	// forward an lvalue as either an lvalue or an rvalue
	return (static_cast<_Ty&&>(_Arg)); //oversimplification (as in, gist and not absolute truth) of how this works: if _TY = T&, then && & = &; if _TY = T (or T&& i think), then  then && && = && (or just &&)
}
*/

//REMOVE REFERENCE SPECIALIZATIONS
/*
template<class _Ty>
struct remove_reference
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct remove_reference<_Ty&>
{	// remove reference
	typedef _Ty type;
};

template<class _Ty>
struct remove_reference<_Ty&&>
{	// remove rvalue reference
	typedef _Ty type;
};
*/

template<typename T>
void bar(T& lvalue)
{
	std::cout << "lvalue" << std::endl;
}

template<typename T>
void bar(T&& rvalue)
{
	std::cout << "rvalue" << std::endl;
}

template<typename T>
void forward_Demo(T&& ref)
{
	bar(std::forward<T>(ref));
}

//FORWARD DEFINTION
int main()
{
	//you can't move from const objects because the move needs to modify the object 
	//(at least in practice, this isn't enforced, if you provide a move ctor with a const CLASS&& parameter, it will try to use that!)
	DemoT obj;
	DemoT obj2(std::move(obj));

	const DemoT ConstObj;
	DemoT Obj3(std::move(ConstObj));

	forward_Demo(obj);			//will call the lvalue bar
	forward_Demo(std::move(obj)); //will call the rvalue bar

	std::cin.get();
}