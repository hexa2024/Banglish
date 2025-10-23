#include "lexer.h"
#include <cctype>
using namespace std;

vector<Token> tokenize(const string &src) {
    vector<Token> tokens;
    size_t i = 0;

    while (i < src.size()) {
        if (isspace(src[i])) { 
            i++; 
            continue; 
        }

        if (isalpha(src[i])) {
            string id;
            while (i < src.size() && isalnum(src[i])) {
                id += src[i++];
            }
            if (id == "print") tokens.push_back({PRINT, id});
            else tokens.push_back({ID, id});
        } 
        else if (isdigit(src[i])) {
            string num;
            while (i < src.size() && isdigit(src[i])) {
                num += src[i++];
            }
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
                default:
                    tokens.push_back({ERROR, string(1, src[i])});
                    break;
            }
            i++;
        }
    }

    tokens.push_back({END, ""});
    return tokens;
}
