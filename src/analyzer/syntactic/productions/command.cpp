#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;

bool command1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (operation(tokens, currentToken)) {
        if (call_args(tokens, currentToken)) {return true;}
    }
    return false;
}

bool command2(vector<Token> tokens, int* currentToken)
{
    // possibilidade 2 e 3
    if (primary(tokens, currentToken)) {
        // 2 e 3
        if (verify_content(tokens, currentToken, ".") || verify_content(tokens, currentToken, "::")) {
            if (operation(tokens, currentToken)) {
                if (call_args(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool command4(vector<Token> tokens, int* currentToken)
{
    // possibilidade 4
    if (verify_content(tokens, currentToken, "super")) {
        if (call_args(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool command(vector<Token> tokens, int* currentToken)
{
    return verify_productions(tokens, currentToken, {command1, command2, command4});
}