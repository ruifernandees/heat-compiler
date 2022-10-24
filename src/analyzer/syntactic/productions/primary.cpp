#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <regex>

#include "../syntactic-analyzer.h"
#include "../utils/eat.cpp"

#pragma once

using namespace std;



bool primary(vector<Token> tokens, int* currentToken) 
{
    int pastToken = *currentToken;

    // possibilidade 1
    if (tokens[*currentToken].content.compare("(") == 0) {
        eat(currentToken);
        if (compstmt(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare(")") == 0) {
                eat(currentToken);
                if (primaryL(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 2
    if (literal(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }
    
    *currentToken = pastToken;

    // possibilidade 3
    if (variable(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    };

    *currentToken = pastToken;

    // possibilidade 4
    if (tokens[*currentToken].content.compare("::") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 5
    if (tokens[*currentToken].content.compare("[") == 0) {
        eat(currentToken);
        tentarLer1(tokens, currentToken);
        
        if (tokens[*currentToken].content.compare("]") == 0) {
            eat(currentToken);
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }


    *currentToken = pastToken;

    // possibilidade 6
    if (tokens[*currentToken].content.compare("{") == 0) {
        eat(currentToken);
        tentarLer1(tokens, currentToken);
        if (tokens[*currentToken].content.compare("}")) {
            eat(currentToken);
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }
    
    *currentToken = pastToken;

    // possibilidade 7
    if (tokens[*currentToken].content.compare("{") == 0) {
        eat(currentToken);
        tentarLer3(tokens, currentToken);
        if (tokens[*currentToken].content.compare("}") == 0) {
            eat(currentToken);
            if (primaryL(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 8
    if (tokens[*currentToken].content.compare("return") == 0) {
        eat(currentToken);
        tentarLer4(tokens, currentToken);
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 9
    if (Function(tokens, currentToken)) {
        if (primaryL(tokens, currentToken)) {
            return true;
        }
    }

    *currentToken = pastToken;

    // possibilidade 10
    if (Function(tokens, currentToken)) {
        if (tokens[*currentToken].content.compare("{") == 0) {
            eat(currentToken);
            tentarLer6(tokens, currentToken);
            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("}") == 0) {
                    eat(currentToken);
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
    
    // possiblidade 11
    if (tokens[*currentToken].content.compare("if") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (then(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    while (funcaoComAsterisco(tokens, currentToken)) {}

                    tentarLer8(tokens, currentToken);

                    if (tokens[*currentToken].content.compare("end") == 0) {
                        eat(currentToken);                        
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    *currentToken = pastToken;

    // possibilidade 11
    if (tokens[*currentToken].content.compare("while") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (_do(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare("end") == 0) {
                        eat(currentToken);
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 11 -- REMOVIDA
    
    // possibilidade 12 
    if (tokens[*currentToken].content.compare("for") == 0) {
        eat(currentToken);
        if (block_var(tokens, currentToken)) {
            if (tokens[*currentToken].content.compare("in") == 0) {
                eat(currentToken);
                if (expr(tokens, currentToken)) {
                    if (_do(tokens, currentToken)) {
                        if (compstmt(tokens, currentToken)) {
                            if (tokens[*currentToken].content.compare("end") == 0) {
                                eat(currentToken);
                                if (primaryL(tokens, currentToken)) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    

    *currentToken = pastToken;

    // possibilidade 13
    if (tokens[*currentToken].content.compare("begin") == 0) {
        eat(currentToken);
        if (compstmt(tokens, currentToken)) {
            // bloco do + abaixo
            if (funcaoComMais(tokens, currentToken)) {

                while (funcaoComMais(tokens, currentToken)) {}

                tentarLer8(tokens, currentToken);
                tentarLer10(tokens, currentToken);

                if (tokens[*currentToken].content.compare("end") == 0) {
                    eat(currentToken);
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;
        
    // [rescue [ARGS] DO COMPSTMT]+

    // possibilidade 14
    if (tokens[*currentToken].content.compare("class") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            tentarLer11(tokens, currentToken);
            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("end") == 0) {
                    eat(currentToken);
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                } 
            }
        }
    }

    *currentToken = pastToken;
    
    // possibilidade 15 
    if (tokens[*currentToken].content.compare("module") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                if (tokens[*currentToken].content.compare("end") == 0) {
                    eat(currentToken);
                    if (primaryL(tokens, currentToken)) {
                        return true;
                    }
                }
            }
        }
    }

    *currentToken = pastToken;

    // possibilidade 16 aleluia
    if (tokens[*currentToken].content.compare("def") == 0) {
        eat(currentToken);
        if (fname(tokens, currentToken)) {
            if (argdecl(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    if (tokens[*currentToken].content.compare("end") == 0) {
                        eat(currentToken);
                        if (primaryL(tokens, currentToken)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    *currentToken = pastToken;

    return false;
}

bool funcaoComMais(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare("rescue") == 0) {
        eat(currentToken);
        tentarLer9(tokens, currentToken);
        if (_do(tokens, currentToken)) {
            if (compstmt(tokens, currentToken)) {
                return true;
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

bool funcaoComAsterisco(vector<Token> tokens, int* currentToken) {
    int pastToken = *currentToken;

    if (tokens[*currentToken].content.compare("elsif") == 0) {
        eat(currentToken);
        if (expr(tokens, currentToken)) {
            if (then(tokens, currentToken)) {
                if (compstmt(tokens, currentToken)) {
                    return true;
                }
            }
        }
    }

    *currentToken = pastToken;

    return false;
}

void tentarLer1(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        tentarLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer2(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare(",") == 0) {
        eat(currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer3(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (assocs(tokens, currentToken)) {
        tentarLer2(tokens, currentToken);
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer4(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("(")) {
        eat(currentToken);
        tentarLer5(tokens, currentToken);
        if (tokens[*currentToken].content.compare(")") == 0) {
            eat(currentToken);
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarLer5(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (call_args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer6(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("|") == 0) {
        eat(currentToken);
        tentarLer7(tokens, currentToken);
        if (tokens[*currentToken].content.compare("|") == 0) {
            eat(currentToken);
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarLer7(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (block_var(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer8(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("else") == 0) {
        eat(currentToken);
        if (compstmt(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarLer9(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (args(tokens, currentToken)) {
        return;
    }

    *currentToken = pstToken;
    return;
}

void tentarLer10(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("ensure") == 0) {
        eat(currentToken);
        if (compstmt(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}

void tentarLer11(vector<Token> tokens, int* currentToken)
{
    int pstToken = *currentToken;

    if (tokens[*currentToken].content.compare("<") == 0) {
        eat(currentToken);
        if (identifier(tokens, currentToken)) {
            return;
        }
    }

    *currentToken = pstToken;
    return;
}