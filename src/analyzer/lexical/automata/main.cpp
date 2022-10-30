#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

#include "../../../bnf/keywords.h"
#include "../../../bnf/operators.h"
#include "../../../bnf/delimiters.h"
#include "../../../bnf/types.h"

#include "./current-command-handler.cpp"

/**
 * @brief 
 * 
 * @param commands 
 * @return vector<Token> 
 */
vector<Token> lexicalAnalyzerAutomata(vector<string> commands)
{
    vector<Token> allTokens;
    for (string command : commands)
    {
        bool isAnEmptyLine = command.length() == 0;
        if (isAnEmptyLine) continue;
        int character_stopped = 0;
        while (character_stopped != WAS_ENTIRE_COMMAND_VERIFIED)
        {
            Token token = handleCurrentCommandVerification(command, &character_stopped);
            if (token.content.compare("\n") == 0) {
                if (allTokens.size() > 0 && allTokens.back().content.compare(";") == 0) {
                    continue;
                }
            }
            allTokens.push_back(token);
        }
    }
    return allTokens;
}