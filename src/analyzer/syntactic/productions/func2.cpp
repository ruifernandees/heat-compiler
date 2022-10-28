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

bool func2(vector<Token> tokens, int* currentToken)
{
    int pastToken = *currentToken;

    if (verify_content(tokens, currentToken, "{")) {
        tentarFunc2Ler6(tokens, currentToken);
        if (compstmt(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, "}")) {
                if (primaryL(tokens, currentToken)) {
                    if (functionL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    return true;
}
