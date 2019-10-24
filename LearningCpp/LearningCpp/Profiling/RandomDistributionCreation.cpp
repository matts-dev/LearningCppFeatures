#include <random>
#include <xtr1common>
#include <memory>
#include <stdint.h>
#include <iostream>


namespace
{
	class RandomNumberGenerator 
	{
	public:
		RandomNumberGenerator(std::initializer_list<unsigned int> seedSequenceInitList)
			: seed(seedSequenceInitList)
		{
			rng_eng = std::mt19937(seed);
		}

	public:

		////////////////////////////////////////////////////////
		// V1 versions re-create the uniform distribution
		////////////////////////////////////////////////////////
		template<typename T = int>
		T getInt(T lowerInclusive = 0, T upperExclusive = std::numeric_limits<T>::max())
		{
			static_assert(std::is_integral<T>::value, "must provide integer type");
			std::uniform_int_distribution<T> distribution(lowerInclusive, upperExclusive);
			return distribution(rng_eng);
		}

		template<typename T = float>
		T getFloat(T lowerInclusive = -(std::numeric_limits<T>::max()/2), T upperExclusive = (std::numeric_limits<T>::max()/2))
		{
			static_assert(std::is_floating_point<T>::value, "must provide floating point type (eg float, double)");
			//#optimize: if re-creating a uniform distribution is slow, we can create a static dist [0,1] and use the result of that
			// to multiple [0,1] * |desired_range| -|range_portion_below_zero| or something of that nature (there's lot of edge cases)
			std::uniform_real_distribution<T> distribution(lowerInclusive, upperExclusive);
			return distribution(rng_eng);
		}

		////////////////////////////////////////////////////////
		// V2 versions use a cached uniform distribution
		////////////////////////////////////////////////////////

		//making distributions like this up front is kinda artificial, because I'd like to use a template. perhaps a local static to a template that can be  massaged into the range desired
		std::uniform_real_distribution<float> float_distribution{ -(std::numeric_limits<float>::max()/2), (std::numeric_limits<float>::max()/2) };
		std::uniform_int_distribution<uint32_t> int_distribution{ 0u, std::numeric_limits<uint32_t>::max()-2 };

		template<typename T = int>
		T getInt_v2(T lowerInclusive = 0, T upperExclusive = std::numeric_limits<T>::max())
		{
			static_assert(std::is_integral<T>::value, "must provide integer type");
			return int_distribution(rng_eng);
			return 0;
		}

		template<typename T = float>
		T getFloat_v2(T lowerInclusive = -std::numeric_limits<T>::max(), T upperExclusive = std::numeric_limits<T>::max())
		{
			static_assert(std::is_floating_point<T>::value, "must provide floating point type (eg float, double)");
			return float_distribution(rng_eng);
		}

	private:
		std::seed_seq seed;
		std::mt19937 rng_eng;
	};


	void true_main()
	{
		std::cout << "numeric limits float max" << std::numeric_limits<float>::max() << std::endl;
		std::cout << "negative numeric limits float max" << -std::numeric_limits<float>::max() << std::endl;
		


		std::shared_ptr<RandomNumberGenerator> myGenerator = std::make_shared<RandomNumberGenerator>(std::initializer_list<unsigned int>{5, 7, 3, 6});

		const std::size_t testSize = 100000000;

		std::vector<float> v1_floats(testSize , 0.0f );
		std::vector<float> v2_floats(testSize, 0.0f);

		std::vector<uint32_t> v1_ints(testSize, 0);
		std::vector<uint32_t> v2_ints(testSize, 0);

		std::cout << "start profiling" << std::endl;

		////////////////////////////////////////////////////////
		// V1
		////////////////////////////////////////////////////////
		for (volatile size_t i = 0; i < testSize; ++i)
		{
			v1_floats[i] = myGenerator->getFloat();
		}
		for (volatile size_t i = 0; i < testSize; ++i)
		{
			v1_ints[i] = myGenerator->getInt();
		}


		////////////////////////////////////////////////////////
		// v2
		////////////////////////////////////////////////////////
		for (volatile size_t i = 0; i < testSize; ++i)
		{
			v2_floats[i] = myGenerator->getFloat_v2();
		}
		for (volatile size_t i = 0; i < testSize; ++i)
		{
			v2_ints[i] = myGenerator->getInt_v2();
		}

		std::cout << "end profiling" << std::endl;
	}
}

//int main()
//{
//	true_main();
//}