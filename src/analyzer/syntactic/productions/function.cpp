#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool Function(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (operation(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("(") == 0) {
            eat(currentToken);
            if (call_args(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare(")") == 0) {
                    eat(currentToken);
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(".") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("(") == 0) {
                    eat(currentToken);
                    if (call_args(tokens, currentToken)) {
                        if (tokens[*currentToken].content.compare(")") != 0) {
                            eat(currentToken);
                            return true;
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 3
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("::") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("(") == 0) {
                    eat(currentToken);
                    if (call_args(tokens, currentToken)) {
                        if (tokens[*currentToken].content.compare(")") == 0) {
                            eat(currentToken);
                            return true;
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 4
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(".") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                return true;
            }
        }    
    }
    
    *currentToken = pastToken;

    // possibilidade 5
    if (primary(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("::") == 0) {
            eat(currentToken);
            if (operation(tokens, currentToken)) {
                return true;
            }    
        }
    }

    *currentToken = pastToken;

    // possibilidade 6
    if (tokens[*currentToken].content.compare("super") == 0) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("(") == 0) {
            eat(currentToken);
            if (call_args(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare(")")) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 7
    if (tokens[*currentToken].content.compare("super") == 0) {
        eat(currentToken);
        return true;
    }

    return false;
}