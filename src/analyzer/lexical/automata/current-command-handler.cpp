#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "./alphanumeric-handler.cpp"
#include "./number-handler.cpp"
#include "./operator-and-delimiter-handler.cpp"
#include "./s4.cpp"
#include "./s3.cpp"

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
    // cout << "character stopped "  << currentCharacter << endl;
    if (isalpha(command[*characterStopped]))
    {
        return handleAlphanumericThatCanBeAnIdentifierOrKeyword(command, characterStopped);
    }
    if (isdigit(command[*characterStopped]))
    {
        return handleNumbersAndThrowIfThereIsALetter(command, characterStopped);
    }
    if (isAnOperator(currentCharacter)) {
        // cout << "is an operator " << command[*characterStopped] << endl;
        return s4(command, characterStopped);
    }
    if (isADelimiter(currentCharacter)) {
        return s3(command, characterStopped);
    }
    throw runtime_error("Error: unrecognized character " + command[*characterStopped]);
    // return handleOperatorAndDelimiterAndThrowIfIsInvalid(command, characterStopped);
}