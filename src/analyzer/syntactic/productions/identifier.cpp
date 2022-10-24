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

bool identifier(vector<Token> tokens, int* currentToken)
{
    return tokens[*currentToken].type.compare(IDENTIFIER) == 0;
}
