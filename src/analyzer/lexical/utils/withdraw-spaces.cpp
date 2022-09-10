#include <string>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

vector<string> withdraw_spaces(vector<string> commands)
{
    vector<string> cmds;
    for (string command : commands)
    {
        regex spaces("\\s{2,}");
        string commandWithTrim = regex_replace(command, spaces, " ");
        cmds.push_back(commandWithTrim);
    }
    return cmds;
}