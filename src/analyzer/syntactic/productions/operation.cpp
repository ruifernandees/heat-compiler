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


bool operation(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    identifier(tokens, currentToken);

    // possibilidade 2
    identifier(tokens, currentToken);
    if (tokens[*currentToken].content.compare("!"))
        return false;
    eat(currentToken);

    // possibilidade 3
    identifier(tokens, currentToken);
    if (tokens[*currentToken].content.compare("!"))
        return false;
    eat(currentToken);
}