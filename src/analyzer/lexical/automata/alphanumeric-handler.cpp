#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"

#include "../utils/restore-word.cpp"

/**
 * @brief 
 * 
 * @param command 
 * @param pos 
 * 
 * State S1
 */
void handleAlphanumericThatCanBeAnIdentifierOrKeyword(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isalnum(command[i]))
        {
            string word = restoreWord(command, i, *pos);
            if (isAKeyword(word))
            {
                cout << word << " is a keyword" << endl;
            }
            else
            {
                cout << word << " is a identifier" << endl;
            }
            *pos = i;
            return;
        }
    }

    string word = restoreWord(command, command.length(), *pos);
    if (isAKeyword(word))
    {
        cout << word << " is a keyword" << endl;
    }
    else
    {
        cout << word << " is a identifier" << endl;
    }
    // passou pela string toda
    *pos = -1;
}