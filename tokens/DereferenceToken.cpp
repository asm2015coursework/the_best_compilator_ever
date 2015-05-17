#include "DereferenceToken.h"

DereferenceToken::DereferenceToken(Token* expr) {
    this->expr = expr;
}

string DereferenceToken::toString() {
    return "(*" + expr->toString() + ")";
}

string DereferenceToken::getType() {
    return "Dereference";
}
