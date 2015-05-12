#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Variable {
public:
    Variable(string type, string name);

    string _type;
    string _name;
};

#endif // VARIABLE_H
