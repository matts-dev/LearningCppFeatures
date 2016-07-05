//Demonstrating header files for classes
//Matt Stone 6/16/16

class TwoFileClass{
public:
	TwoFileClass();
	~TwoFileClass();
	void talk();
	int x = 0;
private:
	int y = 0xFFFF;
protected:
	int z = 0XABCD;
};