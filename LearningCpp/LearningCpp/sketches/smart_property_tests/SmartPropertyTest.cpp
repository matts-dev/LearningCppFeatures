
#include<iostream>

namespace
{
	template<typename T>
	class smart_property
	{
	public:
		smart_property(void* owner, T&& value)
			: value(value), owner(owner)
		{
			//registers with the singleton that has hashmap that is keyed off of pointer to owner
			//get singtleton
			//request object with 'this' key
			//add property to list of properties of object
		}

		~smart_property()
		{
			//get singleton
			//get struct for the owner of this property
			//remove from the list this particular property
			//if property is last in list, delete structure from hashmap.
		}

		//accessor/mutator
		void set(const T& newValue) { 
			dirty = true;
			value = newValue;
		}
		const T& get() { return value; }

	private:
		T value;
		bool dirty = false;
		void* owner;

	};

	struct Demo
	{
		smart_property<int> x;
		smart_property<int> y;
		smart_property<int> z;

		Demo() : x(this, 5), y(this, 6), z(this, 7)
		{
		}
	};

	int true_main()
	{
		Demo obj;

		std::cin.get();
		return 0;
	}
}

//int main()
//{
//	true_main();
//}
