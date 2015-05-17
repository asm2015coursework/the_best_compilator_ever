#include "AndToken.h"

AndToken::AndToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string AndToken::toString() {
    return "(" + left->toString() + "&" + right->toString() + ")";
}

string AndToken::getType() {
    return "And";
}
