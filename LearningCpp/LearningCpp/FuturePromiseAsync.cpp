//Future, Promise, and async
//Matt Stone 7/26/16

#include<iostream>
#include<thread>
#include<future>


using namespace std;
//function for thread
int changeNumber(int x);
int promiseDependingFunction(future<int>& fu);
int promiseDependingFunction2(shared_future<int> sfu);


void futures() {
	//NOTE: THIS FILE CONTAINS 3 FUNCTIONS TO LOOK AT; futures, promises, and sharedfutures.
	int number = 10;

	//using future, future essentially is a container that will hvae a value after a thread finishes
	future<int> fu;

	//async with "launch::async" arg will start a thread that will return a future
	fu = async(launch::async, &changeNumber, number);

	//do some work this thread...
	for (int i = 0; i < 100; ++i) {
		this_thread::sleep_for(chrono::milliseconds(10));
	}

	//now need the future value that was processed concurrently
	int fuValue = fu.get();	// YOU MAY ONLY CALL FUTURE.GET ONCE!
	cout << "future value is: " << fuValue << endl;		//this 
}

//Promises are essentially a location to store a value that a future is waiting for
void promises() {
	int x = 10;
	promise<int> myPromise;			//this is where we will put a value when we get it
	future<int> futureForThread;	//this is how the thread will extract the value

	//link the promise to suply the future
	futureForThread = myPromise.get_future();

	//launch the thread (futures and promises cannot be copied, move or reference)
	future<int> myFu = async(launch::async, &promiseDependingFunction, ref(futureForThread));

	//... doing some work ... finally figured out what to pass as promise ...
	this_thread::sleep_for(chrono::milliseconds(543));
	myPromise.set_value(10);
	//set_exception(make_exception_ptr(runtime_error("sorry about breaking promise")));
	
	//... more work now that promise is given ...
	this_thread::sleep_for(chrono::milliseconds(543));

	int myFuValue = myFu.get();
	cout << myFuValue << endl;
}

//You can use shared_future to allow multiple threads to depend on one future (as opposed to copying)
void sharedfutures() {
	int x = 10;
	promise<int> myPromise;			
	future<int> futureForThread = myPromise.get_future();
	shared_future<int> sf = futureForThread.share();	//will allow multiple threads to access the future,

	//launch the thread - NOTICE: shared_futures can be passed by value
	future<int> myFu1 = async(launch::async, &promiseDependingFunction2, sf);
	future<int> myFu2 = async(launch::async, &promiseDependingFunction2, sf);
	future<int> myFu3 = async(launch::async, &promiseDependingFunction2, sf);


	//... doing some work ... finally figured out what to pass as promise ...
	this_thread::sleep_for(chrono::milliseconds(543));
	myPromise.set_value(10);

	//... more work now that promise is given ...
	this_thread::sleep_for(chrono::milliseconds(543));

	int myFuValue1 = myFu1.get();
	int myFuValue2 = myFu2.get();
	int myFuValue3 = myFu3.get();

	cout << myFuValue1 << " " << myFuValue2 << " " << myFuValue3 << endl;
}

//FUNCTIONS FOR THREADS
int changeNumber(int x) {
	for (int i = 0; i < 10; ++i) {
		x += i;
	}
	cout << "worker thread done!" << endl;
	return x;
}
int promiseDependingFunction(future<int>& fu) {
	//... do some work setting up the environment...
	this_thread::sleep_for(chrono::milliseconds(100));

	//ready to wait for promise to be fufilled
	int value = fu.get();

	//use value
	value *= 16;

	return value;
}

int promiseDependingFunction2(shared_future<int> sfu) {
	int value = sfu.get();
	return value*2;
}




//self test
//Write an async that will ultimately be used to get an integer
//Write code using future to get interger
//Write code using a promise; pass a future to a function and have it return something based on a later set promise in main thread


//What is an async?													<essentially is a quick way of launching a thread>
//What is the first argument for async (if not  left implicit)?		<tells where to launch in thread, or wait to launch when needed>
//																		<launch::deffered | launch::async>
//What does async return?											<future object>
//What is a future object?											<container that will store the value whe nthe async thread finishes>
//What is future.get()?												<essentially gets the value from worker thread, calling this will wait until thread finishes if iti s not finished
//How many times can you call future.get()?							<only one time>

//what is a promise?												<essentially is a container to put a value to be calculated later>
//what is the purpose of a promise?									<it can be used to start a function before a value is known, the value is promised to be determined somepoitn later>
//how are promises used?											<promise is linked to a future, and that future is passed as reference to a function; when promise is fufilled, the future.get() function will work>
//what happens when a promise is never met?							<an exception will be thrown>







