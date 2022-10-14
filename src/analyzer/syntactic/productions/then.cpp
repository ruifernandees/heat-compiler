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


bool then(vector<Token> tokens, int* currentToken) {
    // 1 possibilidade
    term(tokens, currentToken);

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("then") != 0) {
        return false;
    }
    eat(tokens, currentToken);

    // 3 possibilidade
    term(tokens, currentToken);
    if (tokens[*currentToken].content.compare("then") != 0) {
        return false;
    }
    eat(tokens, currentToken);
}