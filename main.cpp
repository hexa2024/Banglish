#include <iostream>
#include "lexer.h"
#include "parser.h"
using namespace std;

int main() {
    string code = 
        "a = 5;\n"
        "b = a * 3 + 2;\n"
        "print b;\n"
        "c = 7 /3 ;\n"; // Intentional error

    vector<Token> tokens = tokenize(code);

    cout << "Tokens:\n";
    for (auto &t : tokens) {
        cout << "Token(" << t.value << ")";
        if (t.type == ERROR) cout << " <-- Lexical error!";
        cout << "\n";
    }
    cout << "\nParsing:\n";

    parse(tokens);

    return 0;
}
