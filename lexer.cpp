#include <iostream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

enum TokenType { ID, NUM, ASSIGN, PLUS, MINUS, MUL, DIV, PRINT, SEMICOLON, END };

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokenize(const string &src) {
    vector<Token> tokens;
    for (size_t i = 0; i < src.size();) {
        if (isspace(src[i])) { i++; continue; }
        if (isalpha(src[i])) {
            string id;
            while (isalnum(src[i])) id += src[i++];
            if (id == "print") tokens.push_back({PRINT, id});
            else tokens.push_back({ID, id});
        } 
        else if (isdigit(src[i])) {
            string num;
            while (isdigit(src[i])) num += src[i++];
            tokens.push_back({NUM, num});
        }
        else {
            switch (src[i]) {
                case '=': tokens.push_back({ASSIGN, "="}); break;
                case '+': tokens.push_back({PLUS, "+"}); break;
                case '-': tokens.push_back({MINUS, "-"}); break;
                case '*': tokens.push_back({MUL, "*"}); break;
                case '/': tokens.push_back({DIV, "/"}); break;
                case ';': tokens.push_back({SEMICOLON, ";"}); break;
            }
            i++;
        }
    }
    tokens.push_back({END, ""});
    return tokens;
}
