#include<iostream>
#include <functional>
using namespace std::placeholders;

namespace
{
	struct TypeDemo
	{
	private:
		static int obj_count;
	public:
		int my_id;
		TypeDemo()
		{
			my_id = obj_count++;
		}

		TypeDemo(TypeDemo&& move) = delete; 
		TypeDemo(const TypeDemo& copy) = delete;
		TypeDemo& operator=(TypeDemo&& move) = delete;
		TypeDemo& operator=(const TypeDemo& copy) = delete;
	};
	int TypeDemo::obj_count = 0;


	void type_check(TypeDemo& Type, int specified_id)
	{
		if (Type.my_id == specified_id)
			std::cout << "the object matches the id" << std::endl;
		else 
			std::cout << "different IDS" << std::endl;
	}
}


static int main_v()
{
	{
		//show two equivalent ways of creating function objects, one through bind, the other through lambdas
		auto lambda_closure = [](TypeDemo& obj, int expected_id) {
			type_check(obj, expected_id);
		};

		auto bindobj = std::bind(
			type_check,
			_1,
			_2
		);

		// test the function objects
		TypeDemo first_obj;
		lambda_closure(first_obj, first_obj.my_id);
		bindobj(first_obj, first_obj.my_id);
	}

	//with bind, you have to remember to wrap bound objects in std::ref()
	{
		TypeDemo data;
		auto closure = [&data](int datas_source_id) {
			type_check(data, datas_source_id);
		};

		auto bindobj_incorrect = std::bind(
			type_check,
			std::ref(data),
			_1
		);

		closure(data.my_id);
		bindobj_incorrect(data.my_id);

	}

	//prefer lambda over bind,
	//1. lambdas are easier to read
	//2. lambdas allow you to specify how objects are bound
	//3. lambdas avoid weird timing issues, such as getting values from functions; the bind will get the value it needs from a function when the bind is created, however, function calls inside of the lambda will occur when the lambda is called.Getting around this requires nesting bind calls within a bind declaration itself.
	//4. bind objects have some caveats (such as std::ref) that you just have to memorize. 
	//5. c++14 allows you to do move lambda captures, which eliminates the need for std::bind in that case.
	//6. cpp14 allows you to have generic lambdas, which was previously an advantage of std::bind in cpp11
	std::cin.get();
}