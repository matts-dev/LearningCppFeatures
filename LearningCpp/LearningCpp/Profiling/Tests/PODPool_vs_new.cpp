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
#include "..\Resources\SA_Snapshot\SAGameEntity.h"
#include "..\Resources\SA_Snapshot\MultiDelegate.h"

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

	struct A_WithReleaseEvent : public SA::GameEntity
	{
		SA::MultiDelegate<A_WithReleaseEvent*> onReleaseToPool;

		void release()
		{
			onReleaseToPool.broadcast(this);
		}

	};

	template<typename T>
	struct Pool
	{
		Pool(size_t reserve)
		{
			available.reserve(reserve);
			//claimed.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}

		void makeNewInstance()
		{
			//real version should probably increase reserve amount in each container
			available.push_back(new_sp<T>());
		}

		sp<T> getInstance()
		{
			sp<T> back = available.back();
			available.pop_back();
			//claimed.push_back(back);
			return back;
		}

		void releaseInstance(sp<T>& ptr)
		{
			available.push_back(ptr);
		}

		std::vector<sp<T>> available;
		//std::vector<sp<T>> claimed;
	};

	template<typename T>
	struct RawPool
	{
		RawPool(size_t reserve)
		{
			available.reserve(reserve);
			//claimed.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}
		~RawPool()
		{
			for (size_t idx = 0; idx < available.size(); ++idx)
			{
				delete available[idx];
			}
		}

		void makeNewInstance()
		{
			//real version should probably increase reserve amount in each container
			available.push_back(new T{});
		}

		T* getInstance()
		{
			T* back = available.back();
			available.pop_back();
			return back;
		}

		void releaseInstance(T* ptr)
		{
			available.push_back(ptr);
		}

		std::vector<T*> available;
	};

	template<typename T>
	struct OptimizedPool
	{
		OptimizedPool(size_t reserve)
		{
			available.reserve(reserve);
			//claimed.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}

		void makeNewInstance()
		{
			//real version should probably increase reserve amount in each container
			available.push_back(new_sp<T>());
		}

		sp<T> getInstance()
		//sp<T>&& getInstance()
		{
			sp<T> back = available.back();
			available.pop_back();

			return back; 
			//return std::move(back); //moving a temporary is bad practice because it prevents RTO, I think
		}

		void releaseInstance(sp<T>&& ptr)
		{
			available.emplace_back(move(ptr));
		}

		std::vector<sp<T>> available;
		//std::vector<sp<T>> claimed;
	};


	//dangerous because this could accept a pointer it doesn't own.
	//it either needs to check if it owns the pointer(potential expensive) via a map
	//or it needs to use handles that can reference back to this pool and determine it owns the pointer
	template<typename T>
	struct PoolUnsafe
	{
		PoolUnsafe(size_t reserve)
		{
			available.reserve(reserve);
			owned.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}

		void makeNewInstance()
		{
			//real version should probably increase reserve amount in each container
			owned.push_back(new_sp<T>());
			available.push_back(owned.back().get());
		}

		T* getInstance()
		{
			T* back = available.back();
			available.pop_back();

			return back;
		}

		void releaseInstance(T* ptr)
		{
			//unsafe, needs to make sure that this pool owns the pointer; perhaps set?
			available.emplace_back(ptr);
		}

		std::vector<T*> available;
		std::vector<sp<T>> owned;
	};

	template<typename T, typename MAP_CONTAINER >
	struct PoolRawSafe
	{
		PoolRawSafe(size_t reserve)
		{
			available.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}

		void makeNewInstance()
		{
			//real version should probably increase reserve amount in each container
				
			sp<T> temp= new_sp<T>();
			fastOwnedLUT.insert({temp.get(), temp });
			available.push_back(temp.get());
		}

		T* getInstance()
		{
			T* back = available.back();
			available.pop_back();

			return back;
		}

		bool releaseInstance(T* ptr)
		{
			if (fastOwnedLUT.find(ptr) != fastOwnedLUT.end())
			{
				available.emplace_back(ptr);
				return true;
			}
			return false;
		}

		std::vector<T*> available;
		//MAP_CONTAINER<T*, sp<T> > fastOwnedLUT;
		MAP_CONTAINER fastOwnedLUT;
	};

	template<typename T>
	struct Pool_GameEntityWithRelease : public SA::GameEntity
	{
		size_t reserve;
		Pool_GameEntityWithRelease(size_t reserve)
		{
			this->reserve = reserve;

			//need to bind to delegates outside of constructor
			//available.reserve(reserve);
			//for (size_t idx = 0; idx < reserve; ++idx)
			//{
				//makeNewInstance();
			//}
		}

		virtual void postConstruct() 
		{
			available.reserve(reserve);
			owned.reserve(reserve);
			for (size_t idx = 0; idx < reserve; ++idx)
			{
				makeNewInstance();
			}
		}

		void makeNewInstance()
		{
			static_assert(std::is_base_of<A_WithReleaseEvent, T>::value, "Smart Subscribers must be GameEntity Objects.");

			//real version should probably increase reserve amount in each container
			sp<T> obj = SA::new_sp<T>();

			//obj->onReleaseToPool.addWeakObj(sp_this(), &Pool_GameEntityWithRelease<T>::handleRelease);
			obj->onReleaseToPool.addStrongObj(sp_this(), &Pool_GameEntityWithRelease<T>::handleRelease); //adding strong because this is very slow with Weak, but this does create a circular dependency, meaning these can never be cleaned up unless the pool clears its owned objects

			available.push_back(obj.get());
			owned.emplace_back(obj);
		}

		T* getInstance()
		{
			T* back = available.back();
			available.pop_back();

			return back;
		}

		void handleRelease(A_WithReleaseEvent* ptr)
		{
			releaseInstance(static_cast<T*>(ptr));
		}

		void releaseInstance(T* ptr)
		{
			available.push_back(ptr);
		}

		std::vector<T*> available;
		std::vector<sp<T>> owned;
	};

	void namedSizeTest(size_t numElements, std::map<std::string, std::vector<float>>& testResults)
	{
		std::vector<sp<Base>> smallArray_simple{ numElements };
		std::vector<sp<Base>> smallArray_rmif{ numElements };
		std::set<sp<Base>> treeSet;
		std::unordered_set<sp<Base>> hashSet;

		std::string testName = std::string(" ele: ") + std::to_string(numElements) + std::string(" = ");


		std::uniform_int_distribution<size_t> distribution(0, numElements - 1);
		std::seed_seq seed{ 1, 3,7,101, 27 };
		std::mt19937 rng_eng{ seed };


		std::vector<sp<A>> new_sp_ArrayOutput;
		new_sp_ArrayOutput.reserve(numElements);

		Pool<A> pool(numElements);
		std::vector<sp<A>> pool_ArrayOutput;
		pool_ArrayOutput.reserve(numElements);

		OptimizedPool<A> optPool(numElements);
		std::vector<sp<A>> optpool_ArrayOutput;
		optpool_ArrayOutput.reserve(numElements);

		PoolUnsafe<A> rawPoolBackShare(numElements);
		std::vector<A*> rawPoolBackShare_ArrayOutput;
		rawPoolBackShare_ArrayOutput.reserve(numElements);

		PoolRawSafe<A, std::map<A*, sp<A>>> rawPoolSafeMap(numElements);
		std::vector<A*> rawPoolSafeMap_ArrayOutput;
		rawPoolSafeMap_ArrayOutput.reserve(numElements);

		PoolRawSafe<A, std::unordered_map<A*, sp<A>>> rawPoolSafeHash(numElements);
		std::vector<A*> rawPoolSafeHash_ArrayOutput;
		rawPoolSafeHash_ArrayOutput.reserve(numElements);

		std::vector<A*> new_ArrayOutputTest;
		new_ArrayOutputTest.reserve(numElements);

		sp<Pool_GameEntityWithRelease<A_WithReleaseEvent>> eventPool = SA::new_sp<Pool_GameEntityWithRelease<A_WithReleaseEvent>>(numElements);
		std::vector<A_WithReleaseEvent*> eventPool_ArrayOutput;
		eventPool_ArrayOutput.reserve(numElements);

		RawPool<A> rawPool(numElements);
		std::vector<A*> rawPool_ArrayOutputTest;
		rawPool_ArrayOutputTest.reserve(numElements);


		const size_t numFetches = 4;
		volatile int preventOptimization = 0;
		//std::cout << preventOptimization << ": starting test; numElements: " << numElements << std::endl;

		//profile raw new delete
		{ScopedTimerOutput perf(testName + "raw new/delete", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					new_ArrayOutputTest.push_back(new A{});
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					delete new_ArrayOutputTest.back();
					new_ArrayOutputTest.pop_back();
				}
			}
		}

		//profile new_sp (make_shared)
		{ScopedTimerOutput perf(testName + "new_sp", testResults);
			for(volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				//request
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					new_sp_ArrayOutput.push_back(new_sp<A>());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					new_sp_ArrayOutput.pop_back();
				}
			}
		}

		//profile pool
		{ScopedTimerOutput perf(testName + "pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					pool_ArrayOutput.push_back(pool.getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					pool.releaseInstance(pool_ArrayOutput.back());
					pool_ArrayOutput.pop_back();
				}
			}
		}

		//profile move pool
		{ScopedTimerOutput perf(testName + "move optimized pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//could this be faster with emplace_back? might be cheating the test though. All need to emplace back if so. so I guess same difference? Perhaps not becaues raw new/delete temporaries don't have the overhead of copying a threadsafe control block
					optpool_ArrayOutput.push_back(std::move(optPool.getInstance()));
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					optPool.releaseInstance(std::move(optpool_ArrayOutput.back()));
					optpool_ArrayOutput.pop_back();
				}
			}
		}
		
		//profile share backed pool with raw access
		{ScopedTimerOutput perf(testName + "raw sp_back unsafe pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//could this be faster with emplace_back? might be cheating the test though. All need to emplace back if so. so I guess same difference? Perhaps not becaues raw new/delete temporaries don't have the overhead of copying a threadsafe control block
					rawPoolBackShare_ArrayOutput.push_back(rawPoolBackShare.getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					rawPoolBackShare.releaseInstance(rawPoolBackShare_ArrayOutput.back());
					rawPoolBackShare_ArrayOutput.pop_back();
				}
			}
		}

		//profile share backed pool with raw access using map LUT
		{ScopedTimerOutput perf(testName + "raw sp_back SAFE MAP pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//could this be faster with emplace_back? might be cheating the test though. All need to emplace back if so. so I guess same difference? Perhaps not becaues raw new/delete temporaries don't have the overhead of copying a threadsafe control block
					rawPoolSafeMap_ArrayOutput.push_back(rawPoolSafeMap.getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					rawPoolSafeMap.releaseInstance(rawPoolSafeMap_ArrayOutput.back());
					rawPoolSafeMap_ArrayOutput.pop_back();
				}
			}
		}

		//profile share backed pool with raw access using map LUT
		{ScopedTimerOutput perf(testName + "raw sp_back SAFE HASHMAP pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//could this be faster with emplace_back? might be cheating the test though. All need to emplace back if so. so I guess same difference? Perhaps not becaues raw new/delete temporaries don't have the overhead of copying a threadsafe control block
					rawPoolSafeHash_ArrayOutput.push_back(rawPoolSafeHash.getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					rawPoolSafeHash.releaseInstance(rawPoolSafeHash_ArrayOutput.back());
					rawPoolSafeHash_ArrayOutput.pop_back();
				}
			}
		}

		//profile profile event based pool
		{ScopedTimerOutput perf(testName + "raw event pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//could this be faster with emplace_back? might be cheating the test though. All need to emplace back if so. so I guess same difference? Perhaps not becaues raw new/delete temporaries don't have the overhead of copying a threadsafe control block
					eventPool_ArrayOutput.push_back(eventPool->getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					//releasing causes associated pool to intercept event, after this point the pointer must be discarded
					eventPool_ArrayOutput.back()->release();
					eventPool_ArrayOutput.pop_back();
				}
			}
		}

		//profile raw pool
		{ScopedTimerOutput perf(testName + "raw pool", testResults);
			for (volatile size_t fetch_push_pass = 0; fetch_push_pass < numFetches; ++fetch_push_pass)
			{
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					rawPool_ArrayOutputTest.push_back(rawPool.getInstance());
				}

				//release
				for (volatile size_t ele = 0; ele < numElements; ++ele)
				{
					rawPool.releaseInstance(rawPool_ArrayOutputTest.back());
					rawPool_ArrayOutputTest.pop_back();
				}
			}
		}
	}
}

//
//int main()
//{
//
//	std::cout << "starting test runs" << std::endl;
//
//	std::map<std::string, std::vector<float>> timings;
//
//	//DISCLAIMER: all of these tests are operating on shared pointers, which have overhead for copying/removing
//	//size_t numToAverage = 5000;
//	size_t numToAverage = 100;
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(3, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(6, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(9, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(10, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(30, timings); }
//	//for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(100, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(1000, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(10000, timings); }
//	for (size_t test = 0; test < numToAverage; ++test) { namedSizeTest(100000, timings); }
//
//
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