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

bool command(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    operation(tokens, currentToken);
    call_args(tokens, currentToken);

    // possibilidade 2
    primary(tokens, currentToken);
    
    if (tokens[*currentToken].content.compare(".") != 0) {
        return false;
    }
    eat(currentToken);
    operation(tokens, currentToken);
    call_args(tokens, currentToken);
    
    // possibildade 3
    primary(tokens, currentToken);
    if (tokens[*currentToken].content.compare("::") != 0) {
        return false;
    }
    eat(currentToken);
    operation(tokens, currentToken);
    call_args(tokens, currentToken);
    
    // possibilidade 4
    if (tokens[*currentToken].content.compare("super") != 0) {
        return false;
    }
}