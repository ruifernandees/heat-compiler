#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    string line;
    ifstream myfile ("filee.txt");
    
    vector<string> linhas{};
    
    if (myfile.is_open()) {
        while( getline(myfile, line))
        {
            string palavra;
            for (int i = 0; i < line.size(); i++)
            {
                if (!isspace(line[i]))
                {
                    palavra.push_back(line[i]);
                }
            }
            linhas.push_back(palavra);
        }
        
        vector<string> palavras{};
        for (int i = 0; i < linhas.size(); i++)
        {
            stringstream ss(linhas[i]);
        
            vector<string> vec;
            char delim=';';
            string tok;
            while (getline(ss, tok, delim)) 
            {
                if (!tok.empty())
                {
                    palavras.push_back(tok);
                }
            }
        }
        
        for (const auto &w : palavras) {
            cout << w << endl;
        }
    }
    

    else cout << "nao deu \n";

    return 0;
}