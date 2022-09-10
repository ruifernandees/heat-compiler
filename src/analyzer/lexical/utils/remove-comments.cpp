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
    bool hasBeginCommentStatement = false;
    for (string line : text)
    {
        string newLine;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '=') {
                cout << "IGUAL CHAR" << endl;
                string beginString = "";
                string endString = "";
                for (int k = i; k < MULTIPLE_LINE_COMMENT_BEGIN.size(); k++) {
                    if (k >= line.length()) break;
                    beginString.push_back(line[k]);
                }
                for (int l = i; l < MULTIPLE_LINE_COMMENT_END.size(); l++) {
                    if (l >= line.length()) break;
                    endString.push_back(line[l]);
                }
                if (beginString.compare(MULTIPLE_LINE_COMMENT_BEGIN) == 0) {
                    cout << "BEGIN STRING" << endl;
                    hasBeginCommentStatement = true;
                    // i += MULTIPLE_LINE_COMMENT_BEGIN.size() - 1;
                }
                if (endString.compare(MULTIPLE_LINE_COMMENT_END) == 0) {
                    cout << "END STRING" << endl;
                    hasBeginCommentStatement = false;
                    // i += MULTIPLE_LINE_COMMENT_END.size() - 1;
                }
            }
            if (hasBeginCommentStatement) break;
            if (line[i] == ONE_LINE_COMMENT) break;
            newLine.push_back(line[i]);
        }
        cout << newLine << endl;
        cmds.push_back(newLine);
    }
    if (hasBeginCommentStatement) {
        throw runtime_error("Error: unclosed begin comment statement");
    }
    return cmds;
}