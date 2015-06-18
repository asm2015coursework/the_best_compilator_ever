#include "NotToken.h"

NotToken::NotToken(Token* expr) {
    this->expr = expr;
}

string NotToken::toString() {
    return "(!" + expr->toString() + ")";
}

string NotToken::getType() {
    return "Not";
}
