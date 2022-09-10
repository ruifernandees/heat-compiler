#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../../../bnf/types.h"

#pragma once

using namespace std;

vector<string> removeComments(vector<string> text)
{
    vector<string> cmds;
    for (string line : text)
    {
        string newLine;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ONE_LINE_COMMENT) break;
            newLine.push_back(line[i]);
        }
        cmds.push_back(newLine);
    }
    return cmds;
}