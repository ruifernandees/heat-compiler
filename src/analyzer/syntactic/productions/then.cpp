#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
// include "./index.cpp"

#pragma once

using namespace std;


bool then(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // 1 e 3 possibilidade
    if (term(tokens, currentToken)) {
        int pstToken = *currentToken;

        // 3 possibilidade
        if (tokens[*currentToken].content.compare("then") != 0) {
            eat(currentToken);
            return true;
        }

        *currentToken = pstToken;

        // 1 possibilidade
        return true;
    }

    *currentToken = pastToken;

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("then") == 0) {
        eat(currentToken);
        return true;
    }

    *currentToken = pastToken;

    return false;
}