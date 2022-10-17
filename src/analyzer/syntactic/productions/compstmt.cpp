#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;

bool compstmt(vector<Token> tokens, int* currentToken) {
    if (stmt(tokens, currentToken)) {
        // existe ou nao
        term(tokens, currentToken);
        expr(tokens, currentToken);
        
        term(tokens, currentToken);
    }

}

