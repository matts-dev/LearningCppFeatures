//const cast
//matt stone 7/10/16

#include<iostream>
#include"inhert.hpp"	//functions are not const-safe
using namespace std;

void constcasts() {



	Inherit::Bottom botobj;
	Inherit::Bottom botobj2;
	//points to a constant object
	const Inherit::Base*  constBasePtr = &botobj;

	//const casts
	Inherit::Base* mutBasePtr = const_cast<Inherit::Base*>(constBasePtr);
	mutBasePtr->speakV();

	//take it back to const
	const Inherit::Base* constBasePtr2 = mutBasePtr;
	//constBasePtr2->speakV();	//cannot do this because function is not const safe
		
	//for curiosity, yo ucan cast back to const (even though you don't need a cast to do this)
	constBasePtr2= const_cast<const Inherit::Base*>(mutBasePtr);
	

	//---------------------------------------------------------------------
	//mut object, const pointer
	Inherit::Base* const baseConstPtr = &botobj;
	mutBasePtr = baseConstPtr;	//no need to do const cast;
	//below is NOT What constcast is for (see above, we can just make a new pointer)
	mutBasePtr = const_cast<Inherit::Base*>(baseConstPtr);		//here it is anyways lol
	
}