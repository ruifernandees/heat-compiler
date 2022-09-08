#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../../bnf/keywords.cpp"
#include "./types.cpp"

using namespace std;

vector<Token> verify_tokens(vector<string> commands) //commands: linhas do código
{
    //cout << "Verify token" << endl;
    vector<Token> tokens;
    for (string command: commands) {
        string word = "";
        string type = "";
        for (int letter = 0; letter < command.length(); letter++) {
            string currentLetter (1, command[letter]);
            // recognize number
            if (isdigit(command[letter]))
            {
                if (type.compare("keyword") == 0)
                {
                    cout << "error keyword + digit" << endl;
                    type = "";
                    word = "";
                }

                if (type.compare("word") == 0 && letter == command.length() - 1)
                {
                    word += command[letter];
                    cout << word << " is a identifier" << endl;
                    type = "";
                    word = "";
                    break;
                }
                
                //cout << "numero: " << command[letter] << endl;

                if (type.compare("operator") == 0)
                {
                    cout << word << " is a operator" << endl;
                    type = "";
                    word = "";
                }

                if (type.compare("") == 0)
                {
                    type = "num";
                }

                if (type.compare("num") == 0 && letter == command.length() - 1) // ultima chamada, isso pq no fim do for eu tenho word +=, entao nao contemplaria o ultimo
                {
                    word += command[letter];
                    cout << word << " is a num" << endl;
                    type = "";
                    word = "";
                    break;
                }
            }
            else if (isalpha(command[letter]))
            {
                // AJEITAR AS KEYWORDS, pensar tipo no if, to no 'f' agr ...
                // eh um identificador se achar na lista e se nao tiver uma letra ou digito no proximo

                if (type.compare("num") == 0)
                {
                    cout << "error digit + character" << endl;
                    type = "";
                    word = "";
                }
                else if (type.compare("operator") == 0)
                {
                    cout << word << " is a operator" << endl;
                    type = "";
                    word = "";
                }
                else if (type.compare("keyword") == 0)
                {
                    cout << "error keyword + character" << endl;
                    type = "";
                    word = "";
                }

                bool keyword = regex_match(word + currentLetter, keywords);
                if (keyword) {
                    type = "keyword";
                }
                if (letter == command.length() - 1 && keyword)
                {
                    word += currentLetter;
                    Token keyword;
                    keyword.content = word;
                    keyword.type = "KEYWORD";
                    tokens.push_back(keyword);
                    cout << word << " is a keyword" << endl;
                    type = "";
                    word = "";
                    break;
                }

                if (type.compare("") == 0)
                {
                    type = "word";
                }
                if (type.compare("word") == 0 && letter == command.length() - 1) // ultima chamada
                {
                    word += command[letter];
                    cout << word << " is a identifier" << endl;
                    type = "";
                    word = "";
                    break;
                }
                //type = "word";
                //word = "";
            }
            else // ( ), operadores ...
            {
                if (type.compare("word") == 0)
                {
                    cout << word << " is a identifier" << endl;
                    word = "";
                    type = "";
                }

                else if (type.compare("keyword") == 0 && currentLetter.compare("(") == 0)
                {
                    cout << word << " is a keyword" << endl;
                    word = "";
                    type = "";
                }

                else if (type.compare("num") == 0)
                {
                    cout << word << " is a num" << endl;
                    word = "";
                    type = "";
                }

                if (type.compare("") == 0)
                {
                    type = "operator";
                }
                if (type.compare("operator") == 0 && letter == command.length() - 1)
                {
                    // se for realmente um operador
                    word += command[letter];
                    cout << word << " is a operator" << endl;
                    type = "";
                    word = "";
                    break;
                }
            }
            word += command[letter];
        }
    }
    return tokens;
}