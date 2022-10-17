#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool then(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // 1 possibilidade
    if (term(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("then") == 0) {
        eat(currentToken);
        return true;
    }

    *currentToken = pastToken;

    // 3 possibilidade
    if (term(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("then") != 0) {
            eat(currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}