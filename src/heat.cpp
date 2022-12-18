#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "./utils/read-file.cpp"
#include "./analyzer/lexical/lexical-analyzer.h"
#include "./analyzer/syntactic/syntactic-analyzer.h"
#include "./analyzer/semantic/semantic-analyzer.h"
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

	ofstream lexicalFile("lexical.txt");

    for (Token token : tokens) {
        if (token.content.compare("\n") == 0) {
            lexicalFile << "< " << "LB" << ", " << token.type << " >" << endl;
        } else {
            lexicalFile << "< " << token.content << ", " << token.type << " >" << endl;
        }
    }

	lexicalFile.close();
    vector<var_scope> symbol_table = syntacticAnalyzer(tokens);
    //semanticAnalyzer(tokens, symbol_table);

    return 0;
}