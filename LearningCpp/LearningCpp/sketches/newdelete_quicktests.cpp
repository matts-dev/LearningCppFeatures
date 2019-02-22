
#include <iostream>
#include <stdexcept>

namespace
{
	struct DeleteMatcher
	{
		DeleteMatcher()
		{
			throw std::runtime_error("try crash!");
		}
		void* operator new(std::size_t bytes)
		{
			return new char[bytes];
		}
		//this function will be called if the one below it doesn't exist
		void operator delete(void* mem)
		{
			delete[] mem;
		}
		//this function will be favored since it matches the operator new more closely
		void operator delete(void* mem, size_t bytes)
		{
			delete[] mem;
		}
	};

	void true_main()
	{
		try
		{
			DeleteMatcher* obj = new DeleteMatcher;
			delete obj;
		} catch (std::exception&) {}

	}
}

int main()
{
	true_main();
}
