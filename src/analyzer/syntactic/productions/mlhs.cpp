#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool mlhs(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (mlhs_item(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);
            if (mlhs_item(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare(",") == 0) {
                    eat(currentToken);
                    // pode ser vazio VV
                    if (mlhs_item(tokens, currentToken)) {
                        if (tokens[*currentToken].content.compare("*") == 0) {
                            eat(currentToken);
                            if (lhs(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                    return true; //porque pode ser vazio
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (lhs(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}