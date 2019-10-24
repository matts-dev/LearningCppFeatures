#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>


struct ScopedTimer
{

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	const char* name;

	ScopedTimer(const char* const inName)
	{
		name = inName;
		start = std::chrono::high_resolution_clock::now();
	}

	~ScopedTimer()
	{
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;
		using std::chrono::nanoseconds;

		//set up delta time
		auto now = std::chrono::high_resolution_clock::now();
		milliseconds delta_milis = duration_cast<milliseconds>(now - start);
		auto delta_ms = static_cast<float>(delta_milis.count());

		std::cout << name << " : " <<
			std::fixed << std::setprecision(2) << delta_ms << " ms"
			<< std::endl; //perhaps shouldn't flush buffer since this is a performance test? but performance should be over so probably okay
	}
};