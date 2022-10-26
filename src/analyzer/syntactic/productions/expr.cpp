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


bool expr(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 EXPR" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (mlhs(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("=") == 0) {
            if (eat(tokens, currentToken)) {
                if (mrhs(tokens, currentToken)) {
                    if (exprL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("return") == 0) {
        if (eat(tokens, currentToken)) {
            if (call_args(tokens, currentToken)) {
                if (exprL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    //possibilidade 3
    if (tokens[*currentToken].content.compare("not") == 0) {
        if (eat(tokens, currentToken)) {
            if (expr(tokens, currentToken)) {
                if (exprL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }
    
    *currentToken = pastToken;

    //possibilidade 4
    if (command(tokens, currentToken)) {
        if (exprL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 5
    
    if (tokens[*currentToken].content.compare("!") == 0) {
        if (eat(tokens, currentToken)) {
            if (command(tokens, currentToken)) {
                if (exprL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    //possibilidade 6
    if (arg(tokens, currentToken)) {
        if (exprL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}
