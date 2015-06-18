#include "ForToken.h"

ForToken::ForToken(Token* expr1, Token* expr2, Token* expr3, Token* cmd) {
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
    this->cmd = cmd;
}

string ForToken::toString() {
    string ans = "for (" + expr1->toString() + ";" + expr2->toString() + ";";
    ans += expr3->toString() + ") " + cmd->toString();
    return ans;
}

string ForToken::getType() {
    return "For";
}
