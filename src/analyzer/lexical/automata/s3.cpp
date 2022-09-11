#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"

#include "../utils/restore-word.cpp"
#include "../utils/factories.cpp"

#include "../types.h"

// +=

// []=

Token s3(string command, int *pos) {
    string word;
    for (int i = *pos; i < *pos + greatestOperatorLength(); i++) {
        if (i >= command.length()) break;
        word.push_back(command[i]);
    }
    if (word.length() == 1) {
        *pos = WAS_ENTIRE_COMMAND_VERIFIED;
        // cout << "🙈" << word << endl;
        // cout << "🍷" << endl;
        return delimiterTokenObjectFactory(word);
    }
    if (isalnum(word[1])) {
        *pos += 1;
        string delimiterInWord (1, word[0]);
        // cout << "🙈" << delimiterInWord << " <=> " << word << endl;
        // cout << "🍷" << endl;
        return delimiterTokenObjectFactory(delimiterInWord);
    }
    string originalWord = word;
    for (int i = *pos + originalWord.length() - 1; i > *pos; i--) {
        if (isAnOperator(word))  {
            *pos += word.length();
            return operatorsTokenObjectFactory(word);
        }
        // // cout << "POP " << wor
        word.pop_back();
    }
    *pos += 1;
    // cout << "FINAL WORD" << word << endl;
    return delimiterTokenObjectFactory(word);
}