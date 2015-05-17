#include "ReturnToken.h"

ReturnToken::ReturnToken(Token* expr) {
    this->expr = expr;
}

string ReturnToken::toString() {
    if (expr == nullptr) return "return";
        else return "return " + expr->toString();
}
