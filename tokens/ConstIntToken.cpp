#include "ConstIntToken.h"

ConstIntToken::ConstIntToken(long long value) {
    this->value = value;
}

string ConstIntToken::toString() {
    return std::to_string(value);
}

string ConstIntToken::getType() {
    return "ConstInt";
}
