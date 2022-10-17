#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool args(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (arg(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);
            return true;
        }

    }

    // pode ser vazio
    arg(tokens, currentToken);

    *currentToken = pastToken;

    return false;
}