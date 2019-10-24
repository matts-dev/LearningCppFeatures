#pragma once
#include <memory>

namespace ProfilingTools
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//These forward declarations are carefully placed here to avoid circle includes.
	//new_sp is desired to be responsible for calling post construct, and therefore 
	//needs to know of the type "GameEntity". So that file will include "GameEntity"
	//However, game entity needs to know the smart pointer aliases to friend them, 
	//hence the forward declarations
	//
	//Note, Some of below are the real type aliases (eg see sp)

	//shared pointer
	template<typename T>
	using sp = std::shared_ptr<T>;

	template<typename T, typename... Args>
	sp<T> new_sp(Args&&... args);

	//weak pointer
	template<typename T>
	using wp = std::weak_ptr<T>;

	//unique pointer
	template<typename T>
	using up = std::unique_ptr<T>;

	template<typename T, typename... Args>
	up<T> new_up(Args&&... args);
	///////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Usage example
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	int main(){
		using namespace SA;

		//shared pointer
		sp<EG_Class> ptr2 = new_sp<EG_Class>();
		ptr2->Foo();

		//weak pointer
		wp<EG_Class> wp1 = ptr2;
		if (sp<EG_Class> aquired = wp1.lock())
		{
			aquired->Foo();
		}

		//unique pointer
		up<EG_Class> up1 = new_up<EG_Class>();
		up1->Foo();
	}
	*/

	template<typename T, typename... Args>
	sp<T> new_sp(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	up<T> new_up(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}