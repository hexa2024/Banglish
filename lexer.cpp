#include "lexer.h"
#include <cctype>
#include <sstream>

std::vector<Token> tokenize(const std::string &source) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < source.size()) {
        if (isspace(source[i])) { 
            i++; 
            continue; 
        }

        // Identifier or keyword
        if (isalpha(source[i])) {
            std::string id;
            while (i < source.size() && (isalnum(source[i]) || source[i]=='_'))
                id += source[i++];
            
            if (id == "int") tokens.push_back({INT, id});
            else if (id == "float") tokens.push_back({FLOAT, id});
            else if (id == "print") tokens.push_back({PRINT, id});
            else if (id == "if") tokens.push_back({IF, id});
            else if (id == "else") tokens.push_back({ELSE, id});
            else if (id == "for") tokens.push_back({FOR, id});
            else tokens.push_back({ID, id});
        }
        
        else if (isdigit(source[i])) {
            std::string num;
            bool dot = false;  
            while (i < source.size() && (isdigit(source[i]) || source[i] == '.')) {
                if (source[i] == '.') {
                    if (dot) break; 
                    dot = true;
                }
                num += source[i++];
            }
            tokens.push_back({NUM, num});
        }
    
        else {
            switch (source[i]) {
                case '+': tokens.push_back({PLUS, "+"}); break;
                case '-': tokens.push_back({MINUS, "-"}); break;
                case '*': tokens.push_back({MUL, "*"}); break;
                case '/': tokens.push_back({DIV, "/"}); break;
                case '=': tokens.push_back({ASSIGN, "="}); break;
                case ';': tokens.push_back({SEMICOLON, ";"}); break;
                case '(': tokens.push_back({LPAREN, "("}); break;
                case ')': tokens.push_back({RPAREN, ")"}); break;
                case '{': tokens.push_back({LBRACE, "{"}); break;
                case '}': tokens.push_back({RBRACE, "}"}); break;
                case '>': tokens.push_back({GREATER, ">"}); break;
                case '<': tokens.push_back({LESS, "<"}); break;
                default: break; 
            }
            i++;
        }
    }

    tokens.push_back({END, ""});
    return tokens;
}
