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

void tentarSTMTLer3(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (block_var(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarSTMTLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "|")) {
        tentarSTMTLer3(tokens, currentToken);
        if (verify_content(tokens, currentToken, "|")) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarSTMTLer2(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (verify_content(tokens, currentToken, "do")) {
        tentarSTMTLer1(tokens, currentToken);

        if (compstmt(tokens, currentToken)) {
            if (verify_content(tokens, currentToken, "end")) {
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool stmt1(vector<Token> tokens, int* currentToken)
{
    // 1 possibilidade
    if (call(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "do")) {
            tentarSTMTLer1(tokens, currentToken);
            if (compstmt(tokens, currentToken)) {
                if (verify_content(tokens, currentToken, "end")) {
                    if (stmtL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool stmt2(vector<Token> tokens, int* currentToken)
{
    // 2 e 3 possibilidade
    if (verify_content(tokens, currentToken, "begin") || verify_content(tokens, currentToken, "end")) {
        if (verify_content(tokens, currentToken, "{")) {
            if (compstmt(tokens, currentToken)) {
                if (verify_content(tokens, currentToken, "}")) {
                    if (stmtL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool stmt4(vector<Token> tokens, int* currentToken)
{
    // 4 possibilidade
    if (lhs(tokens, currentToken)) {
        if (verify_content(tokens, currentToken, "=")) {
            if (command(tokens, currentToken)) {
                tentarSTMTLer2(tokens, currentToken);

                if (stmtL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool stmt5(vector<Token> tokens, int* currentToken)
{
    // 5 possibilidade
    if (expr(tokens, currentToken)) {
        if (stmtL(tokens, currentToken)) {
            return true;
        }
    }
    return false;
}

bool stmt(vector<Token> tokens, int* currentToken) {

    FunctionCallbackArray callback;
    callback.push_back(stmt1);
    callback.push_back(stmt2);
    callback.push_back(stmt4);
    callback.push_back(stmt5);
    return verify_productions(tokens, currentToken, callback);
}
