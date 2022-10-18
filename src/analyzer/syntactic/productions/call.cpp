#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool call(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // 1 possibilidade
    if (Function(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    // 2 possibilidade
    if (command(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    return false;
}