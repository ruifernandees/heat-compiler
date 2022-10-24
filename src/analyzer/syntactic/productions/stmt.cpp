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


void tentarSTMTLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("|") == 0) {
        eat(currentToken);
        if (block_var(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare("|") == 0) {
                eat(currentToken);
                
            }
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarSTMTLer2(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("do") == 0) {
        eat(currentToken);

        tentarSTMTLer1(tokens, currentToken);

        if (compstmt(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare("end") == 0) {
                eat(currentToken);
                return;
            }
        }
    }

    *currentToken = pstToken;
    return;
}

bool stmt(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    // 1 possibilidade
    if (call(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("do") == 0) {
            eat(currentToken);

            tentarSTMTLer1(tokens, currentToken);

            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("end") == 0) {
                    eat(currentToken);
                    if (stmtL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // 2 e 3 possibilidade
    if (tokens[*currentToken].content.compare("begin") == 0 ||
        tokens[*currentToken].content.compare("end") == 0) {
        eat(currentToken);
        if (tokens[*currentToken].content.compare("{") == 0) {
            eat(currentToken);
            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("}") == 0) {
                    eat(currentToken);
                    if (stmtL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // 4 possibilidade
    if (lhs(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("=") == 0) {
            eat(currentToken);
            if (command(tokens, currentToken)) {
                tentarSTMTLer2(tokens, currentToken);

                if (stmtL(tokens, currentToken)) {
                    return true;
                }
            }

        }
    }

    *currentToken = pastToken;

    // 5 possibilidade
    if (expr(tokens, currentToken)) {
        if (stmtL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    return false;
}
