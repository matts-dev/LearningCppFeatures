#include<iostream>

#include <xtr1common>
#include <mutex>

namespace
{
	class M
	{
		mutable bool flag_cached = false;
		mutable std::mutex m; // having a mutex as a member prevents copying 
	public:

		void not_thread_safe() const
		{
			if (!flag_cached)
			{
				flag_cached = true; //race condition!
				//dowork 
			}
		}

		void thread_safe() const
		{
			std::lock_guard<std::mutex> lock(m);
			if (!flag_cached)
			{
				flag_cached = true;
				//dowork
			}
		}
	};
}

static int main_v()
{
	//note that they said the use of atomics should be limited to a single update;
	//having multiple atomics will 
	std::cin.get();
}