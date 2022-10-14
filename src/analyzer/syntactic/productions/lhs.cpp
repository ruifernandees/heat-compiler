#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./stmt.cpp"

#pragma once

using namespace std;

bool lhs(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    variable(tokens, currentToken);

    // possibilidade 2
    primary(tokens, currentToken);
    if (tokens[*currentToken].content.compare("["))
        return false;
    eat(tokens, currentToken);
    args(tokens, currentToken);
    if (tokens[*currentToken].content.compare("]"))
        return false;
    eat(tokens, currentToken);

    // possibilidade 3
    primary(tokens, currentToken);
    if (tokens[*currentToken].content.compare("."))
        return false;
    eat(tokens, currentToken);

    identifier(tokens, currentToken);
}