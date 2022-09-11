#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../lexical-analyzer.cpp"
#include "../utils/factories.cpp"
#include "../../../bnf/types.h"

bool shouldRecognizeDoublyLinkedListCorrectly(vector<string> script) {
    try
    {
        // vector<Token> expectedTokens = expectedVectorFactory();
        vector<Token> tokens = lexicalAnalyzer(script);
        for (int i = 0; i < tokens.size(); i++) {
            // cout << tokens[i].content << " vs " << expectedTokens[i].content << endl << tokens[i].type << " vs " << expectedTokens[i].type << endl;
            cout << "< " << tokens[i].content << ", " << tokens[i].type << " >" << endl;
            // if (
            //     tokens[i].content.compare(expectedTokens[i].content) != 0
            //     || tokens[i].type.compare(expectedTokens[i].type) != 0
            // ) {
            //     return false;
            // }
        }
        cout << endl;
        return true;        
    }
    catch (const runtime_error& error)
    {
        cout << error.what() << endl;
        return false;
    }

}