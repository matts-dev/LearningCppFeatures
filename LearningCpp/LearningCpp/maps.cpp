//maps (hash maps)
//Matt Stone 6/13/2016
#include<iostream>
#include<map>
#include<string>
#include<utility> //to create a simple pair

using namespace std;

void maps(void){
	map<string, string> colors = { { "blue", "azul" }, { "red", "rojo" } };
	colors.insert({ "green", "verde" });

	//Manually make a pair and insert it
	pair<string, string> toInsert;
	toInsert.first = "white";
	toInsert.second = "blanco";
	colors.insert(toInsert);

	//insert using bracket operators 
	colors["brown"] = "marron";

	//Loop through with a for each
	for (pair<string, string> pair : colors){
		cout << pair.first << " is " << pair.second << endl;
	} cout << endl << endl;

	//Accessing the map (key to value)
	string white = "white";
	cout << white << " is " << colors[white] << endl; 	//returns key's associated value
	cout << white << " is " << colors.at(white) << endl;	//returns the key's associated value.
	cout << white << " is " << colors.find(white)->second << endl << endl; 	//find returns iterator

	//Accessing ap Again, without variables
	cout << "green is " << colors["green"] << endl;
	cout << "blue is " << colors.at("blue") << endl;
	cout << "red is " << colors.find("red")->second << endl << endl;

	// Maps cannot be accessed backwards (value to key)
	cout << "maps cannot be accessed backwards" << endl;
	//Creates a blank entry "rojo"
	cout << "rojo is " << colors["rojo"] << endl;
	//cout << notInMap << " is " << colors.at(notInMap) << endl; //THROWS CATCHABLE EXCEPTION
	//cout << colors.find(notInMap)->second << endl << endl;	 //non-catchable: iterator non-derefernable 

	// Map size
	cout << "the map size is: " << colors.size() << endl << endl;

	// Inserting a duplicate element;
	auto errorPair = colors.insert({ "green", "verde" }); //see below to see what auto fills in
	pair<map<string, string>::iterator, bool> errorPairDemo = colors.insert({ "test", "test" });
	colors.erase("test");

	if (errorPair.second){
		cout << "insert success" << endl << endl;
		cout << errorPair.first->first << " inserted with " << errorPair.first->second << endl;
		cout << endl;
	}
	else {
		cout << "insert failure" << endl;
		cout << (errorPair.first)->first << " was found with " << (errorPair.first)->second << endl;
		cout << endl;
	}

	//Erasing
	colors.erase("blue");
	colors.erase("yellow");	//not in colors
	colors.erase("rojo");	//invalid entry made when trying to access map backwards
	colors.erase(colors.find(white));

	//Idiomatic way of erasing
	map<string, string>::iterator iter = colors.find("green");	//avoided using auto
	if (iter != colors.end()){
		cout << "Removing " << iter->first << endl;
		colors.erase(iter);
	}
	else cout << "could not find \"green\" to remove" << endl;
	cout << endl << endl;

	//Checking to see if erase worked (my experiments)
	colors.insert({ "yellow", "amarillo" });
	if (colors.erase("yellow")){ cout << "Removed yelow successfully " << endl; }
	else { cout << "failed to remove yellow" << endl; }

	//demosntrate if statement can be used to check
	if (colors.erase("yellow")) cout << "removed yelow successfully " << endl;
	else cout << "Failed to remove yellow" << endl;	
	cout << endl << endl;


	// printing off the map
	cout << "Printing off map after entries erased." << endl;
	for (auto it = colors.begin(); it != colors.end(); ++it){
		cout << '\t' << (*it).first << " is " << it->second << endl;	//review on calling pointers methods/fields
	}
}

//self test Maps

//create a map of strings and strings used to convert from english to spansih colors
//insert an element to the map using the .insert function and brackets {,}
//insert an element to the map using the .insert function and a std::pair variable
//insert an element using the [] notation
//can maps be accessed backwards (using value to get key?)					<no, they cannot>
//Access an element using .at()				<returns value for key>
//Access an element using .find()			<returns a pair>
//Access an element using []				<returns value for key>
//Erase an element passing an iterator and using .find to get the iterator()
//erase an element passing a key
//use the erase method within an if statements condition
//iterator through a map using the STL iterators (get them directly from map)

//? What happens if you try to insert an pair for which a key already exists?	<it returns an error pair, first is the value already at the key,second is bool as in regards to successful insertion>
//? What happens if you successfully insert a pair using insert?				< returns (pair<map<string, string>::iterator, bool>), ie{*{key, value}, (bool success)} is what is returned, first is an iterator>
//? What happens if you try to access something using [] that doesn't exist?	<a key will be created [key], its value will be set to a default value (an emptry string in this case)>
//? What happens if you make a key using [key] but don't set a value and no-default constructor exists for the object?
//? What does .erase return?			<returns number of elements erased>
