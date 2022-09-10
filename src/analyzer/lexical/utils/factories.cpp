#include <string>
#include <cstring>

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"
#include "../../../utils/string-is-a-number.cpp"

#pragma once

using namespace std;

Token keywordTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.type = KEYWORD;
    return newToken;
}

Token numberTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.type = NUMBER;
    return newToken;
}

Token identifierTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.type = IDENTIFIER;
    return newToken;
}

Token delimiterTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.type = DELIMITER;
    return newToken;
}

Token operatorsTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.type = OPERATOR;
    return newToken;
}

Token identifierOrKeywordOrDigitObjectFactory(string word)
{
    Token newToken;
    newToken.content = word;
    if (isAKeyword(word)) {
        newToken.type = KEYWORD;
        return newToken;
    }
    if (isValidNumber(word)) {
        newToken.type = NUMBER;
        return newToken;
    }
    if (isdigit(word[0])) {
        throw runtime_error("Unexpected identifier: " + word);
    }
    newToken.type = IDENTIFIER;
    return newToken;
}