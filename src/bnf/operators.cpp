#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "operators.h"
#include "types.h"

using namespace std;

vector<string> operators;

void initializeOperatorsVector() {
    // 3 positions
    operators.push_back("**=");
    operators.push_back("&&=");
    operators.push_back("||=");
    operators.push_back("==="),
    operators.push_back("...");
    operators.push_back("[]=");

    // 2 positions
    operators.push_back("**"),
    operators.push_back("==");
    operators.push_back("!=");
    operators.push_back("@@");
    operators.push_back("+@");
    operators.push_back("-@");
    operators.push_back("[]");
    operators.push_back(">=");
    operators.push_back("<=");
    operators.push_back("=>");
    operators.push_back("!~");
    operators.push_back("::");
    operators.push_back("&&");
    operators.push_back("||"),
    operators.push_back("+=");
    operators.push_back("-=");
    operators.push_back("*=");
    operators.push_back("/=");
    operators.push_back("?:");
    operators.push_back("..");
    operators.push_back("%=");

    // 1 position
    operators.push_back("@");
    operators.push_back("$");
    operators.push_back(":");
    operators.push_back(".");
    operators.push_back("?");
    operators.push_back(">");
    operators.push_back("<");
    operators.push_back("+");
    operators.push_back("-");
    operators.push_back("*");
    operators.push_back("/");
    operators.push_back("%");
    operators.push_back("&");
    operators.push_back("!");
    operators.push_back("=");
}

bool isAnOperator(string word) {
    if (operators.size() == 0) { 
        initializeOperatorsVector();
    }
    for (int i = 0; i < operators.size(); i++){
        if (word.compare(operators[i]) == 0) return true;
    }
    return false;
}

int greatestOperatorLength() {
    if (operators.size() == 0) { 
        initializeOperatorsVector();
    }
    int greatest = 0;
    for (int i = 0; i < operators.size(); i++){
        if (operators[i].length() > greatest) {
            greatest = operators[i].length();
        }
    }
    return greatest;
}
