#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

#include "./automata/main.cpp"
#include "./utils/withdraw-spaces.cpp"
#include "./utils/split-commands-by-delimiter.cpp"

using namespace std;

void lexicalAnalyzer(vector<string> script) {
    vector<string> commands = splitCommandsByDelimiter(script, ';');
    cout << "👽" << endl;
    commands = withdraw_spaces(commands); // deixar apenas um espaco (trim)
    cout << "🙈" << endl;
    commands = splitCommandsByDelimiter(commands, ' ');
    vector<Token> tokens = verify_tokens(commands);
}