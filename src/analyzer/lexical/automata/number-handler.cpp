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
 * State S2
 */
void handleNumbersAndThrowIfThereIsALetter(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isdigit(command[i]))
        {
            if (isalpha(command[i]))
            {
                cout << "error (number + character)" << endl;
                *pos = WAS_ENTIRE_COMMAND_VERIFIED;
                throw runtime_error("Error: invalid identifier (number + character).");
            }
            else
            {
                string number = restoreWord(command, i, *pos);
                cout << number << " is a number" << endl;
                *pos = i; // caractere especial continuar verificacao do comando
            }
            return;
        }
    }
    string number = restoreWord(command, command.length(), *pos);
    cout << number << " is a number" << endl;
    *pos = WAS_ENTIRE_COMMAND_VERIFIED;
}