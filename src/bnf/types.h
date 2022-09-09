#define KEYWORD "KEYWORD"
#define IDENTIFIER "IDENTIFIER"
#define OPERATOR "OPERATOR"
#define DELIMITER "DELIMITER"
#define DIGIT "DIGIT"

#pragma once

using namespace std;

typedef struct aux {
  string content;
  string type;    
} Token;