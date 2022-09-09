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
        cout << i << endl;
        if (!isalnum(command[i]))
        {
            cout << i << endl;
            string word = command.substr(*pos, i);
            cout << word << endl;
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

    *pos = -1;
    // passou pela string toda
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
                string token = command.substr(*pos, i);
                cout << token << " is a number" << endl;
                *pos = i; // caractere especial continuar verificacao do comando
                return;
            }
        }
    }

    *pos = -1;
}

void s3(string command, int *pos)
{
    for (int i = *pos; i < command.length(); i++)
    {
        if (isalnum(command[i]))
        {
            string token = command.substr(*pos, i);
            if (isAnOperator(token))
            {
                cout << token << " is a operator" << endl;
            }
            else
            {
                cout << token << " unrecognized character" << endl;
            }
            *pos = i;
            return;
        }
    }

    *pos = -1;
}

void s0(string command, int *character_stopped)
{
    //cout << command << endl;
    if (isalpha(command[*character_stopped]))
    {
        //cout << "A" << command << endl;
        //cout << "stopped1 " << *character_stopped << endl;
        s1(command, character_stopped);
        //cout << "stopped2 " << *character_stopped << endl;
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
        int character_stopped = 0;
        while (character_stopped != -1)
        {
            s0(command, &character_stopped);
        }
    }
}