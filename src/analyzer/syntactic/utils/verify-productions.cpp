#pragma once

bool verify_productions(vector<Token> tokens, int *currentToken, vector<bool (*)(vector<Token>, int*)> productions)
{
    int pastToken = *currentToken;

    for (auto && fn : productions) {
        if (fn(tokens, currentToken)) {
            return true;
        } else {
            *currentToken = pastToken;
        }
    }
    return false;
}