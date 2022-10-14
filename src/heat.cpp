#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "./utils/read-file.cpp"
#include "./analyzer/lexical/lexical-analyzer.h"
#include "./analyzer/syntactic/syntactic-analyzer.h"
#include "./analyzer/semantic/main.cpp"
#include "./bnf/types.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        cout << "Please provide a file name!" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<string> script = readFile(filename);
    vector<Token> tokens = lexicalAnalyzer(script);
    for (Token token : tokens) {
        cout << "< " << token.content << ", " << token.type << " >" << endl;
    }
    syntacticAnalyzer(tokens);
    semanticAnalyzer();
    return 0;
}