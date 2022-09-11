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
 * State S2
 */
Token handleNumbersAndThrowIfThereIsALetter(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isdigit(command[i]))
        {
            if (isalpha(command[i]))
            {
                // cout << "error (number + character)" << endl;
                *pos = WAS_ENTIRE_COMMAND_VERIFIED;
                throw runtime_error("Error: invalid identifier (number + character).");
            }
            string number = restoreWord(command, i, *pos);
            Token token = numberTokenObjectFactory(number);
            // cout << number << " is a number" << endl;
            *pos = i; // caractere especial continuar verificacao do comando
            return token;
        }
    }
    string number = restoreWord(command, command.length(), *pos);
    Token token = numberTokenObjectFactory(number);
    // cout << number << " is a number" << endl;
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    return token;
}