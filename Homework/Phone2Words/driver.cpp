#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> // std::sort

#include "phone2word.h"

void init_standard_keypad( std::map< char, std::string > & keypad ) {
    keypad[ '0' ] = "0";  
    keypad[ '1' ] = "1";  
    keypad[ '2' ] = "abc";
    keypad[ '3' ] = "def";
    keypad[ '4' ] = "ghi";
    keypad[ '5' ] = "jkl";
    keypad[ '6' ] = "mno";
    keypad[ '7' ] = "pqrs";
    keypad[ '8' ] = "tuv";
    keypad[ '9' ] = "wxyz";
}

void init_keypad( std::map< char, std::string > & keypad ) {
    keypad[ '0' ] = "ab";  
    keypad[ '1' ] = "cd";  
    keypad[ '2' ] = "ef";
    keypad[ '3' ] = "ghi";
    keypad[ '4' ] = "jkl";
    keypad[ '5' ] = "m";
    keypad[ '6' ] = "no";
    keypad[ '7' ] = "pq";
    keypad[ '8' ] = "rstuvwx";
    keypad[ '9' ] = "yz";
}

void test0()
{
    std::string pn( "3456" );
    // init keypad map
    std::map<char,std::string> keypad;
    init_standard_keypad( keypad );

    std::vector< std::string > res = all_combinations( pn, keypad );
    std::sort( res.begin(), res.end() );
    std::cout << "Got " << res.size() << " words" << std::endl;
    for ( auto const& s : res ) { std::cout << s << std::endl; }
}

void test1()
{
    std::string pn( "13579" );
    // init keypad map
    std::map<char,std::string> keypad;
    init_standard_keypad( keypad );

    std::vector< std::string > res = all_combinations( pn, keypad );
    std::sort( res.begin(), res.end() );
    std::cout << "Got " << res.size() << " words" << std::endl;
    for ( auto const& s : res ) { std::cout << s << std::endl; }
}

void test2()
{
    std::string pn( "0125679679" );
    // init keypad map
    std::map<char,std::string> keypad;
    init_keypad( keypad ); // non standard

    std::vector< std::string > res = all_combinations( pn, keypad );
    std::sort( res.begin(), res.end() );
    std::cout << "Got " << res.size() << " words" << std::endl;
    for ( auto const& s : res ) { std::cout << s << std::endl; }
}

void test3()
{
    std::string pn( "2718281828459045" );
    // init keypad map
    std::map<char,std::string> keypad;
    init_standard_keypad( keypad ); // non standard

    std::vector< std::string > res = all_combinations( pn, keypad );
    // std::sort( res.begin(), res.end() );
    std::cout << "Got " << res.size() << " words" << std::endl;
    // for ( auto const& s : res ) { std::cout << s << std::endl; }
}

void (*pTests[])() = { test0, test1, test2, test3 };

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
    //pTests[0]();
	return 0;
}
