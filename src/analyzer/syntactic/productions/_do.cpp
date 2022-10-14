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

bool _do(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    term(tokens, currentToken);
    eat(currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("do") != 0) {
        return false;
    }
    eat(currentToken);

    // possibilidade 3
    term(tokens, currentToken);
    eat(currentToken);

    if (tokens[*currentToken].content.compare("do") != 0) {
        return false;
    }
}
