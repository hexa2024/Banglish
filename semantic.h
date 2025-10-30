#pragma once
#include <string>
#include <map>

class SemanticAnalyzer {
public:
    std::map<std::string, std::string> symbolTable;

    bool checkVariable(const std::string &name);
    void declareVariable(const std::string &name, const std::string &type);
    void checkAssignment(const std::string &name, const std::string &type);
};
