#include "semantic.h"
#include <iostream>
using namespace std;

bool SemanticAnalyzer::checkVariable(const std::string &name) {
    if (symbolTable.find(name) == symbolTable.end()) {
        cerr << "Semantic error: variable '" << name << "' not declared.\n";
        return false;
    }
    return true;
}

void SemanticAnalyzer::declareVariable(const std::string &name, const std::string &type) {
    if (symbolTable.find(name) != symbolTable.end()) {
        cerr << "Semantic error: variable '" << name << "' already declared.\n";
    } else {
        symbolTable[name] = type;
    }
}

void SemanticAnalyzer::checkAssignment(const std::string &name, const std::string &type) {
    if (!checkVariable(name))
     return;
    if (symbolTable[name] != type) {
        cerr << "Type warning: assigning '" << type << "' to variable '" << name << "' of type '" << symbolTable[name] << "'.\n";
    }
}
