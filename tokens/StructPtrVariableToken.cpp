#include "StructPtrVariableToken.h"

StructPtrVariableToken::StructPtrVariableToken(Token* expr, string name) {
    this->expr = expr;
    this->name = name;
}

string StructPtrVariableToken::toString() {
    return "((" + expr->toString() + ")->" + name + ")";
}

string StructPtrVariableToken::getType() {
    return "StructPtrVariable";
}
