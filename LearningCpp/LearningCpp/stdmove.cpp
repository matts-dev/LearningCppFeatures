//the standard move function
//Matt Stone 7/17/16

#include<iostream>
#include<vector>
#include<string>

using namespace std;

// x = sqrt(Y) 		//this statement requires 3 copies
// sqrt(Y)			//takes a "copy-by-value" of Y
// sqrt(Y)			//returns a "copy-by-value" of the result
// x =				// makes a copy of the R value (and then assigns it)

//move semantics reduce these copies (or allow moving of hard to copy data)

template<typename T>
void swap(T& lhs, T& rhs) {
	cout << "custom swap" << endl;
	T temp = move(lhs);
	lhs = move(rhs);
	rhs = move(temp);
}

//move allows the moving of data without the need for copying.
void stdmoves() {
	//some vectors to work with
	vector<string> v1 = { "one", "two", "three" };
	vector<string> v2 = { "blue", "green", "purple", "red" };

	//using different sizes to distinguish the vectors
	cout << "v1:" << v1.size() << endl;
	cout << "v2:" << v2.size() << endl;


	cout << endl << "moving r-value with move" << endl;
	//move v1 data into v2
	v2 = std::move(v1);

	cout << "v1:" << v1.size() << endl;
	cout << "v2:" << v2.size() << endl;

	for (size_t i = 0; i < v2.size(); ++i) {
		cout << v2[i] << " ";
	}

	v1.push_back("blue");
	v1.push_back("yellow");

	cout << "\n\nv1:" << v1.size() << endl;
	cout << "v2:" << v2.size() << endl;

	::swap(v1, v2);
	cout << "v1:" << v1.size() << endl;
	cout << "v2:" << v2.size() << endl;

}
 