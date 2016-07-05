//name spaces
//matt stone 6/24/16
#include<string>
#include<iostream>

namespace CustomString{
	class string{
	private:
		char* underlyingstring;
		size_t	_size;
	public:
		explicit string(char* arg);
		size_t size();
	};

	string::string(char* arg){
		underlyingstring = arg; //shallow, could use a vector to build from source
		for (int i = 0; i < 1024; ++i){
			if (arg[i] == 0){
				_size = i;
				break;
			}
		}
	};
	size_t string::size(){
		return _size;
	}

}; //end namespace customString

//using namespace std;
//using CustomString::string;
using std::cout;
using std::endl;

void namespaces(){
	std::string test1("string");
	CustomString::string test2("string");

	std::cout << "std string size" << test1.size() << endl;
	cout << "custom string size method" << test2.size() << endl;
}