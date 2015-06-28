#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <map>
#include <utility>

#include <Type.h>

using std::string;
using std::map;
using std::pair;

class Struct {
public:
    size_t size;
    map<string, Type> functions;
    map<string, pair<size_t, Type> > vars;
};

#endif // STRUCT_H
