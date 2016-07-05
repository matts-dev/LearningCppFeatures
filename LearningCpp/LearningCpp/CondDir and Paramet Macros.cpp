//conditional preprocessor directives
//Matt Stone 6/21/2016

//conditonals in preprocessor langauge 

//#if                 //detmines if variable defined
//#elif				  //else if (checks another variable
//#else				  //if all if and elif fail, this will happen
//#ifdef              //determines if a directive is defined 
//#ifndef			  //does something if directive wasn't defined
//#endif			  //is the end if a directive ifs

//#if defined(MACRO)	== ifdef
//#if !defined(MACRO)  == if#endif

#define A 0
#define B 1		//may be any number, other than 0
#define C 0
#define D 0

//#define DIRECTIVE 1		//remove comment to change preprocessor behavior

//function maros
#define MAX(a, b) ((a > b) ? 1 : 0)
#define SQUARE(x) (x)   \
              *			\
             (x)		//the above \ must be the last line 

#ifndef COND_H	
#define COND_H			//if you leave value out, many macros can be defined
#define MAXA 10
#define MAXB 20
#define MAXC 30
#define MAXD 40
#else
#define MAXA -10
#define MAXB -20
#define MAXC -30
#define MAXD -40
#endif

#ifdef DIRECTIVE
#define NUMBER 99
#else
#define NUMBER -99
#endif

#if defined(DIRECTIVE)
#define ALTERNATIVE 1
#else
#define ALTERNATIVE -1
#endif


#include<iostream>
using namespace std;

void condDirs(void){
	int max = 0;
	//thse could be used to define different behavior depending upon the operating system
#if A 
	max = 10;
#elif B
	max = 20;
#elif C
	max = 30;
#elif D
	max = 40;
#else 
	max = -1;
#endif

	cout << max << endl;
	cout << "maximum function macro " << MAX(max, 10) << endl;
	cout << "large function macro" <<  SQUARE(2) << endl;
	cout << NUMBER << endl;
	cout << ALTERNATIVE << endl;
}

//self test 
//what is the difference betwen #if and #ifdef?					<one is for macros, one is for directives>
//what must you include after an #if or #ifdef?
//make a function macro
//make a maro containing a constant variable
//how does the preprocessor work? Are macros like variables?		<it changes the actual source code sent to compiler>
