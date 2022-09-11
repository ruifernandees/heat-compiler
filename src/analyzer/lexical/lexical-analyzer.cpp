#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

#include "./automata/main.cpp"
#include "./utils/withdraw-spaces.cpp"
#include "./utils/split-commands-by-delimiter.cpp"
#include "./utils/remove-comments.cpp"

#pragma once

using namespace std;

vector<Token> lexicalAnalyzer(vector<string> script) {
    vector<string> commands = removeComments(script);
    commands = withdraw_spaces(commands);
    commands = splitCommandsByDelimiter(commands, ' ');
    return lexicalAnalyzerAutomata(commands);
}