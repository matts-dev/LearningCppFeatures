//https://www.youtube.com/watch?v=QrDe8CK0x8U RTTI
//RRTI using dynamic cast and typeid
//Matt Stone 7/8/2016

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class shape {
public:
	virtual void id() = 0;
};

class circle : public shape {
public:
	void id() { cout << "circle" << endl; }
};

class sphere : public circle {
public:
	void id() { cout << "sphere" << endl; }
};

class rectangle : public shape {
public:
	void id() { cout << "rectangle" << endl; }
};

vector<circle*> getCirlcesTypeId(vector<shape*> list);
vector<shape*> generateShapes();
vector<circle*> getCirlcesDynCast(vector<shape*> list);

// ------------------------------------- MAIN ------------------------------------- 
void RTTIDynCastTypeID() {
	vector<shape*> shapes = generateShapes();
	//vector<circle*> circles = getCirlcesTypeId(shapes);
	vector<circle*> circles = getCirlcesDynCast(shapes);		//this will work like java instanceof
	for (circle* cptr : circles) {
		cptr->id();
	}

	//clean up memory
	for (shape* sptr : shapes) delete sptr;
}

// --------------------------------------------------------------------------------

vector<circle*> getCirlcesTypeId(vector<shape*> list) {
	vector<circle*> circles;
	for (shape* ptr : list) {
		if (typeid(*ptr) == typeid(circle)) {
			//this will not accept spheres, because it is only checking for concrete circle
			circles.push_back(static_cast<circle*>(ptr));
		}
	}

	return circles;
}

vector<circle*> getCirlcesDynCast(vector<shape*> list) {
	vector<circle*> circles;
	for (shape* ptr : list) {
		circle* cptr = dynamic_cast<circle*>(ptr);
		if (cptr != nullptr) {
			//this will take circles and spheres.
			circles.push_back(cptr);	//will only push back circles that match (not nullptr)
		}
	}

	return circles;
}

vector<shape*> generateShapes() {
	srand((unsigned int)time(0));
	vector<shape*> ret;

	for (int i = 0; i < 10; ++i) {
		int choice = (int)(rand() % 3);
		if (choice == 0) {
			ret.push_back(new rectangle);
		}
		else if (choice == 1) {
			ret.push_back(new circle);
		}
		else if (choice == 2) {
			ret.push_back(new sphere);
		}
	}
	return ret;
}


//self test
//will the typeId of a subclass and a base result in the same value (ie typeid.name())?		<no>
//what are the implications of the above?													<typeid will not correctly test for the dynamic type, each sub class must be tested for indepedently>
//how can you test for a dynamic type?					<if a class hierarchy has a virtual table, then you can use dynamic cast and check for null pointer>
//what does a dynamic cast do?							<at runtime, it attempts to cast the type of an object>
//what happens when a dynamic cast fails?				<it returns a nullptr>
//
