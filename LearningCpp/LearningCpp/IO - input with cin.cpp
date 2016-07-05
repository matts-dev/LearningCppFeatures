//Matt Stone 6/9/2016
//IO and Files
#include<iostream>
#include<string>
#include<limits> //for numeric limits with cin
using namespace std;

void ioCIN(void){
	string str;
	//Examining the cin object
	cout << "cin only accepts a single world (delimited by spaces)" << endl;
	cout << "enter a sentence to test 'cin'" << endl;

	//cin will leave tokens in the buffer! later cin calls will use those words!
	cin >> str;	//must include string
	cout << "you entered: \"" << str << "\" was the latter words removed?" << endl;
	cout << "\n'cin' will leave other words in the buffer and lead to problems" << endl;

	//clear the cin buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//second argument optional, clears until \n
	//WARNING: leaving out a stop argument can break cin...
	//WARNING: doesn't clear for the remainder of the program, have to do this manually

	//cin.ignore(numeric_limits<streamsize>::max());	//-BAD: cin will ignore newlines! since we're using namespace
	cout << "Buffer was cleared? enter something new!" << endl;
	cin >> str;
	cout << "you entered: \"" << str << "\" with ending words chopped off" << endl;
	//clear buffer again
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //must be called everytime!

	//How to make CIN read a line (not quite the best way)
	cout << "\nTo get a line, use cin.getline(char[], sizeof(charbuffer)" << endl;
	cout << "enter a sentence this time!" << endl;

	//cin.getline
	char buffer[128];
	//WARNING: too large of strings will cause issues - (cin will throw error flag on itself)
	cin.getline(buffer, sizeof(buffer)); // must be used on char[] //warning cont'd: clearing buffer doesn't help
	cout << "You entered: \"" << buffer << "\"" << endl;

	//cin.getline handling errors (also works with typical cin >> string)
	cout << "\nEnter something with more characters than 3" << endl;
	cout << "This will flag cin, unless cleared" << endl;
	char buf2[4];
	if (!cin.getline(buf2, sizeof(buf2))){
		cout << "ERROR WITH CIN,\t NEED TO CLEAR (in if statment)\n" << endl;
		cin.clear();	//clears error flag, NOT BUFFER
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //CLEAR BUFFER
	}
	cout << "to prove error was handled, enter a string" << endl;
	cin >> str; //leaves \n after string: see comment below
	//http://stackoverflow.com/questions/25475384/when-and-why-do-i-need-to-use-cin-ignore-in-c
	cout << "called another cin and got: \"" << str << "\"" << endl;


	//Perhaps the best way to get a line (namespaces provided for clairty)? from stackoverflow
	cout << "\nUsing std::getline(std::cin, string)" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	std::getline(std::cin, str);
	cout << "You entered: \"" << str << "\"" << endl;
	cout << "\nenter another using getline(cin str) " << endl;
	getline(cin, str);
	cout << "entered: \"" << str << "\"" << endl;


	//reloading an ignore
	cout << "\nPreloaded an ignore for 'n', it should only do it one time " << endl;
	cout << "TYPE 'n' AT SOME POINT IN NEXT STR" << endl;
	cout << "type hipinipih" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), 'n');
	std::getline(cin, str);
	cout << str << "\nEnter hipinipih again" << endl;
	std::getline(cin, str);
	cout << str << endl;
}

//self test cin
//using cin, can you pass an entire string into it?
//				no, cin deliminates by spaces, thus it will not store the entire string
//what happens when you attempt to load a string containig spaces into cin? there are remaining words in the buffer
//how to clear cins buffer?			cin.ignore(,)
//what are the arguments of cin.ignore?			(size, and stop point)
//what arguments should you use to clear a line at a time?			<numeric_limits<streamsize::max()>, '\n'>
//what must you include toget the max limit? //#include<limits> //for numeric limits with cin

//make cin to take an entire string? 				getline(char buffer and sizeof)
//what are the arguments of cin.getline(,)?			char[] and sizeof the array

//what happens if you enter a line too big for the buffer of cingetline?
// how to clear the error?			cin.clear()
// should you clear the buffer?		yes,   cin.ignore(numeric_limits(streamsize::max()), '\n'
// should you always include '\n' in the cin.ignore(,) buffer clear? <YES, otherwise cin seems to will ignore further calls>

// another good aproach for getting a line? independent of cin?
// std::getline(), how is it different from cin.getline()?			<it accepts streams (first arg), then location (second arg)>
//					note, std::getline(stream, container) can save in strings, not just char buffers
// can this getline be used with stringstrams? <YES>
//



