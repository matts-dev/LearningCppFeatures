//Matt Stone 6/9/2016
#include<iostream>
#include<string>
#include<iomanip>	//for setprecisions
using namespace std;

void ioCOUT(void){
	int x = 256 + 150 + 31;
	int y = 3973515;
	int z = 3884217;
	float fx = 31.75;
	cout << "modifying cout" << endl;
	cout << x << " " << y << " " << z << " " << fx << endl;

	cout << std::hex;		//using namespace, shown in this for clarity
	cout << x << " " << y << " " << z << " " << fx << endl; //float not hex

	cout << std::showbase << hexfloat;
	cout << x << " " << y << " " << z << " " << fx << "\n" << endl; //notice ints hex is still set
	cout << oct;
	cout << "oct: " << x << " " << y << " " << z << " " << fx << endl;
	cout << dec;
	cout <<"dec: "<< x << " " << y << " " << z << " " << fx << endl;

	double fy = 1234.1234;
	double fz = 5E-1;
	cout << scientific;
	cout << '\n' << fx << ' ' << fy << ' ' << fz << ' ' << endl;
	cout << setprecision(2);	//for scientific
	cout << fx << ' ' << fy << ' ' << fz << ' ' << endl;
	cout << fixed << setprecision(2);	//fixed or scientific, not both
	cout << fx << ' ' << fy << ' ' << fz << ' ' << endl;

	//reset cout ot floats default
	cout.unsetf(ios_base::floatfield);	//reset to default
	cout << "default: " << fx << ' ' << fy << ' ' << fz << ' ' << '\n' << endl;

	//String formating
	string str1 = "hello world";
	string str2 = "this message is brought to you by:";
	string str3 = "three strings";
	cout << str1 << '\n' << str2 << '\n' << str3 << '\n' << endl;
	
	//format the strings before you call them, you will need to format each of them
	cout << setw(64) << right << str1 << endl;
	cout << setw(64) << right << str2 << endl;
	cout << setw(64) << right << str3 << endl;

	//fill settings for string formating
	cout << setfill('-') << setw(64) << right << str1 << endl;	//fill is saved 
	cout << setw(64) << left << str1 << endl; //notice the fill did not change

	//endl is actually a manipulator too 

	//reseting cout afte rmanipulating it 
	ios::fmtflags f(cout.flags());	//save the state of cout
	cout.flags(f);					//set cout to a prevoius state (if state is clean, this can be used to reset cout)
	//this isn't a perfect reset however, see answers: http://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it
	
}

/*COUT SELFTEST */
//pass arguments/modifiers to cout
//what is a modifier/manipulator?
// what is the modifier to cout to print hex integers?
// what is hte modifier to print oct numbers?
// what is the modifier to print scientific?
// what is the modifier to set the precision?
// what is the include if you try to setprecision without properly setting up? #include<manip>
// how to reset the float outputs of cout?     cout.unset(ios_base::floatfield)
// FORMATING
// how ot set hte width?
// how to make right/left justified?
// when does the target string enter couter when using the baove two manipulators? <at the end>
// how to set the fill of the width (ie change from default whitespace)
// how ot set cout? is it straightfoward?

