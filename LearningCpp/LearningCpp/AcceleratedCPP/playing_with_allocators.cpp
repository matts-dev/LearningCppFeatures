#include<iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

namespace
{
	class A
	{
	public:
		A() { std::cout << "\tno arg" << std::endl; }
		A(const A&) { std::cout << "\tcopy ctor" << std::endl; }
		~A() { std::cout << "\tdtor" << std::endl; }
	};
}

static 
int main_v()
{
	size_t size = 4;

	std::allocator<A> alloc;
	A* start = alloc.allocate(size);
	A* avail = start;
	A* end = start + size; //goes one passed end, like all std::container iterators.

	std::cout << "generate an object" << std::endl;
	alloc.construct(avail++);

	std::cout << "copy an object" << std::endl;
	alloc.construct(avail++, *start);

	std::cout << "delete the copied object" << std::endl;
	alloc.destroy(--avail);

	std::cout << "uninitialized_copy" << std::endl;
	A* stop = (start + 1);
	//avail = std::uninitialized_copy(start, stop, avail); //requires disabling checked warnings

	std::cout << "uninitialized_fill" << std::endl;
	std::uninitialized_fill(avail, end, *start); //fill the remaining array up; returns void so have to manually update avail
	avail += end - avail;
	assert(avail == end);

	std::cout << "destory all elements" << std::endl;
	while (avail != start)
	{
		//avail will start 1 passed end, so we need to decrement first
		//also, we want to dtor the start too, prefix decrement will give us that behavior too
		alloc.destroy(--avail);
	}
	alloc.deallocate(start, size);

	start = avail = end = stop = nullptr;
	std::cin.get();
	return 0;
}