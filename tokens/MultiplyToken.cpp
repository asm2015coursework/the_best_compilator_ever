#include "MultiplyToken.h"

MultiplyToken::MultiplyToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string MultiplyToken::toString() {
    return "(" + left->toString() + "*" + right->toString() + ")";
}
