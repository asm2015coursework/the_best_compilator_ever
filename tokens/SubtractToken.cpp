#include "SubtractToken.h"

SubtractToken::SubtractToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string SubtractToken::toString() {
    return "(" + left->toString() + "-" + right->toString() + ")";
}
