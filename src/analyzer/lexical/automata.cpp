#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

using namespace std;

#include "../../bnf/keywords.h"
#include "../../bnf/operators.h"
#include "../../bnf/delimiters.h"
#include "../../bnf/types.h"

#include "factories.cpp"

void s1(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isalnum(command[i]))
        {
            string word;
            for (int y = *pos; y < i; y++)
            {
                word.push_back(command[y]);
            }

            if (isAKeyword(word))
            {
                cout << word << " is a keyword" << endl;
            }
            else
            {
                cout << word << " is a identifier" << endl;
            }
            *pos = i;
            return;
        }
    }

    string word;
    for (int y = *pos; y < command.length(); y++)
    {
        word.push_back(command[y]);
    }
    if (isAKeyword(word))
    {
        cout << word << " is a keyword" << endl;
    }
    else
    {
        cout << word << " is a identifier" << endl;
    }
    // passou pela string toda
    *pos = -1;
}

void s2(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (!isdigit(command[i]))
        {
            if (isalpha(command[i]))
            {
                cout << "error (number + character)" << endl;
                *pos = -1; // parar de reconhecer a linha
                return;
            }
            else
            {
                string token;
                for (int y = *pos; y < i; y++)
                {
                    token.push_back(command[y]);
                }
                cout << token << " is a number" << endl;
                *pos = i; // caractere especial continuar verificacao do comando
                return;
            }
        }
    }

    string token;
    for (int y = *pos; y < command.length(); y++)
    {
        token.push_back(command[y]);
    }
    cout << token << " is a number" << endl;
    *pos = -1;
}

void s3(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (isalnum(command[i]) != 0)
        {
            string token;
            for (int y = *pos; y < i; y++)
            {
                token.push_back(command[y]);
            }
            if (isAnOperator(token))
            {
                cout << token << " is a operator" << endl;
            }
            else if (isADelimiter(token))
            {
                cout << token << " is a delimiter" << endl;
            }
            else
            {
                cout << token << " unrecognized character" << endl;
            }
            *pos = i;
            return;
        }
    }

    string token;
    for (int y = *pos; y < command.length(); y++)
    {
        token.push_back(command[y]);
    }
    if (isAnOperator(token))
    {
        cout << token << " is a operator" << endl;
    }
    else if (isADelimiter(token))
    {
        cout << token << " is a delimiter" << endl;
    }
    else
    {
        cout << token << " unrecognized character" << endl;
    }
    *pos = -1;
}

void s0(string command, int *character_stopped)
{
    if (isalpha(command[*character_stopped]))
    {
        s1(command, character_stopped);
    }
    else if (isdigit(command[*character_stopped]))
    {
        s2(command, character_stopped);
    }
    else
    {
        s3(command, character_stopped);
    }
}

vector<Token> verify_tokens(vector<string> commands) //commands: linhas do código
{
    for (string command : commands)
    {
        if (command.length() != 0) // isso por causa das linhas vazias
        {
            int character_stopped = 0;
            while (character_stopped != -1)
            {
                s0(command, &character_stopped);
            }
        }
    }
}