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
        if (verify_content(tokens, currentToken, "=")) {
            if (mrhs(tokens, currentToken)) {
                if (exprL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (verify_content(tokens, currentToken, "return")) {
        if (call_args(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    //possibilidade 3
    if (verify_content(tokens, currentToken, "not")) {
        if (expr(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
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
    if (verify_content(tokens, currentToken, "!")) {
        if (command(tokens, currentToken)) {
            if (exprL(tokens, currentToken)) {
                return true;
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
