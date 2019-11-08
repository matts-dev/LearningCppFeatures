#include "..\Resources\shared_ptrs.h"
#include <unordered_map>
#include <typeindex>
#include <map>
#include "..\ProfileUtils\ScopedTiming.h"
#include <vector>
#include <random>
#include <set>
#include <unordered_set>
#include <algorithm>

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

	void sizeTest(size_t numElements)
	{
		std::vector<sp<Base>> smallArray_simple{ numElements };
		std::vector<sp<Base>> smallArray_rmif{ numElements };
		std::set<sp<Base>> treeSet;
		std::unordered_set<sp<Base>> hashSet;

		std::vector<sp<Base>> removeOrder;
		for (size_t ele = 0; ele < numElements; ++ele)
		{
			sp<Base> item = new_sp<A>();
			removeOrder.push_back(item);
			smallArray_rmif.push_back(item);
			smallArray_simple.push_back(item);
			treeSet.insert(item);
			hashSet.insert(item);
		}

		std::uniform_int_distribution<size_t> distribution(0, numElements - 1);
		std::seed_seq seed{ 1, 3,7,101, 27 };
		std::mt19937 rng_eng{ seed };

		//randomize the ordering of the remove order
		for (size_t ele = 0; ele < numElements; ++ele)
		{
			size_t swapIdx = distribution(rng_eng);
			sp<Base> swapTarget = removeOrder[swapIdx];
			removeOrder[swapIdx] = removeOrder[ele];
			removeOrder[ele] = swapTarget;
		}

		volatile int preventOptimization = 0;
		std::cout << preventOptimization << ": starting test; numElements: " << numElements << std::endl;

		//profile removals
		{NanoScopedTimer perf("simple_array_remove");
			for (size_t ele = 0; ele < numElements; ++ele)
			{
				smallArray_simple.erase(std::find(smallArray_simple.begin(), smallArray_simple.end(), removeOrder[ele]));
			}
		} 

		{NanoScopedTimer perf("remove_if array");
			for (size_t ele = 0; ele < numElements; ++ele)
			{
				Base* target = removeOrder[ele].get();
				smallArray_rmif.erase(
					std::remove_if(
						smallArray_rmif.begin(),
						smallArray_rmif.end(),
						[target](const sp<Base>& item) {return item.get() == target; })
					, smallArray_rmif.end());
			}
		}

		{NanoScopedTimer perf("treeset remove");
			for (size_t ele = 0; ele < numElements; ++ele)
			{
				treeSet.erase(removeOrder[ele]);
			}
		}
		{NanoScopedTimer perf("hashset_remove");
			for (size_t ele = 0; ele < numElements; ++ele)
			{
				hashSet.erase(removeOrder[ele]);
			}
		}


		//	{NanoScopedTimer perf("dynamic cast reference");
		//		for (size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
		//		{
		//			if (A* aObj = dynamic_cast<A*>(sp_collection[elementIdx].get()))
		//			{
		//				aObj->functionOfA();
		//			}
		//		}
		//	} 


		std::cout << "------------------------------------------------------------" << preventOptimization << std::endl;
	}
}


//int main()
//{
//
//	std::cout << "starting test runs" << std::endl;
//
//	//DISCLAIMER: all of these tests are operating on shared pointers, which have overhead for copying/removing
//	sizeTest(3);
//	sizeTest(10);
//	sizeTest(30);
//	sizeTest(100);
//	sizeTest(1000);
//	sizeTest(10000);
//	//sizeTest(100000);
//	//sizeTest(1000000); //too large
//
//	std::cout << "ending test runs" << std::endl;
//}