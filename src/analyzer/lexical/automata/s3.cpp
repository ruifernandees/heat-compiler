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
        // string word = restoreWord(command, i+1, *pos);
        // if (isAnOperator(word)) {
        //     *pos 
        //     s4(command, )
        // }
    }
    string originalWord = word;
    cout << "Verifying delimiter in " << word << endl;
    for (int i = *pos + originalWord.length(); i > *pos; i--) {
        if (isAnOperator(word)) {
            cout << "Is an operator " << word << endl;
            if (i == command.length() - 1) {
                *pos = WAS_ENTIRE_COMMAND_VERIFIED;
            } else {
                *pos = i;
            }
            return operatorsTokenObjectFactory(word);
        }
        word.pop_back();
    }
    string currentCommand (1, command[*pos]);
    cout << "Final word " << currentCommand << ",  " << *pos << endl;
    *pos++;
    cout << "Command " << command << endl;
    if (*pos == command.length()  -1 ) *pos = WAS_ENTIRE_COMMAND_VERIFIED;
    cout << "POS " << *pos << endl;
    return delimiterTokenObjectFactory(currentCommand);
}