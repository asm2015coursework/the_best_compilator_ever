#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <map>
#include <Type.h>
#include <utility>

using std::string;
using std::map;
using std::pair;

class Variable {
public:
    string _type;
    string _name;
    Variable(string type, string name) {
        this->_type = type;
        this->_name = name;
    }
};

class Struct {
public:
    map<string, Type> functions;
    map<string, pair<size_t, Type> > vars;
};

#endif // VARIABLE_H
