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

bool operation(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 OPERATION" << endl;
    
    int pastToken = *currentToken;

    // possibilidade 1, 2 e 3
    if (identifier(tokens, currentToken)) {
        //cout << "OPERATION > IDENTIFIER" << endl;
        int pstToken = *currentToken;

        // possibilidade 2
        if (verify_content(tokens, currentToken, "!")) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 3
        if (verify_content(tokens, currentToken, "?")) {
            return true;
        }

        *currentToken = pstToken;

        // possibilidade 1
        return true;
    }

    *currentToken = pastToken;

    return false;
}