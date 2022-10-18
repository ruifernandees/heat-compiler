#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool arglist(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (identifier(tokens, currentToken)) {
        // varios ou vazio
        while (funcaoComAsterisco(tokens, currentToken)) {}

        if (tokens[*currentToken].content.compare(",")) {
            eat(currentToken);
            if (tokens[*currentToken].content.compare("*")) {
                eat(currentToken);
                if (identifier(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare(",")) {
                        eat(currentToken);
                        if (tokens[*currentToken].content.compare("&")) {
                            eat(currentToken);
                            if (identifier(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(",") == 0) {
                eat(currentToken);
                if (tokens[*currentToken].content.compare("&") == 0) {
                    eat(currentToken);
                    if (identifier(tokens, currentToken)) {
                        return true;
                    }
                }
            }

        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (tokens[*currentToken].content.compare("&") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare(",")) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}