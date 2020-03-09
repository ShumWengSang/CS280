#include <iostream>
#include "catalan.h"

void test0() { 
    std::cout << catalan3( 3 ) << std::endl; 
    std::cout << catalan3( 5 ) << std::endl; 
    std::cout << catalan3( 7 ) << std::endl; 
}

void test1() { 
    std::cout << catalan4( 4 ) << std::endl; 
    std::cout << catalan4( 5 ) << std::endl; 
    std::cout << catalan4( 7 ) << std::endl; 
}

void test2() {
    std::cout << catalan2( 4 ) << std::endl;
    std::cout << catalan( 4, 2 ) << std::endl;
}

void test3() { 
    std::cout << catalan3( 4 ) << std::endl;
    std::cout << catalan( 4, 3 ) << std::endl;
}

void test4() { 
    std::cout << catalan3( 5 ) << std::endl;
    std::cout << catalan( 5, 3 ) << std::endl;
}

void test5() { 
    std::cout << catalan( 10, 5 ) << std::endl;
}

void test6() { 
    std::cout << catalan( 8, 7 ) << std::endl;
}


// n'th catalan number may be shown to be
//    (2n)!
//   -------
//   (n+1)!n!
// n = 19 gives 1.767.263.190 (n=20 is overfloat error)
void (*pTests[])() = { test0,test1,test2,test3,test4,test5,test6 };

void test_all() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0]); ++i) 
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
