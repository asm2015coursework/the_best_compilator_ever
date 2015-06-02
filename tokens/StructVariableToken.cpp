#include "StructVariableToken.h"

StructVariableToken::StructVariableToken(Token* expr, string name) {
    this->expr = expr;
    this->name = name;
}

string StructVariableToken::toString() {
    return "((" + expr->toString() + ")." + name + ")";
}

string StructVariableToken::getType() {
    return "StructVariable";
}
