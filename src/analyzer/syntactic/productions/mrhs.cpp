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


bool mrhs(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    args(tokens, currentToken);
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(tokens, currentToken);
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(tokens, currentToken);
    arg(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(tokens, currentToken);
    arg(tokens, currentToken);
}