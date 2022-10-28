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


bool assoc(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 assoc" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (arg(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "=>")) {
            if (arg(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}