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


bool funcaoArgsComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

bool args(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (arg(tokens, currentToken)) {
        while (funcaoArgsComAsterisco(tokens, currentToken)) {}
        return true;
    }

    *currentToken = pastToken;

    return false;
}
