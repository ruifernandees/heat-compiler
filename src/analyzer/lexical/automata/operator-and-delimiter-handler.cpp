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

Token classifyWordIntoOperatorOrDelimiter(string command, int currentPosition, int initialPosition)
{
    string word = restoreWord(command, currentPosition, initialPosition);
    if (isAnOperator(word))
    {
        // cout << word << " is a operator" << endl;
        return operatorsTokenObjectFactory(word);
    }
    if (isADelimiter(word))
    {
        // cout << word << " is a delimiter" << endl;
        return delimiterTokenObjectFactory(word);
    }
    // cout << word << " unrecognized character" << endl;
    throw runtime_error("Error: unrecognized character - " + word);
}

/**
 * @brief 
 * 
 * @param command 
 * @param pos 
 * @return Token
 * 
 * State S3
 */
Token handleOperatorAndDelimiterAndThrowIfIsInvalid(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (isalnum(command[i]) != 0)
        {
            Token token = classifyWordIntoOperatorOrDelimiter(command, i, *pos);
            *pos = i;
            return token;
        }
    }
    Token token = classifyWordIntoOperatorOrDelimiter(command, command.length(), *pos);
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    return token;
}