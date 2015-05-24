#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Variable {
public:
    string _type;
    string _name;
    Variable(string type, string name) {
        this->_type = type;
        this->_name = name;
    }
};

#endif // VARIABLE_H
