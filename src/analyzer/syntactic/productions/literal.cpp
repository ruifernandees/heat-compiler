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

bool literal(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (tokens[currentToken].type != NUMBER)
    {
        return false;
    }
    eat(currentToken);

    // possibilidade 2
    symbol(tokens, currentToken);
}
