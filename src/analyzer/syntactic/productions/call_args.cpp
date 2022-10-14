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


bool call_args(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    args(tokens, currentToken);

    // possibilidade 2
    args(tokens, currentToken);
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);
    assocs(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    // possibilidade 3
    assocs(tokens, currentToken);
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    // possibilidade 4
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);
    
    arg(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    // possibilidade 5
    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    arg(tokens, currentToken);

    // possibilidade 6
    command(tokens, currentToken);
}