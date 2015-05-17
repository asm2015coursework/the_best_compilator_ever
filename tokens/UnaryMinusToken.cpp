#include "UnaryMinusToken.h"

UnaryMinusToken::UnaryMinusToken(Token* expr) {
    this->expr = expr;
}

string UnaryMinusToken::toString() {
    return "(-" + expr->toString() + ")";
}

string UnaryMinusToken::getType() {
    return "UnaryMinus";
}
