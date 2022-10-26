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

vector<string> op_asgnOperators;

void initializeop_asgnOperatorsVector() {
    op_asgnOperators.push_back("+=");
    op_asgnOperators.push_back("-=");
    op_asgnOperators.push_back("*=");
    op_asgnOperators.push_back("/=");
    op_asgnOperators.push_back("%=");
}

bool isAnop_asgnOperator(string operato) {
    if (op_asgnOperators.size() == 0) { 
        initializeop_asgnOperatorsVector();
    }
    for (int i = 0; i < op_asgnOperators.size(); i++){
        if (operato.compare(op_asgnOperators[i]) == 0) return true;
    }
    return false;
}

bool op_asgn(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;
    if (isAnop_asgnOperator(tokens[*currentToken].content)){
        eat(tokens, currentToken);
        return true;
    }

    *currentToken = pastToken;

    return false;
}
