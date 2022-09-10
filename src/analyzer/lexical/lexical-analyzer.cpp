#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "lexical-analyzer.h"

#include "./split-commands-by-delimiter.cpp"
#include "./automata.cpp"

using namespace std;

vector<string> withdraw_spaces(vector<string> commands)
{
    vector<string> cmds;
    for (string command : commands)
    {
        regex spaces("\\s{2,}");
        string commandWithTrim = regex_replace(command, spaces, " ");
        cout << commandWithTrim << endl;
        cmds.push_back(commandWithTrim);
    }
    return cmds;
}

void lexicalAnalyzer(vector<string> script) {
    vector<string> commands = splitCommandsByDelimiter(script, ';');
    cout << "👽" << endl;
    commands = withdraw_spaces(commands); // deixar apenas um espaco (trim)
    cout << "🙈" << endl;
    commands = splitCommandsByDelimiter(commands, ' ');
    vector<Token> tokens = verify_tokens(commands);
}