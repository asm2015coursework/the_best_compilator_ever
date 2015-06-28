#include "ForToken.h"

ForToken::ForToken(Token* expr1, Token* expr2, Token* expr3, Token* cmd) {
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
    this->cmd = cmd;
}

string ForToken::toString() {
    //string ans = "for (" + expr1->toString() + ";" + expr2->toString() + ";";
    //ans += expr3->toString() + ") " + cmd->toString();
    string ans = "for (";
    if (expr1 != nullptr) ans += expr1->toString();
    ans += ";";
    if (expr2 != nullptr) ans += expr2->toString();
    ans += ";";
    if (expr3 != nullptr) ans += expr3->toString();
    ans += ") ";
    if (cmd != nullptr) ans += cmd->toString();
    return ans;
}

string ForToken::getType() {
    return "For";
}
