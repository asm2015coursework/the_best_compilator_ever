#include "ArrayCallToken.h"

ArrayCallToken::ArrayCallToken(Token* name, Token* expr) {
    this->name = name;
    this->expr = expr;
}

string ArrayCallToken::toString() {
    string ans = "(" + name->toString() + ")[" + expr->toString() + "]";
    return ans;
}

string ArrayCallToken::getType() {
    return "ArrayCall";
}
