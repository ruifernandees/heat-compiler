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


bool term(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    // cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 TERM" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (verify_content(tokens, currentToken, ";") || verify_content(tokens, currentToken, "\n")) {
        return true;
    }

    *currentToken = pastToken;

    return false;
}