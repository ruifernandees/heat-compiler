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
#include "../utils/factories.cpp"

#include "../types.h"

Token classifyWordIntoKeywordOrIdentifier(string command, int currentPosition, int initialPosition)
{
    string word = restoreWord(command, currentPosition, initialPosition);
    // cout << "S1 classifying ["  << word << "]" << endl;
    if (isAKeyword(word))
    {
        return keywordTokenObjectFactory(word);
    }
    return identifierTokenObjectFactory(word);
}

/**
 * @brief 
 * 
 * @param command 
 * @param pos 
 * @return Token
 * 
 * State S1
 */
Token handleAlphanumericThatCanBeAnIdentifierOrKeyword(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isalnum(command[i]) && !(command[i] == '_'))
        {
            Token token = classifyWordIntoKeywordOrIdentifier(command, i, *pos);
            *pos = i;
            return token;
        }
    }
    Token token = classifyWordIntoKeywordOrIdentifier(command, command.length(), *pos);
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    return token;
}