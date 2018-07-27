#include<iostream>
#include<chrono>
#include<thread>
#include <future>

using namespace std::chrono_literals;

namespace
{
	void worker()
	{
		std::this_thread::sleep_for(5s);
	}
} 

static int main_v()
{
	std::cout << "launching deferred async with immediate dtor, if it calls join (it shouldn't) then there will be a delay before dtor message is printed" << std::endl;
	{
		std::future<void> future_deferred = std::async(std::launch::deferred, &worker);
	} //future's dtor called here
	std::cout << "deferred std::async dtor called." << std::endl << std::endl;

	std::cout << "launching async that is done concurrently, its dtor will be called immediately. If it blocks, the the dtor called join!" << std::endl;
	{
		std::future<void> future_concurrent = std::async(std::launch::async, &worker);
	} //future's dtor called here.
	std::cout << "async std::async dtor called." << std::endl << std::endl;


	//noticed that the async std::async blocks because it calls join on its underlying thread...
	//this means that something like std::vector<...async_futures...> will be ambiguous as to whether the asyncs will block on their dtors! 
	//			ie std::vector<std::future<void>>
	std::cout << "done press enter" << std::endl;
	std::cin.get();
}