#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

#include "../../bnf/keywords.h"
#include "../../bnf/operators.h"
#include "../../bnf/delimiters.h"
#include "../../bnf/types.h"

#include "factories.cpp"

using namespace std;

vector<Token> tokens;

void verifyCommand(string command) {
    string word = "";
    int currentLetterIndex = 0;
    while (currentLetterIndex < command.length()) {
        bool currentLetterIsAnOperator = false;
        bool currentLetterIsADelimiter = false;
        while (!isspace(command[currentLetterIndex]))  {
            if (isAnOperator(command[currentLetterIndex] + "")) {
                cout << "OPERATOR " << command[currentLetterIndex] << endl << endl;
                currentLetterIsAnOperator = true;
                currentLetterIndex++;
                break;
            }
            if (isADelimiter(command[currentLetterIndex] + "")) {
                currentLetterIsADelimiter = true;
                currentLetterIndex++;
                break;
            }
            if (currentLetterIndex >= command.length()) break;
            word += command[currentLetterIndex];
            currentLetterIndex++;
        }
        tokens.push_back(identifierOrKeywordOrDigitObjectFactory(word));
        if (isspace(command[currentLetterIndex])) {
            currentLetterIndex++;
        }
        if (currentLetterIsAnOperator) {
            string currentOperator = command[currentLetterIndex] + "";
            while (isAnOperator(currentOperator)) {
                currentOperator += command[currentLetterIndex];
                currentLetterIndex++;
            }
            tokens.push_back(operatorsTokenObjectFactory(currentOperator + ""));
        } else if (currentLetterIsADelimiter) {
            tokens.push_back(delimiterTokenObjectFactory(command[currentLetterIndex] + ""));
            currentLetterIndex++;
        } 
        word = "";
    }
}

vector<Token> verify_tokens(vector<string> commands) //commands: linhas do código
{
    for (string command: commands) {
        cout << command << endl;
        verifyCommand(command);
    }
    for (int i = 0; i < tokens.size(); i++) {
        cout << "<" << tokens[i].content << ", " << tokens[i].type << ">" << endl;
    }
    cout << endl;
}