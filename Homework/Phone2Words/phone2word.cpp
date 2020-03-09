//
// Created by roland on 2/20/20.
//

#include "phone2word.h"

void recursive_result(std::vector<std::string>& result, const char* phone_number,
        std::map<char, std::string>& keypad, std::string currentString)
{
    if(phone_number[0] == '\0')
    {
        result.push_back(currentString);
        return;
    }
    char currentChar = phone_number[0];
    const std::string& tempPaths = keypad[currentChar];

    for(const char& possible : tempPaths)
    {
        std::string toBePassed;
        if(currentString.empty())
        {
            toBePassed.push_back(possible);
            recursive_result(result, phone_number + 1, keypad, toBePassed);
        }
        else
        {
            toBePassed = currentString;
            toBePassed.push_back(possible);
            recursive_result(result, phone_number + 1, keypad, toBePassed);
        }
    }
}

std::vector<std::string> all_combinations(std::string const &phone_number, std::map<char, std::string> &keypad)
{
    std::vector<std::string> result;

    recursive_result(result, phone_number.c_str(), keypad, "");

    return result;
}
