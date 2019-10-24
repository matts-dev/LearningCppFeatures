#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <typeindex>
#include <set>


namespace
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Boilerplate code from project
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	template<typename T, typename... Args>
	sp<T> new_sp(Args&&... args)
	{
		if constexpr (std::is_base_of<GameEntity, T>::value)
		{
			sp<T> newObj = std::make_shared<T>(std::forward<Args>(args)...);
			//safe cast because of type-trait
			GameEntity* newGameEntity = static_cast<GameEntity*>(newObj.get());
			//newGameEntity->postConstruct();
			return newObj;
		}
		else
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
	}

	template<typename T, typename... Args>
	up<T> new_up(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	class GameEntity
	{
	public:
		virtual ~GameEntity() {} //add vtable
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Behavior tree memory that interally uses dynamic casts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct PrimitiveWrapper : public GameEntity
	{
		PrimitiveWrapper(T inValue) : value(inValue) {}
		T value;
	};


	////////////////////////////////////////////////////////
	// Memory just using dynamic casts to value check
	////////////////////////////////////////////////////////
	class Memory_JustDynamicCasts : public GameEntity
	{
		//hashmap of keys to values
		std::unordered_map<std::string, sp<GameEntity>> memory;

	public:
		template<typename T>
		T* getValueAs(const std::string& key)
		{
			auto findResult = memory.find(key);
			if (findResult != memory.end())
			{
				sp<GameEntity>& rawResult = findResult->second;
				if constexpr (std::is_base_of<GameEntity, T>())
				{
					//#optimize if dynamic casts become a problem, we can try storing typeid flags in a set so that further dynamic casts can be bypassed with static_casts
					return dynamic_cast<T*>(rawResult.get());
				}
				else
				{
					if (PrimitiveWrapper<T>* wrappedObj = dynamic_cast<PrimitiveWrapper<T>*>(rawResult.get()))
					{
						return &(wrappedObj->value);
					}
				}
			}
			return nullptr;
		}

		template<typename T>
		T* createValue(const std::string& key, const sp<T>& value)
		{
			static_assert(std::is_base_of<GameEntity, T>(), "Value must be of GameEntity. For primitive/integral values, use provided PrimitiveWrapper");
			memory.insert({ key, value });
			return value.get();
		}

		bool hasValue(const std::string& key)
		{
			return memory.find(key) != memory.end();
		}

		bool removeValue(const std::string& key)
		{
			return memory.erase(key) > 0;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// memory with RTTI optimization attempts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct EntryWrapper : public GameEntity
	{
		EntryWrapper(const sp<GameEntity>& inObj)
		{
			obj = inObj;
		}
		sp<GameEntity> obj;
		std::unordered_set<std::type_index> RTTI_Identifiers;
		//std::set<std::type_index> RTTI_Identifiers;
	};

	class Memory_Wrapper_JustDynamicCasts
	{
		//hashmap of keys to values
		std::unordered_map<std::string, sp<EntryWrapper>> memory;

	public:
		template<typename T>
		T* getValueAs(const std::string& key)
		{
			auto findResult = memory.find(key);
			if (findResult != memory.end())
			{
				sp<EntryWrapper>& entryWrapper = findResult->second;
				if constexpr (std::is_base_of<GameEntity, T>())
				{
					//#optimize if dynamic casts become a problem, we can try storing typeid flags in a set so that further dynamic casts can be bypassed with static_casts
					return dynamic_cast<T*>(entryWrapper->obj.get());
				}
				else
				{
					if (PrimitiveWrapper<T>* wrappedObj = dynamic_cast<PrimitiveWrapper<T>*>(entryWrapper->obj.get()))
					{
						return &(wrappedObj->value);
					}
				}
			}
			return nullptr;
		}

		template<typename T>
		T* createValue(const std::string& key, const sp<T>& value)
		{
			static_assert(std::is_base_of<GameEntity, T>(), "Value must be of GameEntity. For primitive/integral values, use provided PrimitiveWrapper");
			memory.insert({ key, new_sp<EntryWrapper>(value)});
			return value.get();
		}

		bool hasValue(const std::string& key)
		{
			return memory.find(key) != memory.end();
		}

		bool removeValue(const std::string& key)
		{
			return memory.erase(key) > 0;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Optimized memory that makes use of RTTI set`
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Memory_Wrapper_Optimized
	{
		//hashmap of keys to values
		std::unordered_map<std::string, sp<EntryWrapper>> memory;

	public:
		template<typename T>
		T* getValueAs(const std::string& key)
		{
			auto findResult = memory.find(key);
			if (findResult != memory.end())
			{
				sp<EntryWrapper>& entryWrapper = findResult->second;
				if constexpr (std::is_base_of<GameEntity, T>())
				{
					if (entryWrapper->RTTI_Identifiers.find(typeid(T)) != entryWrapper->RTTI_Identifiers.end())
					{
						//we found this rtti info about the object (each level of inheritance will have a different RTTI; which is why we need a set)
						return static_cast<T*>(entryWrapper->obj.get());
					}
					else
					{
						T* castObj = dynamic_cast<T*>(entryWrapper->obj.get());
						if (castObj)
						{
							entryWrapper->RTTI_Identifiers.insert(typeid(T));
						}
						return castObj;
					}
				}
				else
				{
					if (PrimitiveWrapper<T>* wrappedObj = dynamic_cast<PrimitiveWrapper<T>*>(entryWrapper->obj.get()))
					{
						return &(wrappedObj->value);
					}
				}
			}
			return nullptr;
		}

		template<typename T>
		T* createValue(const std::string& key, const sp<T>& value)
		{
			static_assert(std::is_base_of<GameEntity, T>(), "Value must be of GameEntity. For primitive/integral values, use provided PrimitiveWrapper");
			memory.insert({ key, new_sp<EntryWrapper>(value) });
			return value.get();
		}

		bool hasValue(const std::string& key)
		{
			return memory.find(key) != memory.end();
		}

		bool removeValue(const std::string& key)
		{
			return memory.erase(key) > 0;
		}
	};

	struct Base : public GameEntity
	{

	};

	struct Child : public Base
	{

	};

	struct GrandChild : public Child
	{
		int z = 0;
	};
}



void true_main()
{
	sp<Memory_JustDynamicCasts> rawCastMemory = new_sp<Memory_JustDynamicCasts>();
	sp<Memory_Wrapper_JustDynamicCasts> wrapperCastMemory = new_sp<Memory_Wrapper_JustDynamicCasts>();
	sp<Memory_Wrapper_Optimized> wrapperOptimizedMemory = new_sp<Memory_Wrapper_Optimized>();

	std::string myIntKey = "myInt";
	std::string myGrandChildKey = "myGrandChild";

	rawCastMemory->createValue(myIntKey, new_sp<PrimitiveWrapper<int>>(5));
	rawCastMemory->createValue(myGrandChildKey, new_sp<GrandChild>());

	wrapperCastMemory->createValue(myIntKey, new_sp<PrimitiveWrapper<int>>(5));
	wrapperCastMemory->createValue(myGrandChildKey, new_sp<GrandChild>());

	wrapperOptimizedMemory->createValue(myIntKey, new_sp<PrimitiveWrapper<int>>(5));
	wrapperOptimizedMemory->createValue(myGrandChildKey, new_sp<GrandChild>());

//happy path doesn't add failed rtti's ; should test optimizations around this if it turns out to be useful
#define PROFILE_HAPPY_PATH
#ifdef PROFILE_HAPPY_PATH
	int startProfileHere = 0;

	for (volatile int i = 0; i < 1000000; ++i)
	{
		if (int* myInt = rawCastMemory->getValueAs<int>(myIntKey))
		{
			++(*myInt);
		}
		if (GrandChild* grandChild = rawCastMemory->getValueAs<GrandChild>(myGrandChildKey))
		{
			++(grandChild->z);
		}
	}
	for (volatile int i = 0; i < 1000000; ++i)
	{
		if (int* myInt = wrapperCastMemory->getValueAs<int>(myIntKey))
		{
			++(*myInt);
		}
		if (GrandChild* grandChild = wrapperCastMemory->getValueAs<GrandChild>(myGrandChildKey))
		{
			++(grandChild->z);
		}
	}

	for (volatile int i = 0; i < 1000000; ++i)
	{
		if (int* myInt = wrapperOptimizedMemory->getValueAs<int>(myIntKey))
		{
			++(*myInt);
		}
		if (GrandChild* grandChild = wrapperOptimizedMemory->getValueAs<GrandChild>(myGrandChildKey))
		{
			++(grandChild->z);
		}
	}

	int intEndProfileHere = startProfileHere;
#endif //PROFILE_HAPPY_PATH


}

//
//int main()
//{
//	true_main();
//}