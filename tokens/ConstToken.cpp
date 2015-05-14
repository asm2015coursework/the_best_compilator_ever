#include "ConstToken.h"

ConstToken::ConstToken(string value) {
    this->_value = value;
}

string ConstToken::toString() {
    return _value;
}
