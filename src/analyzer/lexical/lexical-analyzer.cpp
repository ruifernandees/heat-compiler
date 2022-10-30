#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

#include "./automata/main.cpp"
#include "./utils/withdraw-spaces.cpp"
#include "./utils/split-commands-by-delimiter.cpp"
#include "./utils/remove-comments.cpp"
#include "./utils/eat-lines.cpp"

using namespace std;

vector<Token> lexicalAnalyzer(vector<string> script) {
    vector<string> commands = eat_first_blanks(script);
    commands = removeComments(commands);
    commands = withdraw_spaces(commands);
    commands = splitCommandsByDelimiter(commands, ' ');
    return lexicalAnalyzerAutomata(commands);
}