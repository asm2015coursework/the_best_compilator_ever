#include "StructToken.h"

StructToken::StructToken(string name, vector<InitializationToken*> variables, vector<FunctionToken*> functions) {
    this->name = name;
    this->variables = variables;
    this->functions = functions;
}

string StructToken::toString() {
    string ans = "struct " + name + " {\n";
    for (size_t i = 0; i < variables.size(); i++) {
        ans += variables[i]->toString() + ";\n";
    }
    for (size_t i = 0; i < functions.size(); i++) {
        ans += functions[i]->toString() + "\n";
    }
    ans += "}\n";
    return ans;
}

string StructToken::getType() {
    return "Struct";
}
