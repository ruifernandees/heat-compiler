#include <string>
#include <cstring>

#define KEYWORD "KEYWORD"
#define IDENTIFIER "IDENTIFIER"
#define OPERATOR "OPERATOR"
#define DELIMITER "DELIMITER"
#define NUMBER "NUMBER"

#define ONE_LINE_COMMENT '#'
#define NULL_ID_RECURSIVE -1

#pragma once

using namespace std;

typedef struct scope {
    string name;
    string type;
} Scope;


typedef struct var_scope {
    string name;
    vector<string> value;
    Scope scope;
    int idRecursive = NULL_ID_RECURSIVE;
} var_scope;

typedef struct function_scope {
    int linha;
    string name;
    int qnt_argumentos;
    Scope scope;
    int idRecursive = NULL_ID_RECURSIVE;
} function_scope;

const string MULTIPLE_LINE_COMMENT_BEGIN = "=begin";
const string MULTIPLE_LINE_COMMENT_END = "=end";

typedef struct aux {
  string content;
  string type;    
} Token;