#include "..\Resources\shared_ptrs.h"
#include <unordered_map>
#include <typeindex>
#include <map>
#include "..\ProfileUtils\ScopedTiming.h"
#include <vector>
#include <random>

using namespace ProfilingTools;

namespace
{
	struct Base
	{
		virtual void virtualCallFunc() = 0;
		int value = 0;
	};

	struct A : public Base
	{
		virtual void virtualCallFunc() override
		{
			value++;
		}
		void functionOfA() { value--; }
	};

	struct B : public Base
	{
		virtual void virtualCallFunc() override
		{
			value--;
		}
	};
}


int main()
{
	std::vector<sp<Base>> sp_collection;
	std::vector<wp<Base>> wp_collection;
	std::vector<std::unique_ptr<Base>> up_collection;
	std::vector<Base*> raw_collection;

	

	size_t numElements 	= 
		10000000	//10mil
		//100000000	//100mil
	;
	std::vector<sp<Base>> copy_collection{ numElements };

	for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
	{
		sp<Base> newItem;
		if (elementIdx % 2 == 0)
		{
			newItem = new_sp<A>();
			up_collection.push_back(std::make_unique<A>());
		}
		else
		{
			newItem = new_sp<B>();
			up_collection.push_back(std::make_unique<B>());
		}
		sp_collection.push_back(newItem);
		wp_collection.push_back(newItem);
		raw_collection.push_back(newItem.get());
	}

	volatile int preventOptimization = 0;
	std::cout << preventOptimization << ": starting test; numElements: " << numElements << std::endl;

	preventOptimization++;

	{ScopedTimer perf("shared_ptr calling virtual function");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			sp_collection[elementIdx]->virtualCallFunc();
		}
	}

	{ScopedTimer perf("weak ptr lock and call virtual");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			wp<Base>& item = wp_collection[elementIdx];
			if (!item.expired())
			{
				item.lock()->virtualCallFunc();
			}
		}
	}

	{ScopedTimer perf("unique_ptr calling virtual function");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			up_collection[elementIdx]->virtualCallFunc();
		}
	}
	

	{ScopedTimer perf("raw ptr calling virtual function");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			raw_collection[elementIdx]->virtualCallFunc();
		}
	}

	{ScopedTimer perf("shared pointer copy (with array access)");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			copy_collection[elementIdx] = sp_collection[elementIdx];
		}
	}

	{ScopedTimer perf("dynamic cast reference");
		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		{
			if (A* aObj = dynamic_cast<A*>(sp_collection[elementIdx].get()))
			{
				aObj->functionOfA();
			}
		}
	} 

	std::cout << "ending test" << preventOptimization << std::endl;
}