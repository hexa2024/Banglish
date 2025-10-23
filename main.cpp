#include <iostream>
#include "lexer.cpp"
#include "parser.cpp"
using namespace std;

int main() {
    string code = "a = 5; b = a * 3 + 2; print b;";
    auto tokens = tokenize(code);

    cout << "Tokens:\n";
    for (auto &t : tokens)
        cout << t.value << " ";

    cout << "\n\nParsing...\n";
    parse();

    return 0;
}
