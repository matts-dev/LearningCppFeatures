//escape sequences
//Matt Stone 6/30/16

#include<cstdio>

void escapes(){
	puts("\t, \\, \", \', \n");

	puts("hex: \x40 \x69 \x91");
	//puts("Unicode: \u03bc");		//not supported in current page
	puts("oct: \017");
};