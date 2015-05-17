#include "ReturnToken.h"

ReturnToken::ReturnToken(Token* expr) {
    this->expr = expr;
}

string ReturnToken::toString() {
    return "return " + expr->toString();
}
