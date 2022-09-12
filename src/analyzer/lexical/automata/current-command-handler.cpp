#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "./alphanumeric-handler.cpp"
#include "./number-handler.cpp"
#include "./operator-handler.cpp"
#include "./delimiter-handler.cpp"

/**
 * @brief 
 * 
 * @param command 
 * @param characterStopped 
 * @return Token
 * 
 * State s0
 */
Token handleCurrentCommandVerification(string command, int *characterStopped)
{
    string currentCharacter (1, command[*characterStopped]);
    if (isalpha(command[*characterStopped]))
    {
        return handleAlphanumericThatCanBeAnIdentifierOrKeyword(command, characterStopped);
    }
    if (isdigit(command[*characterStopped]))
    {
        return handleNumbersAndThrowIfThereIsALetter(command, characterStopped);
    }
    if (isAnOperator(currentCharacter)) {
        return handleOperators(command, characterStopped);
    }
    if (isADelimiter(currentCharacter)) {
        return handleDelimitersThatCanBeOperatorOrDelimiter(command, characterStopped);
    }
    throw runtime_error("Error: unrecognized character " + command[*characterStopped]);
}