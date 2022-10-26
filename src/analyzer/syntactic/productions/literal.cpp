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

bool literal(vector<Token> tokens, int* currentToken)
{
    // if (tokens.size() <= *currentToken + 1) return false;
    // if (tokens.size() <= *currentToken) return false;
    int pastToken = *currentToken;
    cout << "[" <<tokens[*currentToken].content << ", " << tokens[*currentToken].type << "] " << *currentToken << "🧪 LITERAL" << endl;

    // possibilidade 1
    cout << "[LITERAL CALLS] COMPARE NUMBER" << endl;
    if (tokens[*currentToken].type.compare(NUMBER) == 0) {
        cout << "[LITERAL CALLS] COMPARE NUMBER ok" << endl;
        eat(tokens, currentToken);
        return true;
    }
    
    *currentToken = pastToken;

    // possibilidade 2
    if (symbol(tokens, currentToken)) {return true;}

    *currentToken = pastToken;

    return false;
}
