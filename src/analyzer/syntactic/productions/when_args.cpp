#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "./stmt.cpp"

#pragma once

using namespace std;


bool when_args(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // 1 possibilidade
    if (args(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);
            if (tokens[*currentToken].content.compare("*") == 0) {
                eat(currentToken);
                if (arg(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // 2 possibilidade
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}