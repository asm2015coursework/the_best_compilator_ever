#include "UnaryPlusToken.h"

UnaryPlusToken::UnaryPlusToken(Token* expr) {
    this->expr = expr;
}

string UnaryPlusToken::toString() {
    return "(+" + expr->toString() + ")";
}

