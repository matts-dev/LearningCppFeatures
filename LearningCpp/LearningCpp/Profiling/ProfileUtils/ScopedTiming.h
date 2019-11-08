#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>


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

struct NanoScopedTimer
{

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	const char* name;

	NanoScopedTimer(const char* const inName)
	{
		name = inName;
		start = std::chrono::high_resolution_clock::now();
	}

	~NanoScopedTimer()
	{
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;
		using std::chrono::nanoseconds;

		//set up delta time
		auto now = std::chrono::high_resolution_clock::now();
		nanoseconds delta_nano = duration_cast<nanoseconds>(now - start);
		auto delta_ns = static_cast<float>(delta_nano.count());

		std::cout << name << " : " <<
			std::fixed << std::setprecision(2) << delta_ns << " ns"
			<< std::endl; //perhaps shouldn't flush buffer since this is a performance test? but performance should be over so probably okay
	}
};

template<
	typename UNIT_TYPE = std::chrono::nanoseconds,
	typename MAP_TYPE = std::map<std::string, std::vector<float>> 
>
struct ScopedTimerOutput
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::string name;
	MAP_TYPE& output;

	ScopedTimerOutput(const std::string& inName, MAP_TYPE& output) : output(output)
	{
		name = inName;
		start = std::chrono::high_resolution_clock::now();
	}

	~ScopedTimerOutput()
	{
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;

		//set up delta time
		auto now = std::chrono::high_resolution_clock::now();
		UNIT_TYPE delta = duration_cast<UNIT_TYPE>(now - start);
		auto delta_float = static_cast<float>(delta.count());
		output[name].push_back(delta_float);
	}
};