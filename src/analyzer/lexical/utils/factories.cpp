#include <string>
#include <cstring>

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"
#include "../../../utils/string-is-a-number.cpp"

using namespace std;

Token keywordTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.content = KEYWORD;
    return newToken;
}

Token identifierTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.content = IDENTIFIER;
    return newToken;
}

Token delimiterTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.content = DELIMITER;
    return newToken;
}

Token operatorsTokenObjectFactory(string word) {
    Token newToken;
    newToken.content = word;
    newToken.content = OPERATOR;
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
        newToken.type = DIGIT;
        return newToken;
    }
    if (isdigit(word[0])) {
        throw runtime_error("Unexpected identifier: " + word);
    }
    newToken.type = IDENTIFIER;
    return newToken;
}