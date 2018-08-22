//a little experiment with some smart pointer typedefs (actually usings) to make code less verbose. This may not be a good practice.
#include <memory>
#include <string>
#include <iostream>
#include <stdlib.h>

//option 1 for shared pointers
template<typename T>
using sp = std::shared_ptr<T>;

template<typename T>
const auto new_sp = std::make_shared<T>;

//option 2 for shared pointers
template<typename T>
using sptr = std::shared_ptr<T>;

template<typename T>
const auto new_sptr = std::make_shared<T>;

//weak pointers
template<typename T>
using wp = std::weak_ptr<T>;

//unique pointers
template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using up = std::unique_ptr<T>;

template<typename T>
const auto new_up = std::make_unique<T>;




//functions from this
template<typename T>
const auto shared_this = std::shared_from_this;

template<typename T>
const auto weak_this = std::weak_from_this;

namespace{
	class EG_Class
	{
	public:
		void doWork() const
		{
			
		}
	};

	void true_main()
	{
		//I feel like I like below the best
		sp<EG_Class> ptr2 = new_sp<EG_Class>();
		ptr2->doWork();

		//second best
		sptr<EG_Class> ptr0 = new_sp<EG_Class>();
		ptr0->doWork();

		sptr<EG_Class> ptr1 = new_sptr<EG_Class>();
		ptr1->doWork();


		wp<EG_Class> wp1 = ptr2;
		if (sp<EG_Class> aquired = wp1.lock())
		{
			aquired->doWork();
		}

		up<EG_Class> up1 = new_up<EG_Class>();
		up1->doWork();
	}
}


int main()
{
	true_main();
	std::cin.get();
}