#include "NameToken.h"

NameToken::NameToken(string name) {
    this->_name = name;
}

string NameToken::toString() {
    return _name;
}
