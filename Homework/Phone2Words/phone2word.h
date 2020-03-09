#ifndef  PHONE2WORD
#define PHONE2WORD
#include <string>
#include <map>
#include <vector>

std::vector< std::string > all_combinations( 
        std::string const& phone_number,      // number to convert
        std::map<char,std::string> & keypad   // mapping on the keypad - I may use a non-standard mapping
        );
#endif
