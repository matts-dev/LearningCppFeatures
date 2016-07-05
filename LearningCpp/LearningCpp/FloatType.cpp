//Float Data Type 
//Matt Stone 6/29/16

#include<cstdio>

using namespace std;

void floats(){
	//Float sizes are not guaranteed across platforms
	printf("float size: -------- %ld\n", sizeof(float));
	printf("double size: ------- %ld\n", sizeof(double));
	printf("long double size: -- %ld\n\n", sizeof(long double));

	float x = 500.0;		//do not need to use 500.0f like in java; though this is valid
	x = 500.0f;

	double y = 5E2;
	long double z = 12345.54321;
	printf("%.1f, %.1lf, %.1lf\n\n", x, y, z);

	x = (float)(.1 + .1 + .1);
	y = .3;


	printf("comparing x:%.1f and y:%.1lf\n", x, y);
	printf("Are x and y equal? (true/false): ");
	if (x == y){
		printf("true\n\n");
	}
	else {
		printf("false\n\n");
	}
	
	//floating points have small variations in precision
	printf("floating points are not perfectly accurate\n");
	printf("x: %.9f\n", x);
	printf("y: %.9f\n\n", y);

	//you can check for this by using greater/lesser than signs
	printf("making a comparison between x and y using a tolerance: \n");
	double tolerance = 1E-7;	//you will have to decided what level of tolerance is required
	if (x < y + tolerance && x > y - tolerance){
		printf("true\n");
	}
	else {
		printf("false\n");
	}


}