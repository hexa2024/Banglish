#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  

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

    ofstream out("output.cpp");
    streambuf* coutbuf = cout.rdbuf(); 
    cout.rdbuf(out.rdbuf()); 

    parse(tokens);

    cout.rdbuf(coutbuf); 
    out.close();

    cout << "\nBanglish code compiled to 'output.cpp'\n";

    
    int compileResult = system("g++ output.cpp -o program.exe");
    if (compileResult != 0) {
        cerr << "Error: Failed to compile generated C++ code.\n";
        return 1;
    }

    cout << " Running program...\n\n";
    system(".\\program.exe");

    return 0;
}
