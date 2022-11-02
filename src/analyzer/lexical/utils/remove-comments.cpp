#include <string>
#include <vector>
#include <cstring>
#include <regex>
#include <iostream>

#include "../../../bnf/types.h"

#pragma once

using namespace std;

/**
 * @brief 
 * 
 * @param text 
 * @return vector<string> 
 */
vector<string> removeComments(vector<string> text)
{
    cout <<"TEXT\n";
    for (auto t: text) {
        cout << t;
    }
    vector<string> cmds;
    bool hasBeginCommentStatement = false;
    for (string line : text)
    {
        regex onlySpaces("^\\s+$");
        string newLine = "";

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '=') {
                string beginString = "";
                string endString = "";
                for (int k = i; k < i + MULTIPLE_LINE_COMMENT_BEGIN.size(); k++) {
                    if (k >= line.length()) break;
                    beginString.push_back(line[k]);
                }
                for (int l = i; l < i + MULTIPLE_LINE_COMMENT_END.size(); l++) {
                    if (l >= line.length()) break;
                    endString.push_back(line[l]);
                }
                if (beginString.compare(MULTIPLE_LINE_COMMENT_BEGIN) == 0) {
                    hasBeginCommentStatement = true;
                    i += MULTIPLE_LINE_COMMENT_BEGIN.size();
                }
                if (endString.compare(MULTIPLE_LINE_COMMENT_END) == 0) {
                    bool itsOnlyEnd = i + MULTIPLE_LINE_COMMENT_END.length() == line.length();
                    if (itsOnlyEnd)
                    {
                        hasBeginCommentStatement = false;
                        i += MULTIPLE_LINE_COMMENT_END.size();
                        break;
                    }
                }
            }
            if (hasBeginCommentStatement) break;
            if (line[i] == ONE_LINE_COMMENT) break;
            newLine.push_back(line[i]);
        }
        if (line.compare("\n") == 0 && cmds.back().compare("\n") != 0) {
            cmds.push_back(line);
            continue;
        }
        if (newLine.length() == 0) continue;
        if (regex_match(newLine, onlySpaces)) continue;
        cmds.push_back(newLine);
    }
    if (hasBeginCommentStatement) {
        throw runtime_error("Error: unclosed begin comment statement");
    }
    return cmds;
}