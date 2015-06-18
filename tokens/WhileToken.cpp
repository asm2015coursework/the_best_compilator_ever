#include "WhileToken.h"

WhileToken::WhileToken(Token* expr, Token* cmd) {
    this->expr = expr;
    this->cmd = cmd;
}

string WhileToken::toString() {
    return "while (" + expr->toString() + ") " + cmd->toString();
}

string WhileToken::getType() {
    return "While";
}
