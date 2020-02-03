// all calculation are in integers
// i.e. 5/2 = 2
// input expression cna only have single digit values

#include <iostream>
#include "infix2postfix.h"

void test0() {
    std::cout << Evaluate( Infix2postfix( "1+2+3" ) ) << std::endl;
}
void test1() {
    std::cout << Evaluate( Infix2postfix( "1*2+3" ) ) << std::endl;
}
void test2() {
    std::cout << Evaluate( Infix2postfix( "1+2*3" ) ) << std::endl;
}
void test3() {
    std::cout << Evaluate( Infix2postfix( "(1+2)*3" ) ) << std::endl;
}
void test4() {
    std::cout << Evaluate( Infix2postfix( "1+(2*3)" ) ) << std::endl;
}
void test5() {
    std::cout << Evaluate( Infix2postfix( "(3-6*(0-4)/2)-(2*7-7*8)" ) ) << std::endl;
}
void test6() {
    std::cout << Evaluate( Infix2postfix( "(1+2*4)*5-(4-1)" ) ) << std::endl;
}

void (*pTests[])() = { test0,test1,test2,test3,test4,test5,test6 };

void test_all() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i) 
		pTests[i]();
}

#include <cstdio>   //sscanf
int main (int argc, char ** argv) {
	if (argc >1) {
		int test = 0;
		std::sscanf(argv[1],"%i",&test);
		try {
            pTests[test]();
		} catch( const char* msg) {
			std::cerr << msg << std::endl;
		}
	}
	return 0;
}
// (3-6*(0-1)/2)-(2*7-7*8) - problem
// (3-6*(0-4)/2)-(2*7-7*8)=57
