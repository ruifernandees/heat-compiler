#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "operators.h"

using namespace std;

vector<string> operators;

void initializeOperatorsVector() {
    operators.push_back("+");
    operators.push_back("-");
    operators.push_back("*");
    operators.push_back("/");
    operators.push_back("%");
    operators.push_back("**"),
    operators.push_back("==");
    operators.push_back("!=");
    operators.push_back(">");
    operators.push_back("<");
    operators.push_back(">=");
    operators.push_back("<=");
    operators.push_back("<=>");
    operators.push_back("==="),
    operators.push_back("&&");
    operators.push_back("!");
    operators.push_back("|");
    operators.push_back("||"),
    operators.push_back("=");
    operators.push_back("+=");
    operators.push_back("-=");
    operators.push_back("*=");
    operators.push_back("/=");
    operators.push_back("%=");
    operators.push_back("**=");
    operators.push_back("&&=");
    operators.push_back("||=");
    operators.push_back("^");
    operators.push_back("&");
    operators.push_back("~");
    operators.push_back("<<");
    operators.push_back(">>"),
    operators.push_back("?:");
    operators.push_back("^=");
    operators.push_back("..");
    operators.push_back("...");
    operators.push_back("<<=");
    operators.push_back(">>=");
    operators.push_back("=>");
    operators.push_back("=~");
    operators.push_back("!~");
    operators.push_back("::");
    operators.push_back("+@");
    operators.push_back("-@");
    operators.push_back("[]");
    operators.push_back("[]=");
    operators.push_back("(");
    operators.push_back(")");
    operators.push_back("[");
    operators.push_back("]");
    operators.push_back("{");
    operators.push_back("}");
    operators.push_back(".");
    operators.push_back(",");
    operators.push_back("?");
}

bool isAnOperator(string word) {
    initializeOperatorsVector();
    for (int i = 0; i < operators.size(); i++){
        if (word.compare(operators[i]) == 0) return true;
    }
    return false;
}
