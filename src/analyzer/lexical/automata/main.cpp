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
 * @param commands - Linhas de código
 * @return vector<Token> 
 */
vector<Token> verify_tokens(vector<string> commands)
{
    for (string command : commands)
    {
        bool isAnEmptyLine = command.length() == 0;
        if (isAnEmptyLine) continue;
        int character_stopped = 0;
        while (character_stopped != -1)
        {
            handleCurrentCommandVerification(command, &character_stopped);
        }
    }
}