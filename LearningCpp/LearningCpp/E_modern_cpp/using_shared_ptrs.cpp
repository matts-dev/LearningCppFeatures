#include<iostream>
#include <memory>
#include <vector>

namespace
{
	class M
	{
	public:
		M(){}
		M(int x) {}

		~M() { std::cout << "dtor" << std::endl; }
	};


	class SmartClass : public std::enable_shared_from_this<SmartClass>
	{
		//make members private to force user to use factory method.
	private:
		//friend std::shared_ptr<SmartClass>; not necessary with the current implementation

		SmartClass() = default;
		SmartClass(const SmartClass& copy) = default;
		SmartClass& operator=(const SmartClass& copy) = default;
		SmartClass(SmartClass&& move) = default;
		SmartClass& operator=(SmartClass&& move) = default;
	public:
		virtual ~SmartClass() = default;
	public:
		template<typename... Ts>
		//static std::shared_ptr<SmartClass>&& factory(Ts&&... args)  //don't return an rvalue, just return a copy unless allocating on a heap... this will cause issues (ie access violations)
		static std::shared_ptr<SmartClass> factory(Ts&&... args)
		{
			//return std::move(std::make_shared<SmartClass>(std::forward(args)...)); //Bad! this will cause issues since it is declared on the stack (assuming signature returns &&)
			//return std::make_shared<SmartClass>(std::forward(args)...);  //can't do this, even with friendship
			return std::shared_ptr<SmartClass>(new SmartClass(std::forward(args)...));
		}

		void register_container(std::vector<std::shared_ptr<SmartClass>>& container)
		{
			container.push_back(shared_from_this());
		}

		void dowork() { std::cout << "expensive io work!" << std::endl; }
	};

}

static int main_v()
{
	auto deleterA = [](M* rawPtr) {
		std::cout << "deleting: " << rawPtr << std::endl;
		delete rawPtr;
	};
	
	//two ways to create smart pointers, the less safe way (ie using new) allows setting of custom deleters
	std::shared_ptr<M> sptr0(new M(), deleterA); //this method is not recommended, but allows a custom deleter.
	std::shared_ptr<M> sptr1 = std::make_shared<M>();

	//shared pointers internally contain two pointers, the raw pointer, and a pointer to a control block
	//the control block holds the reference count, and holds other things (like the custom deleter)
	//the control block is shared among all the smart pointers, and updates to it are atomic; which has some overhead (specifally changing the reference count)
	auto a = std::make_shared<M>();
	auto b = a; //create a new shared pointer! (copy ctor)

	//shared_ptrs are different than unique pointers in that their custom deleters are not part of the signature, they're instead part of the control block!
	//this means that adding a custom deleter of lambda, fptr, or std::function obj will not change the size of a shared pointer.
	//the shared pointer will stay the same size because the memory for the custom deleter will be in the control block that is internally pointed to by the shared pointer

	//there are many operations of a shared pointer that may cause the deletion of a pointer, it is not just the shared pointer dtor.
	//any operation that decrease the reference count may encounter a reference count of 0 and call delete on the pointed object 
	auto temp = std::make_shared<M>();
	auto other0 = std::make_shared<M>();
	temp = other0; //copy assignment, this decrements temp and will cause dtor!

	// Costs of using shared pointers (well worth it)
	//1. Shared pointers are two times the size of a raw pointer because they contain two pointers, a pointer to the control block and a pointer to the data.
	//2. Reference count(ie control block) memory is allocated dynamically, it cannot be stored within the object -- becaue the object doesn't know it is being managed by a shared pointer...
	//3. Changes to the reference count (I think the control block in general) must be atomic to be thread safe; this has some overhead, even though it uses hardware level atomic instructions
	//			note: atomic operations are generally slower because of this overhead.

	//using move semantics with shared pointers doesn't affect the reference count, and it leaves the moved-from shared_ptr as nullptr
	//since moving avoids updating the atomic reference count, it is faster than copying a shared pointer.
	std::shared_ptr<M> moveTo = std::move(temp); //this will nullify temp in the process of moving

	//shared pointers method of using custom deleters doesn't change the type, which allows you to store shared pointers with different deleters in the same container

	auto deleterB = [](M* rawPtr) {std::cout << "this is a different deleter..." << std::endl; delete rawPtr; };
	{

		std::shared_ptr<M> usesDeleterA(new M(), deleterA);
		std::shared_ptr<M> usesDeleterB(new M(), deleterB);
		std::vector<std::shared_ptr<M>> container;
		container.push_back(std::move(usesDeleterA));
		container.push_back(std::move(usesDeleterB));
		container.emplace_back(new M(), deleterB);
	}

	//note, you can use custom allocators to manage memory of the control block of the smart pointer; you just pass it the allocater you want to use
	std::shared_ptr<M> supedUpSptr(new M(), deleterA, std::allocator<M>()); //this may be a bad example (maybe need a move?), I haven't written custom allocators conforming to std 

	//creation of control blocks (3 ways)
	//1. std::make_shared always creates a control block; 
	//2. A control block is created when a shared_ptr is created when moving from a unique pointer (or auto_ptr)
	//3. A control block is created when a raw pointer is passed to the shared_ptr ctor; passing another shared_ptr will not create a new control block. 
	//				(be careful not to give a raw pointer to two different ctor calls; because that will create two control blocks for a single pointer!)

	{
		auto ptr = SmartClass::factory();

		std::vector<std::shared_ptr<SmartClass>> container;
		ptr->register_container(container);
		container[0]->dowork();
		
	}

	//last minute notes:
	//control blocks internally use virtual methods, so there is the price of a vtable in using shared_ptrs. 
	//shared pointers can't work with arrays; you can force them to work with arrays, but you don't get the nice features like [] operator etc. You probably should just use a vector anyways. Plus, shared_ptr enables polymorphic conversion things that might play strange when used with arrys.
	//if a unique ptr will work, prefer it to shared_ptrs; unique pointers are more light weight
	//once you commit to shared_ptrs, it is hard to get away from them. It is easy to convert from uptr to sptr, but not the other way around!

	//when using std::make_shared, the control block is allocated within the memory used for the class!

	//note: (there's no shared pointers of arrays implemented)
	std::cin.get();
}
