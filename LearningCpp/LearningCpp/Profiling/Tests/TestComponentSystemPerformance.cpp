#include "..\Resources\shared_ptrs.h"
#include <unordered_map>
#include <typeindex>
#include <map>
#include "..\ProfileUtils\ScopedTiming.h"
#include <vector>
#include <random>

using namespace ProfilingTools;

template<typename T, typename... Args>
sp<T> new_comp(Args&&... args)
{
	sp<T> comp = std::make_shared<T>(std::forward<Args>(args)...);
	comp->postConstruct();
	return comp;
}

namespace
{
	class Component
	{
	public:
		virtual ~Component(){}

		void doSomething() volatile { preventOptimize++; }
		void postConstruct() 
		{
			//std::cout << typeid(*this).name() << std::endl;
		};

		volatile int preventOptimize = 0;
	};

	class A_Component : public Component {};
	class B_Component : public Component {};
	class C_Component : public Component {};
	class D_Component : public Component {};
	class E_Component : public Component {};
	class F_Component : public Component {};
	class G_Component : public Component {};
	class H_Component : public Component {};
	class I_Component : public Component {};
	class J_Component : public Component {};
	class K_Component : public Component {};
	class L_Component : public Component {};
	class M_Component : public Component {};
	class N_Component : public Component {};
	class O_Component : public Component {};
	class P_Component : public Component {};
	class Q_Component : public Component {};
	class R_Component : public Component {};
	class S_Component : public Component {};
	class T_Component : public Component {};
	class U_Component : public Component {};
	class V_Component : public Component {};
	class W_Component : public Component {};
	class X_Component : public Component {};
	class Y_Component : public Component {};
	class Z_Component : public Component {};

	template <typename CONTAINER>
	class ComponentManager
	{
	public:
		template<typename ComponentType>
		void createComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);

			//have this template cache type_index since typeid may call virtual dispatch
			static std::type_index typeIndex = typeid(ComponentType);

			if (components.find(typeIndex) == components.end())
			{
				const sp<ComponentType>& component = new_comp<ComponentType>();
				//component->setOwner
				components.insert({ typeIndex, component });
			}
			else
			{
				//already created component of type, this should not be happening!
				//log/crash/do_something this shouldn't happen
			}
		}

		template<typename ComponentType>
		void deleteComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			static std::type_index typeIndex = typeid(ComponentType);

			auto findResult = components.find(typeIndex);
			if (findResult != components.end())
			{
				components.erase(findResult);
			}
			else
			{
				//trying to delete an already deleted component... 
				//log/crash/do_something this shouldn't happen
			}
		}

		template<typename ComponentType>
		bool hasComponent() const
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			static std::type_index typeIndex = typeid(ComponentType);

			return components.find(typeIndex) != components.end();
		}

		template<typename ComponentType>
		ComponentType* getComponent() //TODO if used properly set up const and non const versions of this
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			static std::type_index typeIndex = typeid(ComponentType);

			auto findResult = components.find(typeIndex);
			if (findResult != components.end())
			{
				//static cast is safe since we've verified the type_index
				return static_cast<ComponentType*>(findResult->second.get());
			}
			else
			{
				return nullptr;
			}
		}

	private:
		CONTAINER components;
		//std::unordered_map<std::type_index, sp<Component>> components;
	};

	class ComponentManager_ArrayLookup
	{
		static size_t nextIndex;
		std::vector<sp<Component>> components;

		enum class ComponentOp {GET, CREATE, DELETE};
		template<typename ComponentType>
		inline ComponentType* _componentOperation(ComponentOp operation)
		{
			//this will create many different functions that automatically know the index of the type
			//operations all live in the same function so that the this_type_index is always the same

			static_assert(std::is_base_of<Component, ComponentType>::value);
			static size_t this_type_index = nextIndex++; //first time this is called, it gets a new index for fast compile time lookup

			if (components.size() < this_type_index + 1)
			{
				components.resize(this_type_index + 1, nullptr);
			}

			ComponentType* ret = nullptr;

			//avoid switch because I heard they suck with cache... probably should try and test that.
			if (operation == ComponentOp::GET)
			{
				//static cast is safe since we're using index look up as a proxy for RTTI
				ret = static_cast<ComponentType*>(components[this_type_index].get());
			}
			else if (operation == ComponentOp::CREATE)
			{
				if (components[this_type_index] == nullptr)
				{
					components[this_type_index] = new_comp<ComponentType>();
					ret = static_cast<ComponentType*>(components[this_type_index].get());
				}
				else
				{
					//crash log or do something
				}
			}
			else if (operation == ComponentOp::DELETE)
			{
				if (sp<Component>& comp = components[this_type_index])
				{
					components[this_type_index] = nullptr;
				}
				else
				{
					//component didn't exist, why is this person trying to delete it?
					//crash, log, or do something
				}
			}
			return ret;
		}

	public:

		template<typename ComponentType>
		void createComponent()
		{

			static_assert(std::is_base_of<Component, ComponentType>::value);
			_componentOperation<ComponentType>(ComponentOp::CREATE);
		}

		template<typename ComponentType>
		void deleteComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			_componentOperation<ComponentType>(ComponentOp::DELETE);

		}

		template<typename ComponentType>
		bool hasComponent() const
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			return _componentOperation<ComponentType>(ComponentOp::GET) != nullptr;
		}

		template<typename ComponentType>
		ComponentType* getComponent() //TODO if used properly set up const and non const versions of this
		{
			static_assert(std::is_base_of<Component, ComponentType>::value);
			return _componentOperation<ComponentType>(ComponentOp::GET);
		}
	};
	/*static*/ size_t ComponentManager_ArrayLookup::nextIndex = 0; //TODO if this is used, don't paste it in the header file!

	template<typename CONTAINER>
	void createComponents(ComponentManager<CONTAINER>& container)
	{
		container.createComponent<A_Component>();
		container.createComponent<B_Component>();
		container.createComponent<C_Component>();
		container.createComponent<D_Component>();
		container.createComponent<E_Component>();
		container.createComponent<F_Component>();
		container.createComponent<G_Component>();
		container.createComponent<H_Component>();
		container.createComponent<I_Component>();
		container.createComponent<J_Component>();
		container.createComponent<K_Component>();
		container.createComponent<L_Component>();
		container.createComponent<M_Component>();
		container.createComponent<N_Component>();
		container.createComponent<O_Component>();
		container.createComponent<P_Component>();
		container.createComponent<Q_Component>();
		container.createComponent<R_Component>();
		container.createComponent<S_Component>();
		container.createComponent<T_Component>();
		container.createComponent<U_Component>();
		container.createComponent<V_Component>();
		container.createComponent<W_Component>();
		container.createComponent<X_Component>();
		container.createComponent<Y_Component>();
		container.createComponent<Z_Component>();

	}

	void createComponents(ComponentManager_ArrayLookup& container)
	{
		container.createComponent<A_Component>();
		container.createComponent<B_Component>();
		container.createComponent<C_Component>();
		container.createComponent<D_Component>();
		container.createComponent<E_Component>();
		container.createComponent<F_Component>();
		container.createComponent<G_Component>();
		container.createComponent<H_Component>();
		container.createComponent<I_Component>();
		container.createComponent<J_Component>();
		container.createComponent<K_Component>();
		container.createComponent<L_Component>();
		container.createComponent<M_Component>();
		container.createComponent<N_Component>();
		container.createComponent<O_Component>();
		container.createComponent<P_Component>();
		container.createComponent<Q_Component>();
		container.createComponent<R_Component>();
		container.createComponent<S_Component>();
		container.createComponent<T_Component>();
		container.createComponent<U_Component>();
		container.createComponent<V_Component>();
		container.createComponent<W_Component>();
		container.createComponent<X_Component>();
		container.createComponent<Y_Component>();
		container.createComponent<Z_Component>();

	}

	std::vector<sp<Component>> createArrayOfComponents()
	{
		std::vector<sp<Component>> componentArray =
		{
			new_comp<A_Component>(),
			new_comp<B_Component>(),
			new_comp<C_Component>(),
			new_comp<D_Component>(),
			new_comp<E_Component>(),
			new_comp<F_Component>(),
			new_comp<G_Component>(),
			new_comp<H_Component>(),
			new_comp<I_Component>(),
			new_comp<J_Component>(),
			new_comp<K_Component>(),
			new_comp<L_Component>(),
			new_comp<M_Component>(),
			new_comp<N_Component>(),
			new_comp<O_Component>(),
			new_comp<P_Component>(),
			new_comp<Q_Component>(),
			new_comp<R_Component>(),
			new_comp<S_Component>(),
			new_comp<T_Component>(),
			new_comp<U_Component>(),
			new_comp<V_Component>(),
			new_comp<W_Component>(),
			new_comp<X_Component>(),
			new_comp<Y_Component>(),
			new_comp<Z_Component>()
		};
		return componentArray;
	}

	void scaleTest_get_A(const size_t numberOfGetsInTest)
	{
		std::cout << "size: " << numberOfGetsInTest << std::endl;

		//test api
		ComponentManager<std::unordered_map<std::type_index, sp<Component>>> hashContainer;
		hashContainer.createComponent<A_Component>();
		bool bHasComponent = hashContainer.hasComponent<A_Component>();
		A_Component* component = hashContainer.getComponent<A_Component>();
		hashContainer.deleteComponent<A_Component>();
		bool deleteSuccess = bHasComponent != hashContainer.hasComponent<A_Component>();

		ComponentManager<std::map<std::type_index, sp<Component>>> mapContainer;
		ComponentManager_ArrayLookup arrayLookup;

		createComponents(hashContainer);
		createComponents(mapContainer);
		createComponents(arrayLookup);
		volatile std::vector<sp<Component>> castTest = createArrayOfComponents();

		{ScopedTimer perf("hash container component getter");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				volatile A_Component* comp = hashContainer.getComponent<A_Component>();
				comp->doSomething();
			}
		}

		{ScopedTimer perf("map container component getter");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				volatile A_Component* comp = mapContainer.getComponent<A_Component>();
				comp->doSomething();
			}
		}

		{ScopedTimer perf("compile time array lookup ");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				volatile A_Component* comp = arrayLookup.getComponent<A_Component>();
				comp->doSomething();
			}
		}

		{ScopedTimer perf("cast from array component getter");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				auto* nonVolatilePtr = const_cast<std::vector<sp<Component>>*>(&castTest); //const cast away volatility
				sp<Component>& item = (*nonVolatilePtr)[0]; //get errors when trying to index into a volatile vector; 
				volatile A_Component* comp = dynamic_cast<A_Component*>(item.get()); //cast will always be true... but hopefully volatile removes compiler optimizations
				if (comp) { comp->doSomething(); }; //if check should be happening with all dyn casts; adding it to be closer to real scenarios
			}
		}
		std::cout << std::endl;
	}

	template<typename CONTAINER>
	void randomSelect(CONTAINER& container, std::mt19937& eng, std::uniform_int_distribution<size_t>& dist)
	{
		volatile Component* comp = nullptr;
		size_t typeToChooseIdx = dist(eng);
		switch (typeToChooseIdx)
		{
			case 0:
				comp = container.getComponent<A_Component>(); break;
			case 1:
				comp = container.getComponent<B_Component>(); break;
			case 2:
				comp = container.getComponent<C_Component>(); break;
			case 3:
				comp = container.getComponent<D_Component>(); break;
			case 4:
				comp = container.getComponent<E_Component>(); break;
			case 5:
				comp = container.getComponent<F_Component>(); break;
			case 6:
				comp = container.getComponent<G_Component>(); break;
			case 7:
				comp = container.getComponent<H_Component>(); break;
			case 8:
				comp = container.getComponent<I_Component>(); break;
			case 9:
				comp = container.getComponent<J_Component>(); break;
			case 10:
				comp = container.getComponent<K_Component>(); break;
			case 11:
				comp = container.getComponent<L_Component>(); break;
			case 12:
				comp = container.getComponent<M_Component>(); break;
			case 13:
				comp = container.getComponent<N_Component>(); break;
			case 14:
				comp = container.getComponent<O_Component>(); break;
			case 15:
				comp = container.getComponent<P_Component>(); break;
			case 16:
				comp = container.getComponent<Q_Component>(); break;
			case 17:
				comp = container.getComponent<R_Component>(); break;
			case 18:
				comp = container.getComponent<S_Component>(); break;
			case 19:
				comp = container.getComponent<T_Component>(); break;
			case 20:
				comp = container.getComponent<U_Component>(); break;
			case 21:
				comp = container.getComponent<V_Component>(); break;
			case 22:
				comp = container.getComponent<W_Component>(); break;
			case 23:
				comp = container.getComponent<X_Component>(); break;
			case 24:
				comp = container.getComponent<Y_Component>(); break;
			default:
				comp = container.getComponent<Z_Component>(); break;
		}
		comp->doSomething();
	}

	void randomSelectDyn(volatile std::vector<sp<Component>>& castTest, std::mt19937& eng, std::uniform_int_distribution<size_t>& dist)
	{
		size_t typeToChooseIdx = dist(eng);
		auto* nonVolatilePtr = const_cast<std::vector<sp<Component>>*>(&castTest); //const cast away volatility

		switch (typeToChooseIdx)
		{
			case 0:
				if (auto* comp = dynamic_cast<A_Component*>((*nonVolatilePtr)[0].get())) { comp->doSomething(); } break;
			case 1:
				if (auto* comp = dynamic_cast<B_Component*>((*nonVolatilePtr)[1].get())) { comp->doSomething(); }break;
			case 2:
				if (auto* comp = dynamic_cast<C_Component*>((*nonVolatilePtr)[2].get())) { comp->doSomething(); }break;
			case 3:
				if (auto* comp = dynamic_cast<D_Component*>((*nonVolatilePtr)[3].get())) { comp->doSomething(); }break;
			case 4:
				if (auto* comp = dynamic_cast<E_Component*>((*nonVolatilePtr)[4].get())) { comp->doSomething(); }break;
			case 5:
				if (auto* comp = dynamic_cast<F_Component*>((*nonVolatilePtr)[5].get())) { comp->doSomething(); }break;
			case 6:
				if (auto* comp = dynamic_cast<G_Component*>((*nonVolatilePtr)[6].get())) { comp->doSomething(); }break;
			case 7:
				if (auto* comp = dynamic_cast<H_Component*>((*nonVolatilePtr)[7].get())) { comp->doSomething(); }break;
			case 8:
				if (auto* comp = dynamic_cast<I_Component*>((*nonVolatilePtr)[8].get())) { comp->doSomething(); }break;
			case 9:
				if (auto* comp = dynamic_cast<J_Component*>((*nonVolatilePtr)[9].get())) { comp->doSomething(); }break;
			case 10:
				if (auto* comp = dynamic_cast<K_Component*>((*nonVolatilePtr)[10].get())) { comp->doSomething(); }break;
			case 11:
				if (auto* comp = dynamic_cast<L_Component*>((*nonVolatilePtr)[11].get())) { comp->doSomething(); }break;
			case 12:
				if (auto* comp = dynamic_cast<M_Component*>((*nonVolatilePtr)[12].get())) { comp->doSomething(); }break;
			case 13:
				if (auto* comp = dynamic_cast<N_Component*>((*nonVolatilePtr)[13].get())) { comp->doSomething(); }break;
			case 14:
				if (auto* comp = dynamic_cast<O_Component*>((*nonVolatilePtr)[14].get())) { comp->doSomething(); }break;
			case 15:
				if (auto* comp = dynamic_cast<P_Component*>((*nonVolatilePtr)[15].get())) { comp->doSomething(); }break;
			case 16:
				if (auto* comp = dynamic_cast<Q_Component*>((*nonVolatilePtr)[16].get())) { comp->doSomething(); }break;
			case 17:
				if (auto* comp = dynamic_cast<R_Component*>((*nonVolatilePtr)[17].get())) { comp->doSomething(); }break;
			case 18:
				if (auto* comp = dynamic_cast<S_Component*>((*nonVolatilePtr)[18].get())) { comp->doSomething(); }break;
			case 19:
				if (auto* comp = dynamic_cast<T_Component*>((*nonVolatilePtr)[19].get())) { comp->doSomething(); }break;
			case 20:
				if (auto* comp = dynamic_cast<U_Component*>((*nonVolatilePtr)[20].get())) { comp->doSomething(); }break;
			case 21:
				if (auto* comp = dynamic_cast<V_Component*>((*nonVolatilePtr)[21].get())) { comp->doSomething(); }break;
			case 22:
				if (auto* comp = dynamic_cast<W_Component*>((*nonVolatilePtr)[22].get())) { comp->doSomething(); }break;
			case 23:
				if (auto* comp = dynamic_cast<X_Component*>((*nonVolatilePtr)[23].get())) { comp->doSomething(); }break;
			case 24:
				if (auto* comp = dynamic_cast<Y_Component*>((*nonVolatilePtr)[24].get())) { comp->doSomething(); }break;
			default:
				if (auto* comp = dynamic_cast<Z_Component*>((*nonVolatilePtr)[25].get())) { comp->doSomething(); }break;
		}
	}

	void randomSelectDyn_novol(std::vector<sp<Component>>& castTest, std::mt19937& eng, std::uniform_int_distribution<size_t>& dist)
	{
		size_t typeToChooseIdx = dist(eng);

		switch (typeToChooseIdx)
		{
			case 0:
				if (auto* comp = dynamic_cast<A_Component*>(castTest[0].get())) { comp->doSomething(); } break;
			case 1:
				if (auto* comp = dynamic_cast<B_Component*>(castTest[1].get())) { comp->doSomething(); }break;
			case 2:
				if (auto* comp = dynamic_cast<C_Component*>(castTest[2].get())) { comp->doSomething(); }break;
			case 3:
				if (auto* comp = dynamic_cast<D_Component*>(castTest[3].get())) { comp->doSomething(); }break;
			case 4:
				if (auto* comp = dynamic_cast<E_Component*>(castTest[4].get())) { comp->doSomething(); }break;
			case 5:
				if (auto* comp = dynamic_cast<F_Component*>(castTest[5].get())) { comp->doSomething(); }break;
			case 6:
				if (auto* comp = dynamic_cast<G_Component*>(castTest[6].get())) { comp->doSomething(); }break;
			case 7:
				if (auto* comp = dynamic_cast<H_Component*>(castTest[7].get())) { comp->doSomething(); }break;
			case 8:
				if (auto* comp = dynamic_cast<I_Component*>(castTest[8].get())) { comp->doSomething(); }break;
			case 9:
				if (auto* comp = dynamic_cast<J_Component*>(castTest[9].get())) { comp->doSomething(); }break;
			case 10:
				if (auto* comp = dynamic_cast<K_Component*>(castTest[10].get())) { comp->doSomething(); }break;
			case 11:
				if (auto* comp = dynamic_cast<L_Component*>(castTest[11].get())) { comp->doSomething(); }break;
			case 12:
				if (auto* comp = dynamic_cast<M_Component*>(castTest[12].get())) { comp->doSomething(); }break;
			case 13:
				if (auto* comp = dynamic_cast<N_Component*>(castTest[13].get())) { comp->doSomething(); }break;
			case 14:
				if (auto* comp = dynamic_cast<O_Component*>(castTest[14].get())) { comp->doSomething(); }break;
			case 15:
				if (auto* comp = dynamic_cast<P_Component*>(castTest[15].get())) { comp->doSomething(); }break;
			case 16:
				if (auto* comp = dynamic_cast<Q_Component*>(castTest[16].get())) { comp->doSomething(); }break;
			case 17:
				if (auto* comp = dynamic_cast<R_Component*>(castTest[17].get())) { comp->doSomething(); }break;
			case 18:
				if (auto* comp = dynamic_cast<S_Component*>(castTest[18].get())) { comp->doSomething(); }break;
			case 19:
				if (auto* comp = dynamic_cast<T_Component*>(castTest[19].get())) { comp->doSomething(); }break;
			case 20:
				if (auto* comp = dynamic_cast<U_Component*>(castTest[20].get())) { comp->doSomething(); }break;
			case 21:
				if (auto* comp = dynamic_cast<V_Component*>(castTest[21].get())) { comp->doSomething(); }break;
			case 22:
				if (auto* comp = dynamic_cast<W_Component*>(castTest[22].get())) { comp->doSomething(); }break;
			case 23:
				if (auto* comp = dynamic_cast<X_Component*>(castTest[23].get())) { comp->doSomething(); }break;
			case 24:
				if (auto* comp = dynamic_cast<Y_Component*>(castTest[24].get())) { comp->doSomething(); }break;
			default:
				if (auto* comp = dynamic_cast<Z_Component*>(castTest[25].get())) { comp->doSomething(); }break;
		}
	}

	void scaleTest_getRandom(const size_t numberOfGetsInTest)
	{
		//test api
		ComponentManager<std::unordered_map<std::type_index, sp<Component>>> hashContainer;
		ComponentManager<std::map<std::type_index, sp<Component>>> mapContainer;
		ComponentManager_ArrayLookup arrayLookup;
		//volatile std::vector<sp<Component>> castTest = createArrayOfComponents();
		std::vector<sp<Component>> castTest = createArrayOfComponents();

		createComponents(hashContainer);
		createComponents(mapContainer);
		createComponents(arrayLookup);

		std::seed_seq seed{ 1, 3,7,101, 27 };
		std::mt19937 rng_eng_hash{ seed };
		std::mt19937 rng_eng_map{ seed };
		std::mt19937 rng_eng_array{ seed };
		std::mt19937 rng_eng_dyn{seed};

		size_t cmpNumber = 24;
		std::uniform_int_distribution<size_t> distribution(0, const_cast<std::vector<sp<Component>>*>(&castTest)->size() - 1); //[0, cmpNumber]

		{ScopedTimer perf("hash container component getter RANDOM");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				randomSelect(hashContainer, rng_eng_hash, distribution);
			}
		}
		{ScopedTimer perf("MAP container component getter RANDOM");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				randomSelect(mapContainer, rng_eng_map, distribution);
			}
		}
		{ScopedTimer perf("ARRAY LOOKUP container component getter RANDOM");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				randomSelect(arrayLookup, rng_eng_array, distribution);
			}
		}
		{ScopedTimer perf("IF CHECKED DYN Cast container component getter RANDOM");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				//randomSelectDyn(castTest, rng_eng_dyn, distribution);
				randomSelectDyn_novol(castTest, rng_eng_dyn, distribution);
			}
		}
		std::cout << std::endl;


	}

	void scaleTest_cycle(const size_t numberOfGetsInTest)
	{
		//test api
		ComponentManager<std::unordered_map<std::type_index, sp<Component>>> hashContainer;
		ComponentManager<std::map<std::type_index, sp<Component>>> mapContainer;
		ComponentManager_ArrayLookup arrayLookup;
		//volatile std::vector<sp<Component>> castTest = createArrayOfComponents();
		std::vector<sp<Component>> castTest = createArrayOfComponents();

		createComponents(hashContainer);
		createComponents(mapContainer);
		createComponents(arrayLookup);

		std::seed_seq seed{ 1, 3,7,101, 27 };
		std::mt19937 rng_eng_hash{ seed };
		std::mt19937 rng_eng_map{ seed };
		std::mt19937 rng_eng_array{ seed };
		std::mt19937 rng_eng_dyn{ seed };

		size_t cmpNumber = 24;
		std::uniform_int_distribution<size_t> distribution(0, const_cast<std::vector<sp<Component>>*>(&castTest)->size() - 1); //[0, cmpNumber]

		{ScopedTimer perf("hash container component getter CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 3 == 0)
				{
					hashContainer.getComponent<A_Component>()->doSomething();
				}
				else if (i % 3 == 1)
				{
					hashContainer.getComponent<B_Component>()->doSomething();
				}
				//MOD_CHECK(hashContainer, 3, 1, B_Component);
				//MOD_CHECK(hashContainer, 3, 2, C_Component);
				else
				{
					hashContainer.getComponent<C_Component>()->doSomething();
				}
			}
		}
		{ScopedTimer perf("MAP container component getter CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 3 == 0)
				{
					mapContainer.getComponent<A_Component>()->doSomething();
				}
				else if (i % 3 == 1)
				{
					mapContainer.getComponent<B_Component>()->doSomething();
				}
				else
				{
					mapContainer.getComponent<C_Component>()->doSomething();
				}
			}
		}
		{ScopedTimer perf("ARRAY LOOKUP container component getter CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 3 == 0)
				{
					arrayLookup.getComponent<A_Component>()->doSomething();
				}
				else if (i % 3 == 1)
				{
					arrayLookup.getComponent<B_Component>()->doSomething();
				}
				else
				{
					arrayLookup.getComponent<C_Component>()->doSomething();
				}
			}
		}
		{ScopedTimer perf("IF CHECKED DYN Cast container component getter CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 3 == 0)
				{
					if (auto* result = dynamic_cast<A_Component*>(castTest[0].get()))
					{
						result->doSomething();
					}
				}
				else if (i % 3 == 1)
				{
					if (auto* result = dynamic_cast<B_Component*>(castTest[1].get()))
					{
						result->doSomething();
					}
				}
				else
				{
					if (auto* result = dynamic_cast<C_Component*>(castTest[2].get()))
					{
						result->doSomething();
					}
				}
			}
		}
		std::cout << std::endl;
	}

#define MOD_CHECK(container, total, index, type)\
else if (i % total == index)\
{\
	container.getComponent<type>()->doSomething();\
}

#define MOD_CHECK_DYN(total, index, type)\
else if (i % total == index)\
{\
	if (volatile auto* result = dynamic_cast<volatile type*>(castTest[index].get()))\
	{\
		result->doSomething();\
	}\
}

	void scaleTest_cycleBig(const size_t numberOfGetsInTest)
	{
		//test api
		ComponentManager<std::unordered_map<std::type_index, sp<Component>>> hashContainer;
		ComponentManager<std::map<std::type_index, sp<Component>>> mapContainer;
		ComponentManager_ArrayLookup arrayLookup;
		//volatile std::vector<sp<Component>> castTest = createArrayOfComponents();
		std::vector<sp<Component>> castTest = createArrayOfComponents();

		createComponents(hashContainer);
		createComponents(mapContainer);
		createComponents(arrayLookup);

		std::seed_seq seed{ 1, 3,7,101, 27 };
		std::mt19937 rng_eng_hash{ seed };
		std::mt19937 rng_eng_map{ seed };
		std::mt19937 rng_eng_array{ seed };
		std::mt19937 rng_eng_dyn{ seed };

		size_t cmpNumber = 24;
		std::uniform_int_distribution<size_t> distribution(0, const_cast<std::vector<sp<Component>>*>(&castTest)->size() - 1); //[0, cmpNumber]

		{ScopedTimer perf("hash container component getter BIG CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 26 == 0){ hashContainer.getComponent<A_Component>()->doSomething();}
				MOD_CHECK(hashContainer, 26, 1, B_Component)
				MOD_CHECK(hashContainer, 26, 2, D_Component)
				MOD_CHECK(hashContainer, 26, 3, E_Component)
				MOD_CHECK(hashContainer, 26, 4, F_Component)
				MOD_CHECK(hashContainer, 26, 5, G_Component)
				MOD_CHECK(hashContainer, 26, 6, H_Component)
				MOD_CHECK(hashContainer, 26, 7, I_Component)
				MOD_CHECK(hashContainer, 26, 8, J_Component)
				MOD_CHECK(hashContainer, 26, 9, K_Component)
				MOD_CHECK(hashContainer, 26, 10, L_Component)
				MOD_CHECK(hashContainer, 26, 11, M_Component)
				MOD_CHECK(hashContainer, 26, 12, N_Component)
				MOD_CHECK(hashContainer, 26, 13, O_Component)
				MOD_CHECK(hashContainer, 26, 14, P_Component)
				MOD_CHECK(hashContainer, 26, 15, Q_Component)
				MOD_CHECK(hashContainer, 26, 16, R_Component)
				MOD_CHECK(hashContainer, 26, 17, S_Component)
				MOD_CHECK(hashContainer, 26, 18, T_Component)
				MOD_CHECK(hashContainer, 26, 19, U_Component)
				MOD_CHECK(hashContainer, 26, 20, V_Component)
				MOD_CHECK(hashContainer, 26, 21, W_Component)
				MOD_CHECK(hashContainer, 26, 22, X_Component)
				MOD_CHECK(hashContainer, 26, 23, Y_Component)
				MOD_CHECK(hashContainer, 26, 24, Z_Component)
				else{hashContainer.getComponent<C_Component>()->doSomething();}
			}
		}
		{ScopedTimer perf("MAP container component getter BIG CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 26 == 0) { mapContainer.getComponent<A_Component>()->doSomething(); }
				MOD_CHECK(mapContainer, 26, 1, B_Component)
				MOD_CHECK(mapContainer, 26, 2, D_Component)
				MOD_CHECK(mapContainer, 26, 3, E_Component)
				MOD_CHECK(mapContainer, 26, 4, F_Component)
				MOD_CHECK(mapContainer, 26, 5, G_Component)
				MOD_CHECK(mapContainer, 26, 6, H_Component)
				MOD_CHECK(mapContainer, 26, 7, I_Component)
				MOD_CHECK(mapContainer, 26, 8, J_Component)
				MOD_CHECK(mapContainer, 26, 9, K_Component)
				MOD_CHECK(mapContainer, 26, 10, L_Component)
				MOD_CHECK(mapContainer, 26, 11, M_Component)
				MOD_CHECK(mapContainer, 26, 12, N_Component)
				MOD_CHECK(mapContainer, 26, 13, O_Component)
				MOD_CHECK(mapContainer, 26, 14, P_Component)
				MOD_CHECK(mapContainer, 26, 15, Q_Component)
				MOD_CHECK(mapContainer, 26, 16, R_Component)
				MOD_CHECK(mapContainer, 26, 17, S_Component)
				MOD_CHECK(mapContainer, 26, 18, T_Component)
				MOD_CHECK(mapContainer, 26, 19, U_Component)
				MOD_CHECK(mapContainer, 26, 20, V_Component)
				MOD_CHECK(mapContainer, 26, 21, W_Component)
				MOD_CHECK(mapContainer, 26, 22, X_Component)
				MOD_CHECK(mapContainer, 26, 23, Y_Component)
				MOD_CHECK(mapContainer, 26, 24, Z_Component)
				else { mapContainer.getComponent<C_Component>()->doSomething(); }
			}
		}
		{ScopedTimer perf("ARRAY LOOKUP container component getter BIG CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 26 == 0) { arrayLookup.getComponent<A_Component>()->doSomething(); }
				MOD_CHECK(arrayLookup, 26, 1, B_Component)
				MOD_CHECK(arrayLookup, 26, 2, D_Component)
				MOD_CHECK(arrayLookup, 26, 3, E_Component)
				MOD_CHECK(arrayLookup, 26, 4, F_Component)
				MOD_CHECK(arrayLookup, 26, 5, G_Component)
				MOD_CHECK(arrayLookup, 26, 6, H_Component)
				MOD_CHECK(arrayLookup, 26, 7, I_Component)
				MOD_CHECK(arrayLookup, 26, 8, J_Component)
				MOD_CHECK(arrayLookup, 26, 9, K_Component)
				MOD_CHECK(arrayLookup, 26, 10, L_Component)
				MOD_CHECK(arrayLookup, 26, 11, M_Component)
				MOD_CHECK(arrayLookup, 26, 12, N_Component)
				MOD_CHECK(arrayLookup, 26, 13, O_Component)
				MOD_CHECK(arrayLookup, 26, 14, P_Component)
				MOD_CHECK(arrayLookup, 26, 15, Q_Component)
				MOD_CHECK(arrayLookup, 26, 16, R_Component)
				MOD_CHECK(arrayLookup, 26, 17, S_Component)
				MOD_CHECK(arrayLookup, 26, 18, T_Component)
				MOD_CHECK(arrayLookup, 26, 19, U_Component)
				MOD_CHECK(arrayLookup, 26, 20, V_Component)
				MOD_CHECK(arrayLookup, 26, 21, W_Component)
				MOD_CHECK(arrayLookup, 26, 22, X_Component)
				MOD_CHECK(arrayLookup, 26, 23, Y_Component)
				MOD_CHECK(arrayLookup, 26, 24, Z_Component)
				else { arrayLookup.getComponent<C_Component>()->doSomething(); }
			}
		}
		{
			ScopedTimer perf("IF CHECKED DYN Cast container component getter BIG CYCLE");
			for (volatile size_t i = 0; i < numberOfGetsInTest; ++i)
			{
				if (i % 26 == 0)
				{
					if (auto* result = dynamic_cast<A_Component*>(castTest[0].get()))
					{
						result->doSomething();
					}
				}
				MOD_CHECK_DYN(26,1,B_Component)
				MOD_CHECK_DYN(26, 2, C_Component)
				MOD_CHECK_DYN(26, 3, D_Component)
				MOD_CHECK_DYN(26, 4, E_Component)
				MOD_CHECK_DYN(26, 5, F_Component)
				MOD_CHECK_DYN(26, 6, G_Component)
				MOD_CHECK_DYN(26, 7, H_Component)
				MOD_CHECK_DYN(26, 8, I_Component)
				MOD_CHECK_DYN(26, 9, J_Component)
				MOD_CHECK_DYN(26, 10, K_Component)
				MOD_CHECK_DYN(26, 11, L_Component)
				MOD_CHECK_DYN(26, 12, M_Component)
				MOD_CHECK_DYN(26, 13, N_Component)
				MOD_CHECK_DYN(26, 14, O_Component)
				MOD_CHECK_DYN(26, 15, P_Component)
				MOD_CHECK_DYN(26, 16, Q_Component)
				MOD_CHECK_DYN(26, 17, R_Component)
				MOD_CHECK_DYN(26, 18, S_Component)
				MOD_CHECK_DYN(26, 19, T_Component)
				MOD_CHECK_DYN(26, 20, U_Component)
				MOD_CHECK_DYN(26, 21, V_Component)
				MOD_CHECK_DYN(26, 22, W_Component)
				MOD_CHECK_DYN(26, 23, X_Component)
				MOD_CHECK_DYN(26, 24, Y_Component)
				else
				{
					if (auto* result = dynamic_cast<Z_Component*>(castTest[2].get()))
					{
						result->doSomething();
					}
				}
			}
		}
		std::cout << std::endl;
	}




	//void true_main()
	//{
	//	volatile int preventOptimization = 0;
	//	std::cout << "starting getter scale test" << preventOptimization << std::endl;

	//	const size_t numberOfGetsInTest = 100000;
	//	scaleTest_get(numberOfGetsInTest);
	//	scaleTest_get(numberOfGetsInTest*2);
	//	scaleTest_get(numberOfGetsInTest*4);
	//	scaleTest_get(numberOfGetsInTest*8);
	//	scaleTest_get(numberOfGetsInTest*16);


	//	std::cout << "ending getter scale test" << preventOptimization << std::endl;
	//}
}

//int main()
//{
//	volatile int preventOptimization = 0;
//	std::cout << "starting getter scale test" << preventOptimization << std::endl;
//
//	const size_t numberOfGetsInTest = 1000000;
//	scaleTest_get_A(numberOfGetsInTest);
//	scaleTest_get_A(numberOfGetsInTest * 2);
//	scaleTest_get_A(numberOfGetsInTest * 4);
//	scaleTest_get_A(numberOfGetsInTest * 8);
//	scaleTest_get_A(numberOfGetsInTest * 16);
//
//	std::cout << "---------------------------------------------------------------------" << std::endl;
//	scaleTest_getRandom(numberOfGetsInTest);
//	scaleTest_getRandom(numberOfGetsInTest * 2);
//	scaleTest_getRandom(numberOfGetsInTest * 4);
//	scaleTest_getRandom(numberOfGetsInTest * 8);
//	scaleTest_getRandom(numberOfGetsInTest * 16);
//
//	std::cout << "---------------------------------------------------------------------" << std::endl;
//	scaleTest_cycle(numberOfGetsInTest);
//	scaleTest_cycle(numberOfGetsInTest * 2);
//	scaleTest_cycle(numberOfGetsInTest * 4);
//	scaleTest_cycle(numberOfGetsInTest * 8);
//	scaleTest_cycle(numberOfGetsInTest * 16);
//	
//	std::cout << "---------------------------------------------------------------------" << std::endl;
//	scaleTest_cycleBig(numberOfGetsInTest);
//	scaleTest_cycleBig(numberOfGetsInTest * 2);
//	scaleTest_cycleBig(numberOfGetsInTest * 4);
//	scaleTest_cycleBig(numberOfGetsInTest * 8);
//	scaleTest_cycleBig(numberOfGetsInTest * 16);
//
//	std::cout << "ending getter scale test" << preventOptimization << std::endl;
//}