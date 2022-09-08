#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#define FILE_READING_ERROR "FILE_READING_ERROR"

using namespace std;


typedef struct aux {
    string content;
    string type;    
} Token;

regex keywords ("do|end|undef|alias|if|then|else|elsif|case|while|for|in|begin|rescue|ensure|class|def|unless|until|return|yield|and|or|not|super|defined?|nil|self");

// regex operators ("\\+|\\-|\\*|\\/|\\%|\\*\\|\\=\\=|\\!\\=|\\>|\\<|\\>\\=|\\<\\=|\\<\\=\\>|\\=\\=\\|\\&\\&|\\!|\\||\\|\\|\\=|\\+\\=|\\-\\=|\\*\\=|\\/\\=|\\%\\=|\\*\\*\\|\\&\\&\\=|\\|\\|\\=|\\^|\\&|\\~|\\<\\<|\\>\\|\\?\\:|\\^\\=|\\.\\.|\\.\\.\\.|\\<\\<\\=|\\>\\>\\=|\\=\\>|\\=\\~|\\!\\~|\\:\\:|\\+\\@|\\-\\@|\\[\\]|\\[\\]\\|\\(|\\)|\\[|\\]|\\{|\\}|\\.|\\,|\\?");



bool isAOperator(string word) {
    vector<string> operators;
    operators.push_back("+");
    operators.push_back("-");
    operators.push_back("*");
    operators.push_back("/");
    operators.push_back("%");
    operators.push_back("**"),
    operators.push_back("==");
    operators.push_back("!=");
    operators.push_back(">");
    operators.push_back("<");
    operators.push_back(">=");
    operators.push_back("<=");
    operators.push_back("<=>");
    operators.push_back("==="),
    operators.push_back("&&");
    operators.push_back("!");
    operators.push_back("|");
    operators.push_back("||"),
    operators.push_back("=");
    operators.push_back("+=");
    operators.push_back("-=");
    operators.push_back("*=");
    operators.push_back("/=");
    operators.push_back("%=");
    operators.push_back("**=");
    operators.push_back("&&=");
    operators.push_back("||=");
    operators.push_back("^");
    operators.push_back("&");
    operators.push_back("~");
    operators.push_back("<<");
    operators.push_back(">>"),
    operators.push_back("?:");
    operators.push_back("^=");
    operators.push_back("..");
    operators.push_back("...");
    operators.push_back("<<=");
    operators.push_back(">>=");
    operators.push_back("=>");
    operators.push_back("=~");
    operators.push_back("!~");
    operators.push_back("::");
    operators.push_back("+@");
    operators.push_back("-@");
    operators.push_back("[]");
    operators.push_back("[]=");
    operators.push_back("(");
    operators.push_back(")");
    operators.push_back("[");
    operators.push_back("]");
    operators.push_back("{");
    operators.push_back("}");
    operators.push_back(".");
    operators.push_back(",");
    operators.push_back("?");
    for (int i = 0; i < operators.size(); i++){
        if (word.compare(operators[i]) == 0) return true;
    }
    return false;
}

vector<string> withdraw_spaces(vector<string> commands)
{
    vector<string> cmds;
    for (string command : commands)
    {
        string word = "";
        for (int i = 0; i < command.length(); i++)
        {
            if (!isspace(command[i]))
            {
                word.push_back(command[i]);
            }
        }
        cmds.push_back(word);
    }
    return cmds;
}

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

vector<string> readFile(string filename) {
    string line;
    vector<string> lines;
    ifstream fileToRead(filename);
    if (fileToRead.is_open()) {
        while (getline(fileToRead, line)) {
            lines.push_back(line);
        }
        fileToRead.close();
        return lines;
    }
    throw runtime_error("Could not read file");
}

vector<string> recognize(vector<string> script) {
        vector<string> words;
        for (int i = 0; i < script.size(); i++)
        {
            stringstream ss(script[i]);
            char delim=';';
            string tok;
            while (getline(ss, tok, delim)) 
            {
                if (!tok.empty())
                {
                    words.push_back(tok);
                }
            }
        }
        
        // for (const auto &w : words) {
        //     cout << w << endl;
        // }
        return words;
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        cout << "Please provide a file name!" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<string> script = readFile(filename);
    vector<string> commands = recognize(script);
    // antes disso tirar todos os espacos a nao ser por aqueles que vem depois de palavras reservadas
    commands = withdraw_spaces(commands);
    vector<Token> tokens = verify_tokens(commands);
    return 0;
}