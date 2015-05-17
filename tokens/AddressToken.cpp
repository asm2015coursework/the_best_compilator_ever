#include "AddressToken.h"

AddressToken::AddressToken(Token* expr) {
    this->expr = expr;
}

string AddressToken::toString() {
    return "(&" + expr->toString() + ")";
}
