#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/identifiers.h"
#include "../../../bnf/types.h"

#include "../utils/restore-word.cpp"
#include "../utils/factories.cpp"

#include "../types.h"

Token classifyWordIntoKeywordOrIdentifier(string command, int currentPosition, int *initialPosition)
{
    string word = restoreWord(command, currentPosition, *initialPosition);
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
            string word = restoreWord(command, i, *pos);
            *pos = i;
            if (isAnIdentifierEndCharacter(command[i])) {
                word += command[i];
                if (i + 1 < command.length()) {
                    *pos += 1;
                } else {
                    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
                }
            } else if (isAKeyword(word)) {
                return keywordTokenObjectFactory(word);
            }
            return identifierTokenObjectFactory(word);
        }
    }
    Token token = classifyWordIntoKeywordOrIdentifier(command, command.length(), pos);
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    return token;
}