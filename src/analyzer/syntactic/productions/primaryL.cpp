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


bool primaryL(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    if (tokens[*currentToken].content.compare("::"))
        return false;
    eat(currentToken);
    identifier(tokens, currentToken);
    primaryL(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("["))
        return false;
    eat(currentToken);
    args(tokens, currentToken);
    if (tokens[*currentToken].content.compare("]"))
        return false;
    primaryL(tokens, currentToken);
}