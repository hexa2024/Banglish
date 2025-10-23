#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Token { int type; string value; };
extern vector<Token> tokens;
int pos = 0;

bool match(int type) {
    if (tokens[pos].type == type) { pos++; return true; }
    return false;
}

void expr();  // forward declaration

void factor() {
    if (tokens[pos].type == ID || tokens[pos].type == NUM) pos++;
    else cout << "Syntax error in factor\n";
}

void term() {
    factor();
    while (tokens[pos].type == MUL || tokens[pos].type == DIV) {
        pos++;
        factor();
    }
}

void expr() {
    term();
    while (tokens[pos].type == PLUS || tokens[pos].type == MINUS) {
        pos++;
        term();
    }
}

void stmt() {
    if (tokens[pos].type == ID) {
        pos++;
        if (match(3)) { // ASSIGN
            expr();
            if (!match(8)) cout << "Missing semicolon\n"; // SEMICOLON
        }
    } else if (tokens[pos].type == 7) { // PRINT
        pos++;
        if (tokens[pos].type == ID) pos++;
        else cout << "Expected identifier after print\n";
        if (!match(8)) cout << "Missing semicolon\n";
    }
}

void parse() {
    while (tokens[pos].type != 9) { // END
        stmt();
    }
    cout << "Parsing complete.\n";
}
