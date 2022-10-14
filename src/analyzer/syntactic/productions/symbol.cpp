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

bool symbol(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (tokens[*currentToken].content.compare(":") != 0) {
        return false;
    }
    eat(currentToken);

    fname(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare(":") != 0) {
        return false;
    }
    eat(currentToken);

    varname(tokens, currentToken);
}
