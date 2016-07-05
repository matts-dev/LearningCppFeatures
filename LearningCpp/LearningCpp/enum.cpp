//enumeration type
//Matt Stone 7/1/2016

#include <iostream>
using namespace std;

enum CardSuit { SPADE, HEART, CLUB, DIAMOND };
enum CardRank { ACE = 1, DEUCE = 2, JACK = 11, QUEEN, KING };	//queen/king do not need values assigned (it increase after jack's 11 assignment

struct Card{
	unsigned char rank;	//enum type will promote to int, which can demote to char
	unsigned char suit; //enum type will change 
};

struct CardStrict{	//doesn't support all card combinations, must define numbers
	CardRank rank;
	CardSuit suit;
};

//enums behave like integers (integer is the underlying type)
void enums(){
	Card hand[] = { { ACE, HEART }, { 1, 0 }, 5, HEART };
	CardStrict hand2[] = { { ACE, HEART }, { ACE, SPADE } };

	//making assingments
	hand[1].rank = 1;	//set rank to ace using numbers
	hand[1].suit = 1;	//set suit to heart using numbers

	hand[1].rank = CardRank::ACE;	//using full name (like in java, but with :: operator)
	hand[1].suit = CardSuit::HEART;

	hand[1].rank = ACE;		//do not need to use full name like in java 
	hand[1].suit = HEART;	//do not need to use full name like in java

	switch (hand[1].suit){
		case 1:		//1 is HEART
			cout << CardSuit::HEART << endl;	//will print out 1
			cout << "heart is the suit" << endl;
			break;
		case SPADE:
			cout << CardSuit::SPADE << endl;	// will print out 0
			cout << "spade is the suit" << endl;
			break;
		case DIAMOND:
			cout << CardSuit::DIAMOND << endl;	// will print out 3
			cout << "diamond is the suit" << endl;
			break;
		case CLUB:
			cout << CardSuit::CLUB << endl;		// will print out 2
			cout << "club is the suit" << endl;
			break;
		default:
			cout << "default" << endl;
	}
}

//self test
//what is the underlying type of enums?					<int>
//how can can you use numbers and enums together?	since enums can be converted to int, you can use char, int, etc and just pass in enum value (it will be converted to the corresponding int)
//write an enum for weather types
//assign the weather types based on severity, rather than counting up (rain = 5, thunder = 10)
//use a switch statment to print out specific messages depending on the type of weather
//assign a enum typed variable using its full name, its shortened name (without enum), and by a number



// NOTE: ENUM CLASS
enum class Colors { BLUE, RED, GREEN };				//class type enums must have their values scoped
enum class Colors2 : char { BLACK, YELLOW, RED };	//these have an underlying type of char

void classEnums(){
	Colors test1 = Colors::BLUE;	//will use 4 bytes, underlying type is int 
	Colors2 test2 = Colors2::BLACK; //will only use 1 byte since it has an underlying type of char

	if (test1 == Colors::BLUE) test1 = Colors::GREEN;	//must use full names, unlike the c type of enums 

	switch (test1){
		case Colors::BLUE:
			cout << "blue " << endl;
			break;
			//case 1:		//cannot implicit convert these types
		case Colors::RED:
			cout << "red " << endl;
			break;
		case Colors::GREEN:
			cout << "green" << endl;
			break;
		default:
			break;
	}
}




