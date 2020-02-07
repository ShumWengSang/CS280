#define _CRT_SECURE_NO_WARNINGS
#include "subsets.h"

void run( int n )
{
    std::vector<int> set;
    for( int i=0; i<n; ++i ) {
        set.push_back( i );
    }
    subsets( set );
}

void test0() { run( 1 ); }
void test1() { run( 2 ); }
void test2() { run( 3 ); }
void test3() { run( 4 ); }
void test4() { run( 5 ); }
void test5() { run( 6 ); }
void test6() { run( 7 ); }

void (*pTests[])() = { test0, test1, test2, test3, test4, test5, test6 };

#include <cstdio>   //sscanf
int main(int argc, char** argv)
{
    if ( argc > 1 ) {
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

