#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"

#include "../utils/restore-word.cpp"

#include "../types.h"

/**
 * @brief 
 * 
 * @param command 
 * @param pos 
 * 
 * State S3
 */
void handleOperatorAndDelimiterAndThrowIfIsInvalid(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (isalnum(command[i]) != 0)
        {
            string word = restoreWord(command, i, *pos);
            if (isAnOperator(word))
            {
                cout << word << " is a operator" << endl;
            }
            else if (isADelimiter(word))
            {
                cout << word << " is a delimiter" << endl;
            }
            else
            {
                cout << word << " unrecognized character" << endl;
            }
            *pos = i;
            return;
        }
    }

    string word = restoreWord(command, command.length(), *pos);
    if (isAnOperator(word))
    {
        cout << word << " is a operator" << endl;
    }
    else if (isADelimiter(word))
    {
        cout << word << " is a delimiter" << endl;
    }
    else
    {
        cout << word << " unrecognized character" << endl;
    }
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
}