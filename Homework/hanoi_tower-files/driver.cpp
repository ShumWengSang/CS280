#include "hanoi-tower.h"
#include <string>
#include <iostream>
#include <regex>    /* regular expression */

void run_1( int n ) // directly to std::cout
{
    hanoi_tower_1( n, []( std::string const& str ) { std::cout <<  str << std::endl; } );
}

void run_2( int n ) // directly to std::cout
{
    hanoi_tower_2( n, []( std::string const& str ) { std::cout <<  str << std::endl; } );
}

void run_3( int n ) // directly to std::cout
{
    hanoi_tower_3( n, []( std::string const& str ) { std::cout <<  str << std::endl; } );
}

// only prints lines containing a given string
// see tests below - I print lines containing a specific disk
// notice the number of lines (movements) for each disk
void run1_regex( int n, std::regex const& re )
{
    hanoi_tower_1( n, [&re]( std::string const& str ) {
            if ( std::regex_search( str, re ) ) {
                std::cout <<  str << std::endl; 
            } 
        } 
    );
}

// print every period'th move, for large outputs
void run2_count( int n, int period )
{
    hanoi_tower_2( n, [&period]( std::string const& str ) {
            static int c = 0;
            if ( c++ % period == 0 ) {
                std::cout <<  str << std::endl; 
            } 
        }
    );
}

// print every period'th move, for large outputs
void run3_count( int n, int period )
{
    hanoi_tower_3( n, [&period]( std::string const& str ) {
            static int c = 0;
            if ( c++ % period == 0 ) {
                std::cout <<  str << std::endl; 
            } 
        }
    );
}

void test0() { run_1( 3 ); }
void test1() { run_1( 4 ); }
void test2() { run_1( 5 ); }
// only print moves that involve a specific disk
void test3() { run1_regex( 12, std::regex( ".*12.*" ) ); } // check out the number of lines in output
void test4() { run1_regex( 12, std::regex( ".*11.*" ) ); } // check out the number of lines in output
void test5() { run1_regex( 12, std::regex( ".*10.*" ) ); } // check out the number of lines in output
void test6() { run1_regex( 12, std::regex( ".*9.*"  ) ); } // check out the number of lines in output
// with "pictures" -- extra
void test7() { run_2( 3 ); }
void test8() { run_2( 4 ); }
void test9() { run_2( 5 ); }
void test10() { run_2( 6); }
void test11() { run2_count( 8, 10 ); }
void test12() { run2_count( 9, 100 ); }
// with fancy "pictures" -- extra
void test13() { run_3( 3 ); }
void test14() { run_3( 4 ); }
void test15() { run_3( 5 ); }
void test16() { run_3( 6); }
void test17() { run_3( 7); }
void test18() { run3_count( 9, 100); }
void test19() { run3_count( 10, 1000); }
void test20() { run3_count( 12, 10000); }

void (*pTests[])() = { test0, test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11, test12, test13, test14, test15, test16, test17, test18, test19, test20 };

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
