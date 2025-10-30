#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <cstdlib>   // for system()

using namespace std;

int main() {
    cout << "Enter Banglish code (end with END):\n";

    string line, source;
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        source += line + "\n";
    }

    auto tokens = tokenize(source);

    // Redirect generated C++ code to a file
    ofstream out("output.cpp");
    streambuf* coutbuf = cout.rdbuf(); // save old buffer
    cout.rdbuf(out.rdbuf()); // redirect cout to output.cpp

    parse(tokens);

    cout.rdbuf(coutbuf); // restore cout
    out.close();

    cout << "\n✅ Banglish code compiled to 'output.cpp'\n";

    // Compile the generated C++ code
    int compileResult = system("g++ output.cpp -o program.exe");
    if (compileResult != 0) {
        cerr << "❌ Error: Failed to compile generated C++ code.\n";
        return 1;
    }

    cout << "▶ Running program...\n\n";
    system(".\\program.exe"); // Run compiled program

    return 0;
}
