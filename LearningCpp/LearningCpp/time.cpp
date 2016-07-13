// time.h
// Matt Stone

#include<ctime>
#include<iostream> // feeling lazy to type printfs :P
using namespace std;

void times() {
	//Variable to save time in
	time_t timeVar;		//usually a 64 bit integer on most systems

	//get current time
	timeVar = time(nullptr);		//returns # seconds since midnight, Jan 1, 1970
	cout << "Seconds since 1970" << timeVar << endl;

	//get time in gmt  or local
	struct tm gmt   = *(	gmtime(&timeVar)	);	//have to de-reference what is returned
	struct tm local = *(	localtime(&timeVar)	);

	//printing off time
	cout << "gmt" << endl;
	cout << "year " << gmt.tm_year + 1900 << endl;
	cout << "month " << gmt.tm_mon + 1 << endl;
	cout << "day " << gmt.tm_mday << endl;
	cout << "hour " << gmt.tm_hour << endl;
	cout << "min " << gmt.tm_min << endl;
	cout << "sec " << gmt.tm_sec << endl << endl;

	cout << "local" << endl;
	cout << "day " << local.tm_mday << endl;
	cout << "hour " << local.tm_hour << endl;
	cout << "min " << local.tm_min << endl;
	cout << "sec " << local.tm_sec << endl << endl;


	const int buffersize = 128;
	char buffer1[buffersize];
	size_t len = strftime(buffer1, buffersize, "%Y-%m-%d  %H-%M-%S \ndate token -> %D", &gmt);
	printf(buffer1, len);



}