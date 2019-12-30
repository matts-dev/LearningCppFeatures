#include <iostream>
#include <exception>

template<unsigned N>
struct object
{
	void print()
	{
		std::cout << N << std::endl;
	}
};


template <unsigned N>
struct faux_switch
{
	static void select(unsigned arg)
	{
		if (arg <= N)
		{
			select_internal(arg);
		}
		else
		{
			throw std::runtime_error("value out of range");
		}

	}

	static void select_internal(unsigned arg)
	{
		if (N == arg)
		{
			object<N> obj;
			obj.print();
		}
		else
		{
			faux_switch<N - 1>::select_internal(arg);
		}
	}
};

template<>
struct faux_switch<0u>
{
	static void select_internal(unsigned arg)
	{
		if (0u == arg)
		{
			object<0u> obj;
			obj.print();
		}
	}
};


//int main()
//{
//	faux_switch<100>::select(5);
//	faux_switch<100>::select(101);
//
//}