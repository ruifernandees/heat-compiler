#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../lexical-analyzer.cpp"
#include "../utils/factories.cpp"
#include "../../../bnf/types.h"

vector<Token> expectedVectorFactory() {
    vector<Token> allTokens;
    allTokens.push_back(numberTokenObjectFactory("3"));
    allTokens.push_back(identifierTokenObjectFactory("puts"));
    allTokens.push_back(numberTokenObjectFactory("1"));
    allTokens.push_back(delimiterTokenObjectFactory(";"));
    allTokens.push_back(identifierTokenObjectFactory("hello"));
    allTokens.push_back(operatorsTokenObjectFactory("="));
    allTokens.push_back(numberTokenObjectFactory("2"));
    allTokens.push_back(operatorsTokenObjectFactory("%="));
    allTokens.push_back(keywordTokenObjectFactory("if"));
    allTokens.push_back(keywordTokenObjectFactory("if"));
    allTokens.push_back(numberTokenObjectFactory("3"));
    allTokens.push_back(operatorsTokenObjectFactory(">"));
    allTokens.push_back(numberTokenObjectFactory("2"));
    allTokens.push_back(keywordTokenObjectFactory("end"));
    allTokens.push_back(identifierTokenObjectFactory("puts_1"));
    allTokens.push_back(operatorsTokenObjectFactory("="));
    allTokens.push_back(numberTokenObjectFactory("1"));
    return allTokens;
}

bool shouldRecognizeHelloWorldCorrectly(vector<string> script) {
    try
    {
        vector<Token> expectedTokens = expectedVectorFactory();
        vector<Token> tokens = lexicalAnalyzer(script);
        for (int i = 0; i < tokens.size(); i++) {
            // cout << tokens[i].content << " vs " << expectedTokens[i].content << endl << tokens[i].type << " vs " << expectedTokens[i].type << endl;
            cout << "< " << tokens[i].content << ", " << tokens[i].type << " >" << endl;
            if (
                tokens[i].content.compare(expectedTokens[i].content) != 0
                || tokens[i].type.compare(expectedTokens[i].type) != 0
            ) {
                return false;
            }
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