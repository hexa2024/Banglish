#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    INT, FLOAT, PRINT,
    IF, ELSE, // use for a id else 
     FOR, // loop 
    ID, NUM,
    PLUS, MINUS, MUL, DIV,
    ASSIGN, SEMICOLON,
    LPAREN, RPAREN,         // ( ) check a syntex
    LBRACE, RBRACE,         // { }
    GREATER, LESS, EQUAL,   // (optional)
    END
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &source);

#endif
