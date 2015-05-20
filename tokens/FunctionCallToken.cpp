#include "FunctionCallToken.h"

FunctionCallToken::FunctionCallToken(string name, vector<Token*> args) {
    this->name = name;
    this->args = args;
}

string FunctionCallToken::toString() {
    string ans = name + "(";
    for (size_t i = 0; i < args.size() - 1; i++) {
        ans += args[i]->toString() + ", ";
    }
    ans += args[args.size() - 1]->toString() + ")";
    return ans;
}

string FunctionCallToken::getType() {
    return "FunctionCall";
}
