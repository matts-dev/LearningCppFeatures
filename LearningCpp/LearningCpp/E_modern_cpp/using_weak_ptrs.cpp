#include<iostream>
#include <memory>


namespace
{
	class M
	{
	public:
		int dowork() { return -1; }
	};
}

static int main_v()
{
	std::shared_ptr<M> sptr = std::make_shared<M>();

	//you can create weak pointers from shared pointers.
	std::weak_ptr<M> wptr = sptr;

	//weak pointers cannot be directly dereferenced, they must be locked and turned into a shared pointer!
	//weak pointer references look at the shared pointer reference count (in the control block), which is an atomic operation;
	//the reference count read being atomic means it is a slow operation. 
	//(note, the control block has a count for number of weak pointers, but weak pointers still use the shared pointer reference count)

	//there are two ways to access a weak pointer. 
	std::shared_ptr<M> sptr_from_weak1 = wptr.lock(); //this returns nullptr if wptr is expired
	std::shared_ptr<M> sptr_from_weak2(wptr);		 //this throws exception if wptr is expired

	if (sptr_from_weak1)
		sptr_from_weak1->dowork();
	if (sptr_from_weak2)
		sptr_from_weak2->dowork();
	
	//demo what happens when a weak pointer is expired
	std::weak_ptr<M> expired1;
	{
		auto dtor_at_end_of_scope = std::make_shared<M>();
		expired1 = dtor_at_end_of_scope;
	}
	
	//method1, creating shared_ptr from a weak_ptr.lock()
	auto expired_sptr1 = expired1.lock();
	if (expired_sptr1 == nullptr)
		std::cout << "weak.lock returned nullptr" << std::endl;
	else
		std::cout << "something other than nullptr created from lock()" << std::endl;

	//note, you can treat shared pointers just like regular pointers,
	if (expired_sptr1)
		std::cout << "pointer is not null" << std::endl;
	else
		std::cout << "pointer is null!" << std::endl;

	try
	{
		std::shared_ptr<M> expired_sptr2(expired1);
		std::cout << "no exception :3" << std::endl;
		//expired_sptr2->dowork();
	}
	catch (std::exception e)
	{
		std::cout << "creating shared pointer caused an exception" << std::endl;
	}

	//you can also check if weak pointers have expired with a method call...
	//but in multithreaded environments this may cause a race condition because 
	//the object pointing to by the weak pointer may be deleted between the expired() call and its conversion to a shared pointer
	//thus, I think it's probably best to convert to a shared_ptr via the lock() method and then check if it is nullptr
	if (expired1.expired())
	{
		std::cout << "this weak pointer has expired; but don't trust me! check the shared pointer you're going to make..." << std::endl;
	}
	if (!wptr.expired())
	{
		std::cout << "this weak pointer is still valid" << std::endl;
	}

	//rather than thinking of weak_ptrs as pointers, think of them as augmentations of shared pointers because you must have a shared_ptr to get a weak pointer.
	//weak pointers that dangle are "expired", hence the method name above.
	//in terms of efficiency, weak_ptrs are essentially the same as shared_ptrs

	//common usages for weak_ptrs
	//1.observer pattern, subjects (objects with state) and observers(notified on subject change); 
	//observers hold weak pointers to subjects so that subject lifetime isn'tn dependent on the observer
	//2.avoiding cyclic paterns in std::shared_ptr

	//don't overuse weak pointers,
	//in creating a non-cyclic tree, parents should hold children with unique ptrs, which mean no weak_ptrs.
	//in this case, children can refer to their parents with raw pointers since children will be destroyed when parents are destroyed

	//weak pointers don't manipulate the shared_ptr reference count, but weak ptrs do manipulate a different atomic reference count in the control block

	std::weak_ptr<M> null_wptr;

	std::cout << "Hello world" << std::endl;
}