//sets
//Matt Stone 6/12/16

#include<iostream>
#include<set>
#include<string>

using namespace std;

void sets(void){
	//Sets are a generic container 
	//Sets do not hold duplicate values (though multisets hold multi-values)
	//Sets order values using comparison operators 
	//sets are associate - that is objects are ordered by their value 
	//sets do not support random access - it has a bidirectional iterator  


	//create an populate the set
	set<string> strSet;
	strSet.insert("zzz");
	strSet.insert("ddd");
	strSet.insert("aaa");
	strSet.insert("ccc");
	strSet.insert("bbb");

	//print the set
	for (string str : strSet){
		cout << str.c_str() << ' ';
	} cout << endl;

	//get the size of the set
	cout << "size: " << strSet.size() << endl;

	//insert a random element
	strSet.insert("goes?");
	for (string str : strSet) cout << str.c_str() << ' ';		//forgot to include<string>, left it out for a while
	cout << endl;

	//FIND ELEMENT AND ERASE IT
	set<string>::const_iterator it = strSet.find("goes?");
	//make sure iterator isn't at the end
	if (it != strSet.end()){
		cout << "Element Found - erasing it!!!" << endl;
		strSet.erase(it);
	}
	//print out the new set
	for (it = strSet.begin(); it != strSet.end(); ++it)	//reviewing different ways of iteration 
		cout << it->c_str() << ' ';
	cout << endl << endl;

	//Inserting Duplicate element
	//Insert returns a pair that may flag error
	auto responsePair = strSet.insert("aaa");		//see second insert for information on auto

	//pair's second element is boolean (false if insert faied)
	cout << "The insert " << (responsePair.second == false ? "failed." : "passed.") << endl;

	//pair's first element is iterator at 1) newly inserted element or 2) the element that made it fail (an identical element to the attempted insert)
	cout << "element with specficiation: " << responsePair.first->c_str() << endl << endl;

	//second insert (this time to pass)
	string h = "happy";
	pair<set<string>::iterator, bool> responsePair2 = strSet.insert(h);
	if (responsePair2.second){
		cout << "insert passed" << endl;
		cout << *responsePair2.first << " was inserted" << endl;
	}
	else {
		cout << "insert failed" << endl;
		cout << h << " was not inserted" << endl;
		cout << "set contained: " << *responsePair2.first << " already." << endl;
	}


	multiset<string> multiset;
	multiset.insert("aaa");
	multiset.insert("aaa");
	multiset.insert("bbb");
	//just returns iterator for multiset - points the last of duplicates
	auto rp = multiset.insert("aaa");	//this only returns an iterator
	for (; rp != multiset.end(); ++rp){
		cout << *rp << ' ';
	} cout << endl;

	rp = multiset.insert("aaa");
	//iterate backwards to show iterator poitns to last added element in multiset
	while (true){
		cout << *rp << ' ';
		if (rp != multiset.begin()){
			rp--;
		}
		else {
			//get out of while loop
			break;
		}
	}
}

//concept set test questions
//create a set
//insert elements into a set
//find elements in a set
//erase element in set if it was found  - erase requires iterator, so you can't erase non-existent 
//check if an insert was sucessful
//		-a pair is returned: first element = iterator, second element = boolean of status of insert
//		-iterator points to either new element inserted, or the element that was identical to it (and prevented it from being inserted)
// multisetes exist - their insert just returns an iterator to the inserted element (which is the last element)