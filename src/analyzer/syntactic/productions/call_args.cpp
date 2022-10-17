#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;


bool call_args(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // possibilidade 1
    if (args(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    // possibilidade 2
    if (args(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);
            if (assocs(tokens, currentToken)){
                if (tokens[*currentToken].content.compare(",") == 0) {
                    eat(currentToken);
                    if (tokens[*currentToken].content.compare("*") == 0) {
                        eat(currentToken);
                        if (arg(tokens, currentToken)) {
                            if (tokens[*currentToken].content.compare(",") == 0) {
                                eat(currentToken);
                                if (tokens[*currentToken].content.compare("&") == 0) {
                                    eat(currentToken);
                                    if (arg(tokens, currentToken)) {
                                        return true;
                                    }
                                }       
                            }
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (assocs(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare(",") == 0) {
            eat(currentToken);
            if (tokens[*currentToken].content.compare("*") == 0) {
                eat(currentToken);
                if (arg(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare(",") == 0) {
                        eat(currentToken);
                        if (tokens[*currentToken].content.compare("&") == 0) {
                            eat(currentToken);
                            if (arg(tokens, currentToken)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 4
    if (tokens[*currentToken].content.compare("*") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(",") == 0) {
                eat(currentToken);
                if (tokens[*currentToken].content.compare("&") == 0) {
                    eat(currentToken);
                    if (arg(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 5
    if (tokens[*currentToken].content.compare("&") == 0) {
        eat(currentToken);
        if (arg(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;
        
    // possibilidade 6
    if (command(tokens, currentToken)) {
        return true;
    }

    *currentToken = pastToken;

    return false;
}