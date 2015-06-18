#include "ArrayCallToken.h"

ArrayCallToken::ArrayCallToken(string name, Token* expr) {
    this->name = name;
    this->expr = expr;
}

string ArrayCallToken::toString() {
    string ans = name + "[" + expr->toString() + "]";
    return ans;
}

string ArrayCallToken::getType() {
    return "ArrayCall";
}
