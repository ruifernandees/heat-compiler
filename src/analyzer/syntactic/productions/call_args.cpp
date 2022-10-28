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

void tentarCallArgsLer1(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (assocs(tokens, currentToken)){
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarCallArgsLer2(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (verify_content(tokens, currentToken, "*")) {
            if (arg(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarCallArgsLer3(vector<Token> tokens, int *currentToken)
{
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, ",")) {
        if (verify_content(tokens, currentToken, "&")) {
            if (arg(tokens, currentToken)) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool call_args(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 call_args" << endl;
    int pastToken = *currentToken;

    // possibilidade 1 e 2
    if (args(tokens, currentToken)) {
        tentarCallArgsLer1(tokens, currentToken);
        tentarCallArgsLer2(tokens, currentToken);
        tentarCallArgsLer3(tokens, currentToken);

        // possibilidade 1 (se der tudo errado as tentativas)

        return true;
    }

    *currentToken = pastToken;

    // possibilidade 3
    if (assocs(tokens, currentToken)) {
        tentarCallArgsLer2(tokens, currentToken);
        tentarCallArgsLer3(tokens, currentToken);

        return true;
    }

    *currentToken = pastToken;

    // possibilidade 4
    if (verify_content(tokens, currentToken, "*")) {
        if (arg(tokens, currentToken)) {
            tentarCallArgsLer3(tokens, currentToken);
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 5
    if (verify_content(tokens, currentToken, "&")) {
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
