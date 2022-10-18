#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool assocs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (assoc(tokens, currentToken)) {
        // varios ou vazio
        while(funcaoComAsterisco(tokens, currentToken)) {}
        return true;
    }
    
    *currentToken = pastToken;
    return false;
}

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (assoc(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}