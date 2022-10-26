#pragma once

bool eat(vector<Token> tokens, int *currentToken)
{
    if (tokens.size() <= *currentToken + 1) {
        // throw new runtime_error("EVERYTHING OK");
        return false;
    }
    *currentToken = *currentToken + 1;
    return true;
}