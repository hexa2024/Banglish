#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType { ID, NUM, ASSIGN, PLUS, MINUS, MUL, DIV, PRINT, SEMICOLON, END, ERROR };

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &src);

#endif
