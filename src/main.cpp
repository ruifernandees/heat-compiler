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
    operators.push_back("**="),
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
    operators.push_back("[]="),
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

vector<Token> verify_tokens(vector<string> commands) //commands: linhas do código
{
    cout << "Verify token" << endl;
    vector<Token> tokens;
    for (string command: commands) {
        string word;
        for (int letter = 0; letter < command.length(); letter++) {
            string currentLetter (1, command[letter]);
            if (isAOperator(currentLetter)) {
                cout << currentLetter << " is a operator" << endl;
                // word = "";
            }
            word += command[letter];
            // if (regex_match(word, keywords)) {
            //     Token keyword;
            //     keyword.content = word;
            //     keyword.type = "KEYWORD";
            //     tokens.push_back(keyword)
            //     cout << word << " is a keyword" << endl;
            // }
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
    vector<Token> tokens = verify_tokens(commands);
    return 0;
}