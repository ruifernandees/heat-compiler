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
        string word = "";
        for (int i = 0; i < command.length(); i++)
        {
            if (!isspace(command[i]))
            {
                word.push_back(command[i]);
            }
        }
        cmds.push_back(word);
    }
    return cmds;
}

void lexicalAnalyzer(vector<string> script) {
    vector<string> commands = splitCommandsByDelimiter(script);
    // antes disso tirar todos os espacos a nao ser por aqueles que vem depois de palavras reservadas
    // commands = withdraw_spaces(commands);
    // for (auto command : commands) {
        
    // }
    vector<Token> tokens = verify_tokens(commands);
}