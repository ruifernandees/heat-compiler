#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./expr.cpp"

#pragma once

using namespace std;

bool variable(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    varname(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("nil") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 3
    if (tokens[*currentToken].content.compare("self") != 0) {
        return false;
    }
    eat(currentToken);
}
