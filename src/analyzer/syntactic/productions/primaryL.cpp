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


void tentarPrimaryLLer1(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return ;
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

bool primaryL(vector<Token> tokens, int* currentToken) {
    // // if (tokens.size() <= *currentToken + 1) return true;
    // // if (tokens.size() <= *currentToken) return true;
    //cout << tokens[*currentToken].content << ", " << *currentToken << "🧪 PRIMARYL" << endl;
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].content.compare("::") == 0) {
        if (eat(tokens, currentToken)) {
            if (identifier(tokens, currentToken)) {
                if (primaryL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 2
    if (tokens[*currentToken].content.compare("[") == 0) {
        if (eat(tokens, currentToken)) {
            tentarPrimaryLLer1(tokens, currentToken);

            if (tokens[*currentToken].content.compare("]") == 0) {
                if (eat(tokens, currentToken)) {
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // 3 possibidade (vazio)

    return true;
}
