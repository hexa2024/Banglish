#include "parser.h"
#include <iostream>
using namespace std;

static size_t pos = 0;
static vector<Token> tokenStream;

static bool match(TokenType expected) {
    if (pos < tokenStream.size() && tokenStream[pos].type == expected) {
        pos++;
        return true;
    }
    return false;
}

static void error(const string& msg) {
    if (pos < tokenStream.size())
        cerr << "Syntax error at token '" << tokenStream[pos].value << "': " << msg << "\n";
    else
        cerr << "Syntax error at end of input: " << msg << "\n";
}

static void factor() {
    if (pos >= tokenStream.size()) {
        error("Unexpected end of input in factor");
        return;
    }

    TokenType t = tokenStream[pos].type;
    if (t == ID || t == NUM) {
        pos++;
    } else {
        error("Expected identifier or number in factor");
        pos++;  // Try to recover
    }
}

static void term() {
    factor();
    while (pos < tokenStream.size() && 
          (tokenStream[pos].type == MUL || tokenStream[pos].type == DIV)) {
        pos++;
        factor();
    }
}

static void expr() {
    term();
    while (pos < tokenStream.size() && 
          (tokenStream[pos].type == PLUS || tokenStream[pos].type == MINUS)) {
        pos++;
        term();
    }
}

static void stmt() {
    if (pos >= tokenStream.size()) {
        error("Unexpected end of input in statement");
        return;
    }

    if (tokenStream[pos].type == ID) {
        pos++;
        if (!match(ASSIGN)) {
            error("Expected '=' after identifier");
            return;
        }
        expr();
        if (!match(SEMICOLON)) {
            error("Expected ';' at end of statement");
        }
    } else if (tokenStream[pos].type == PRINT) {
        pos++;
        if (pos < tokenStream.size() && tokenStream[pos].type == ID) {
            pos++;
        } else {
            error("Expected identifier after 'print'");
        }
        if (!match(SEMICOLON)) {
            error("Expected ';' after print statement");
        }
    } else {
        error("Expected statement");
        pos++;
    }
}

void parse(const vector<Token>& tokens) {
    tokenStream = tokens;
    pos = 0;

    while (pos < tokenStream.size() && tokenStream[pos].type != END) {
        stmt();
    }

    if (pos == tokenStream.size() || tokenStream[pos].type == END)
        cout << "Parsing completed successfully.\n";
    else
        cout << "Parsing ended prematurely.\n";
}
