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
#include <string>

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

	
	void namedSizeTest(size_t numElements, std::map<std::string, std::vector<float>>& testResults)
	{
		std::vector<sp<Base>> smallArray_simple{ numElements };
		std::vector<sp<Base>> smallArray_rmif{ numElements };
		std::set<sp<Base>> treeSet;
		std::unordered_set<sp<Base>> hashSet;

		std::string testName = std::string(" ele: ") + std::to_string(numElements) + std::string(" = ");

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
		//std::cout << preventOptimization << ": starting test; numElements: " << numElements << std::endl;

		//profile removals
		{ScopedTimerOutput perf(testName + "1-simple_array_remove", testResults);
			for (volatile size_t ele = 0; ele < numElements; ++ele)
			{
				smallArray_simple.erase(std::find(smallArray_simple.begin(), smallArray_simple.end(), removeOrder[ele]));
			}
		} 

		{ScopedTimerOutput perf(testName+"2-remove_if array", testResults);
			for (volatile size_t ele = 0; ele < numElements; ++ele)
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

		{ScopedTimerOutput perf(testName+"3-treeset remove", testResults);
			for (volatile size_t ele = 0; ele < numElements; ++ele)
			{
				treeSet.erase(removeOrder[ele]);
			}
		}
		{ScopedTimerOutput perf(testName+"4-hashset_remove", testResults);
			for (volatile size_t ele = 0; ele < numElements; ++ele)
			{
				hashSet.erase(removeOrder[ele]);
			}
		}

		{ScopedTimerOutput perf(testName+"5-dynamic cast reference", testResults);
			for (volatile size_t elementIdx = 0; elementIdx < numElements; ++elementIdx)
			{
				if (A* aObj = dynamic_cast<A*>(removeOrder[elementIdx].get()))
				{
					aObj->virtualCallFunc();
				}
			}
		} 

		//std::cout << "------------------------------------------------------------" << preventOptimization << std::endl;
	}
}


//int main()
//{
//
//	std::cout << "starting test runs" << std::endl;
//
//	std::map<std::string, std::vector<float>> timings;
//
//	//DISCLAIMER: all of these tests are operating on shared pointers, which have overhead for copying/removing
//	//size_t numToAverage = 5000;
//	size_t numToAverage = 500;
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(3, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(6, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(9, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(10, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(30, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(100, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(1000, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(10000, timings); }
//	//sizeTest(100000);
//	//sizeTest(1000000); //too large
//
//	for (auto kv_pair : timings)
//	{
//		float average = 0.f;
//		uint32_t items = 0;
//		std::vector<float>& timingsArray = kv_pair.second;
//		for (size_t idx = 0; idx < timingsArray.size(); ++idx)
//		{
//			items++;
//			average += timingsArray[idx];
//		}
//		average = average / (float)items;
//
//		std::cout << kv_pair.first << " " << average << " ns" << std::endl;
//	}
//
//
//	std::cout << "ending test runs" << std::endl;
//}