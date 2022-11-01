#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"
#include "../utils/verify-productions.cpp"
// include "./index.cpp"

#pragma once

using namespace std;


bool funcaoAssocsComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (assoc(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}

bool assocs1(vector<Token> tokens, int* currentToken)
{
    // possibilidade 1
    if (assoc(tokens, currentToken)) {
        // varios ou vazio
        while(funcaoAssocsComAsterisco(tokens, currentToken)) {}
        return true;
    }
    return false;
}

bool assocs(vector<Token> tokens, int* currentToken) {
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(assocs1);
    return verify_productions(tokens, currentToken, prodVector);
}
