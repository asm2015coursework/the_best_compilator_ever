#include "StructFunctionCallToken.h"

StructFunctionCallToken::StructFunctionCallToken(Token* expr, string name, vector<Token*> args) {
    this->expr = expr;
    this->name = name;
    this->args = args;
}

string StructFunctionCallToken::toString() {
    string ans = "(" + expr->toString() + ")." + name + "(";
    for (size_t i = 0; i < args.size() - 1; i++) {
        ans += args[i]->toString() + ", ";
    }
    ans += args[args.size() - 1]->toString() + ")";
    return ans;
}

string StructFunctionCallToken::getType() {
    return "StructFunctionCall";
}
