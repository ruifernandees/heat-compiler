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
 */
void handleCurrentCommandVerification(string command, int *characterStopped)
{
    if (isalpha(command[*characterStopped]))
    {
        handleAlphanumericThatCanBeAnIdentifierOrKeyword(command, characterStopped);
    }
    else if (isdigit(command[*characterStopped]))
    {
        handleNumbersAndThrowIfThereIsALetter(command, characterStopped);
    }
    else
    {
        handleOperatorAndDelimiterAndThrowIfIsInvalid(command, characterStopped);
    }
}