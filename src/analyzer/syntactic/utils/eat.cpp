#pragma once

bool eat(vector<Token> tokens, int *currentToken)
{
    if (*currentToken + 1 >= tokens.size()) {
        //throw new runtime_error("EVERYTHING OK");
        return false;
    }
    *currentToken = *currentToken + 1;
    return true;
}