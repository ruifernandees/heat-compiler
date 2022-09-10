#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "./alphanumeric-handler.cpp"
#include "./number-handler.cpp"
#include "./operator-and-delimiter-handler.cpp"

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
    if (isalpha(command[*characterStopped]))
    {
        return handleAlphanumericThatCanBeAnIdentifierOrKeyword(command, characterStopped);
    }
    if (isdigit(command[*characterStopped]))
    {
        return handleNumbersAndThrowIfThereIsALetter(command, characterStopped);
    }
    return handleOperatorAndDelimiterAndThrowIfIsInvalid(command, characterStopped);
}