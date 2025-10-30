#include "parser.h"
#include "semantic.h"
#include <iostream>
using namespace std;

static size_t pos = 0;
static vector<Token> tokenStream;
static SemanticAnalyzer semantic;
static ostream &code = cout;

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

static pair<string,string> factor() {
    if (pos >= tokenStream.size()) { error("Unexpected end in factor"); return {"0","int"}; }
    Token t = tokenStream[pos];

    if (t.type == ID) {
        pos++;
        if (!semantic.checkVariable(t.value)) return {t.value,"int"};
        return {t.value, semantic.symbolTable[t.value]};
    } 
    else if (t.type == NUM) {
        pos++;
        if (t.value.find('.') != string::npos) return {t.value,"float"};
        else return {t.value,"int"};
    } 
    else {
        error("Expected identifier or number in factor");
        pos++;
        return {"0","int"};
    }
}

static pair<string,string> term() {
    auto left = factor();
    while (pos < tokenStream.size() && (tokenStream[pos].type == MUL || tokenStream[pos].type == DIV)) {
        TokenType op = tokenStream[pos].type; pos++;
        auto right = factor();
        left.first = "(" + left.first + (op==MUL?"*":"/") + right.first + ")";
        if (left.second=="float" || right.second=="float") left.second="float";
    }
    return left;
}

static pair<string,string> expr() {
    auto left = term();
    while (pos < tokenStream.size() && 
          (tokenStream[pos].type==PLUS || tokenStream[pos].type==MINUS || 
           tokenStream[pos].type==GREATER || tokenStream[pos].type==LESS)) {
        TokenType op = tokenStream[pos].type; pos++;
        auto right = term();
        string opStr = (op==PLUS?"+": op==MINUS?"-": op==GREATER?">":"<");
        left.first = "(" + left.first + opStr + right.first + ")";
        if (left.second=="float" || right.second=="float") left.second="float";
    }
    return left;
}

static void stmt();

static void block() {
    while (pos < tokenStream.size() && tokenStream[pos].type != RBRACE)
        stmt();
    if (!match(RBRACE)) error("Expected '}' after block");
}

static void stmt() {
    if (pos>=tokenStream.size()) return;

    Token t = tokenStream[pos];

    if (t.type==INT || t.type==FLOAT) {
        string typeStr = (t.type==INT?"int":"float"); pos++;
        if (pos<tokenStream.size() && tokenStream[pos].type==ID) {
            string varName = tokenStream[pos].value; pos++;
            semantic.declareVariable(varName,typeStr);
            if (match(ASSIGN)) {
                auto exprResult = expr();
                code << "    " << typeStr << " " << varName << " = " << exprResult.first << ";\n";
            } else {
                code << "    " << typeStr << " " << varName << ";\n";
            }
            if (!match(SEMICOLON)) error("Expected ';' after declaration");
        } else error("Expected identifier after type");
    }
    else if (t.type==ID) {
        string varName = t.value; pos++;
        if (!match(ASSIGN)) { error("Expected '=' after identifier"); return; }
        auto exprResult = expr();
        semantic.checkAssignment(varName, exprResult.second);
        code << "    " << varName << " = " << exprResult.first << ";\n";
        if (!match(SEMICOLON)) error("Expected ';' at end of statement");
    }
    else if (t.type==PRINT) {
        pos++;
        auto exprResult = expr();
        code << "    cout << " << exprResult.first << " << endl;\n";
        if (!match(SEMICOLON)) error("Expected ';' after print");
    }
    else if (t.type==IF) {
        pos++;
        if (!match(LPAREN)) { error("Expected '(' after if"); return; }
        auto cond = expr();
        if (!match(RPAREN)) { error("Expected ')' after condition"); return; }
        if (!match(LBRACE)) { error("Expected '{' after if"); return; }

        code << "    if (" << cond.first << ") {\n";
        block();
        code << "    }\n";

        if (pos < tokenStream.size() && tokenStream[pos].type == ELSE) {
            pos++;
            if (!match(LBRACE)) { error("Expected '{' after else"); return; }
            code << "    else {\n";
            block();
            code << "    }\n";
        }
    }
    else if (t.type==FOR) {
        pos++;
        if (!match(LPAREN)) { error("Expected '(' after for"); return; }

        auto init = expr();
        if (!match(SEMICOLON)) { error("Expected ';' in for"); return; }
        auto cond = expr();
        if (!match(SEMICOLON)) { error("Expected ';' in for"); return; }
        auto step = expr();
        if (!match(RPAREN)) { error("Expected ')' after for"); return; }
        if (!match(LBRACE)) { error("Expected '{' after for"); return; }

        code << "    for (" << init.first << "; " << cond.first << "; " << step.first << ") {\n";
        block();
        code << "    }\n";
    }
    else { error("Unknown statement"); pos++; }
}

void parse(const vector<Token>& tokens) {
    tokenStream = tokens; pos=0;
    code << "#include <iostream>\nusing namespace std;\nint main() {\n";
    while(pos<tokenStream.size() && tokenStream[pos].type!=END) stmt();
    code << "    return 0;\n}\n";
}
