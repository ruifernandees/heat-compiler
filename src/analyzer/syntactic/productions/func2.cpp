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

void tentarFunc2Ler7(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (block_var(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarFunc2Ler6(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "|")) {
        tentarFunc2Ler7(tokens, currentToken);
        if (verify_content(tokens, currentToken, "|")) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

bool func21(vector<Token> tokens, int* currentToken)
{
    if (verify_content(tokens, currentToken, "{")) {
        tentarFunc2Ler6(tokens, currentToken);
        if (compstmt(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, "}")) {
                if (primaryL(tokens, currentToken)) {
                    if (func2(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool func2(vector<Token> tokens, int* currentToken)
{
    vector<bool (*)(vector<Token>, int*)> prodVector;
    prodVector.push_back(func21);

    if (verify_productions(tokens, currentToken, prodVector)) {
        return true;
    }

    // vazio
    return true;
}
