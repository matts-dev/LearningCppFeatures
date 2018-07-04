#include <iostream>
#include <string>

namespace
{
	class DemoTypeV
	{
	public:
		int x = 5;

	};

	void rvalue_only_param(DemoTypeV&& rvalue_type)
	{
		//this function will only accept rvalues, it will throw compile issues with lvalues
	}

	template <typename T>
	void universal_ref_param(T&& univeral_ref)
	{
		//this can accept both lvalue and rvalue references
	}

	//remember, there are cases where type deduction doesn't produce universal references 
	template <typename T>
	void edge_case_notUniversal(const T&& must_be_rvalue)
	{
		//this function is not a universal reference!
	}

	//example of when moving a universal reference goes wrong
	struct TypeV
	{
		DemoTypeV field;

		TypeV(){ std::cout << "no arg ctor " << std::endl; }
		TypeV(const TypeV& copy) { std::cout << "copy ctor " << std::endl; }
		TypeV(TypeV&& move) noexcept { std::cout << "move ctor " << std::endl; }
		TypeV& operator=(const TypeV& copy) { std::cout << "copy= " << std::endl; return *this; }
		TypeV& operator=(TypeV&& move) noexcept { std::cout << "move=" << std::endl; return *this;}
		~TypeV() = default;

		template <typename T>
		void setFieldUnsafe(T&& universal_type)
		{
			//always moves... even when we pass it an lvalue! Which is dangerous because it will wipe out the original lvalue
			field = std::move(universal_type);
		}

		template <typename T>
		void setFieldSafe(T&& universal_type)
		{
			//this will move when appropriate! and use lvalue to copy when appropriate!
			field = std::forward<T>(universal_type);
		}

		template <typename T>
		void work(T&& universal_type)
		{
			T obj = std::forward<T>(universal_type); //creates a reference if we pass an rvalue, creates a new object if we pass an rvalue
			auto obj2 = std::forward<T>(universal_type); //this will actually declare a non-reference
			obj.speak();
			obj2.speak();
		}
		void speak() { std::cout << ""; } // << std::endl; }

		template <typename T>
		void wait_to_forward(T&& universal_type)
		{
			std::cout << std::endl;

			//pretend we need to do some work with the universal_type... before we move it to the field we should pass it to functions as an lvalue!
			work(universal_type); //use as lvalue
			work(universal_type); //use as lvalue
			work(std::forward<T>( universal_type)); //use as lvalue or rvalue (this is the last time we use it, let it move if appropriate for the performance gain)
		}
	};


	TypeV effecientInternalMoveToParameter(TypeV&& rvalue_type, const TypeV& lvalue_type)
	{
		//we can do some operations and then move the result into the return value (Don't do this in situations without rvalues because of RVO (more on that in a moment)
		rvalue_type = lvalue_type; //copy, pretend there are more calculations based on the types, the book uses an example of matrix addition

		//return rvalue_type; //will call the copy ctor
		//instead of copying rvalue_type to the return value, move rvalue_type into the return value
		return std::move(rvalue_type); //will call the move ctor, a perf gain in many real work scenarios
	}

	template<class T>
	T efficient_forwarding_example(T&& arg)
	{
		return std::forward<T>(arg);
	}

	TypeV RVO_enabled()
	{
		std::cout << std::endl;
		//TypeV obj;
		//return obj; //surprisingly, this doesn't use RVO with MSVS

		return TypeV(); //only constructs one object, all the call site's return value
	}

	TypeV RVO_disabled()
	{
		std::cout << std::endl;

		return std::move(TypeV()); //constructs two objects, here and then makes a move to the call site's return value 
	}
}

static int main_v()
{
	//note: I will be moving from obj multiple times in these examples, which is abnormal, but since obj doesn't really have move semantics and it is useful to use a single variable for examples
	DemoTypeV obj;

	//param_type_rvalue_only(obj); //error: cannot bind rvalue reference to an lvalue
	rvalue_only_param(std::move(obj)); //error: cannot bind rvalue reference to an lvalue

	universal_ref_param(obj);
	universal_ref_param(std::move(obj));

	//edge_case_notUniversal(obj); //error: can't bind rvalue reference to an lvalue
	edge_case_notUniversal(std::move(obj));

	//NOTE:
	//always "MOVE" rvalue references
	//always "FORWARD" universal references

	//The way I remember this is, rvalues should stay rvalues; so cast them to rvalues with std::move.
	//since universal references can bind to lvalues or rvalues, that is, they're universal, 
	//		then we should respect what they originally were and use the conditional cast (ie forward) which conditionally casts to lvalue or rvalues references
	{
		DemoTypeV resouce_used_repeatedly;

		TypeV obj;
		obj.setFieldUnsafe(resouce_used_repeatedly); //wipes out resouce...

		TypeV obj2;
		obj2.setFieldUnsafe(resouce_used_repeatedly); //uh-oh, this will cause a move from a wiped out (ie previously moved) resource
	}

	{
		DemoTypeV resouce_used_repeatedly;

		TypeV obj;
		obj.setFieldSafe(resouce_used_repeatedly); 

		TypeV obj2;
		obj2.setFieldSafe(std::move(resouce_used_repeatedly)); 
	}
	{
		TypeV resource;
		TypeV obj;
		obj.wait_to_forward(resource); //will do all copies!
		obj.wait_to_forward(std::move(resource)); //will do a move in the end
	}
	{
		DemoTypeV resource;
		resource.x = 100;
		TypeV source;
		source.field = resource;

		std::cout << std::endl;
		TypeV result = effecientInternalMoveToParameter(TypeV(), source);

		//forwarding has same behavior with template
		std::cout << std::endl;
		//TypeV result1 = effecientInternalForwardToParameter(TypeV(), source);

		//forwarding allows lvalue version to work too
		std::cout << std::endl;
		TypeV result2 = efficient_forwarding_example(source);
		TypeV result3 = efficient_forwarding_example(std::move(source));

		//note: by typing <type>, you remove the ability for a function to take universal references
		//efficient_forwarding_example<TypeV>(source);
	}

	{
		//reminder, RVO just prevents making a copy when returning (ie it does copy elision), so it is a speed up.

		//avoiding limiting RVO:
		auto obj1 = RVO_enabled();
		auto obj2 = RVO_disabled();

		//Return Value Optimization (RVO) requires 2 things:
		//	1. the local object is same type that is returned by function
		//  2. the local object is returned
		//  (3. the local object can't be a parameter, because a parameter could be dtored by the caller, and if it is optimized to be the return value, the return value will be destroyed when the parameter is!)

		//When dealing with universal references, you want to forward return values for efficiency, but doing this in other places will destroy your RVO capabilities. Which is why you shouldn't write code like RVO_disabled
		//note: if the compiler can't use RVO, it defaults to moving, which makes extra attempts for moving return values superfluous, because it is done anyways! 
		//	So by adding std::move, you never gain a move (it will do it anyways),but you do lose the ability of automatically getting RVO)
	}

	return 0;
}