#include "AssignmentToken.h"

AssignmentToken::AssignmentToken(Token *left, Token *right) {
    this->left = left;
    this->right = right;
}

string AssignmentToken::toString() {
    return "(" + left->toString() + "=" + right->toString() + ")";
}
