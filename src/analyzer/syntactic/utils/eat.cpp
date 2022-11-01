#pragma once

bool eat(vector<Token> tokens, int *currentToken)
{
    if (*currentToken + 1 >= tokens.size()) {
        return false;
    }
    *currentToken = *currentToken + 1;
    return true;
}

bool verify_content(vector<Token> tokens, int *currentToken, string content)
{
    if (tokens[*currentToken].content.compare(content) == 0) {
        return eat(tokens, currentToken);
    }
    return false;
}
