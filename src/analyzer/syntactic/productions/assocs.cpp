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


bool funcaoAssocsComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        if (assoc(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

bool assocs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (assoc(tokens, currentToken)) {
        // varios ou vazio
        while(funcaoAssocsComAsterisco(tokens, currentToken)) {}
        return true;
    }
    
    *currentToken = pastToken;
    return false;
}
