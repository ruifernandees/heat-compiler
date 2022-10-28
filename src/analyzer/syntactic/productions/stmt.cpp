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

bool stmt(vector<Token> tokens, int* currentToken) {
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 STMT" << endl;
    int pastToken = *currentToken;

    // 1 possibilidade
    
        // cout << "[STMT CALLS] CALL" << endl;
    if (call(tokens, currentToken)) {
        // cout << "[STMT CALLS] CALL OK" << endl;
        if (verify_content(tokens, currentToken, "do")) {
            // cout << "[STMT CALLS] TENTA STMT LER 1" << endl;
            tentarSTMTLer1(tokens, currentToken);
            // cout << "[STMT CALLS] TENTA STMT LER 1 OK" << endl;
    
            // cout << "[STMT CALLS] COMPSTMT" << endl;
            if (compstmt(tokens, currentToken)) {
                // cout << "[STMT CALLS] COMPSTMT OK" << endl;
                if (verify_content(tokens, currentToken, "end")) {
                    if (stmtL(tokens, currentToken)) {
                        // cout << "[STMT CALLS] STMTL OK" << endl;
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // 2 e 3 possibilidade
    // cout << "[STMT CALLS] COMPARE BEGIN SECOND IF" << endl;
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

    *currentToken = pastToken;

    // 4 possibilidade
    // cout << "[STMT CALLS] LHS" << endl;
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
