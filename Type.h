#ifndef TYPE_H
#define TYPE_H

#include <string>

#include "Type.h"

using std::string;



struct Type {
    string name;
    size_t size;
    size_t length;

    bool isDefault() const;
    size_t isPointer() const;
    void setSize();
    Type(const string &name);
    Type(const string &name, size_t size);
    Type();
    bool setMax(const Type &a, const Type &b);
    Type toPointer();
    Type setLength(size_t length);
    void dereference();
};

#endif // TYPE_H
