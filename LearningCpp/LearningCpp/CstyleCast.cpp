//c style casts
//matt stone 

#include <iostream>
using namespace std;

void cstylecasts() {
	//This are the be avoiding in favor of c++ style casts.
	//c++ casts provide narrow usage, and therefore are safer to use (instead of accidently doing a wrong cast)
	//c++ casts also allow runtime check

	//------------------ c-style casts are a mixture of static_cast, const_cast, and reinterpret cast ---------
	double largeRadex = 1235.5213;
	
	//c-style cast
	int cstyle = (int)largeRadex;

	//function style
	int functStyle = int(largeRadex);
}