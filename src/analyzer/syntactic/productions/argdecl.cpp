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


bool argdecl(vector<Token> tokens, int* currentToken) {
    // possibilidade 1
    if (tokens[*currentToken].content.compare("("))
        return false;
    eat(currentToken);
    arglist(tokens, currentToken);

    if (tokens[*currentToken].content.compare(")"))
        return false;
    eat(currentToken);

    // possibilidade 2
    arglist(tokens, currentToken);
    term(tokens, currentToken);
}