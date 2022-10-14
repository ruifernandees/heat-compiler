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


bool arglist(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    identifier(tokens, currentToken);
    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    // varios ou vazio
    identifier(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    if (tokens[*currentToken].content.compare(","))
        return false;
    eat(currentToken);

    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);

    // possibilidade 3
    if (tokens[*currentToken].content.compare("&"))
        return false;
    eat(currentToken);

    identifier(tokens, currentToken);
}