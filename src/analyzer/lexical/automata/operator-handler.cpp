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

/**
 * @brief 
 * 
 * @param command 
 * @param pos 
 * @return Token 
 * 
 * State S4
 */
Token handleOperators(string command, int *pos) {
    for (int i = *pos; i < command.length(); i++)
    {
        string word = restoreWord(command, i+1, *pos);
        if (!isAnOperator(word)) {
            word = restoreWord(command, i, *pos);
            *pos = i;
            return operatorsTokenObjectFactory(word);
        }
    }
    string word = restoreWord(command, command.length(), *pos);
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    return operatorsTokenObjectFactory(word);
}