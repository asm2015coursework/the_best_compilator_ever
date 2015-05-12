#include "VariableToken.h"

VariableToken::VariableToken(string name) {
    this->_name = name;
}

string VariableToken::toString() {
    return _name;
}
