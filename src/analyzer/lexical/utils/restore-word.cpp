#include <string>
#include <vector>
#include <cstring>
#include <regex>

#pragma once

using namespace std;

/**
 * @brief 
 * 
 * @param command 
 * @param currentPosition 
 * @param initialPosition 
 * @return string 
 */
string restoreWord(string command, int currentPosition, int initialPosition)
{
    string word;
    for (int y = initialPosition; y < currentPosition; y++)
    {
        word.push_back(command[y]);
    }
    return word;
}