#include "Type.h"
#include "Globals.h"

#include <string>
#include <map>

using std::string;
using std::map;


bool Type::isDefault() const {
    if (name.substr(0, 3) == "int") {
        return 1;
    }
    if (name.substr(0, 4) == "char") {
        return 1;
    }
    if (isPointer() > 0) {
        return 1;
    }
    //if (name.substr(0, 4) == "long") {
    //    return 1;
    //}
    return 0;
}
size_t Type::isPointer() const {
    for (int i = name.length() - 1; i >= 0; i--) {
        if (name[i] != '*') {
            return name.length() - i - 1;
        }
    }
    return 0;//Error!
}

void Type::setSize() {
    if (isPointer() > 0) {
        size = 8;
    } else if (isDefault()) {
        if (name.substr(0, 3) == "int") {
            size = 8;
        } else if (name.substr(0, 4) == "char") {
            size = 1;
        }// else if (name.substr(0, 4) == "long") {
        //    size = 8;
        //}
    } else if (structs.count(name) > 0){
        size = structs[name].size;
    } else {
        name = "Error";
    }
}

Type::Type(const string &name) {
    this->name = name;
    length = 0;
    setSize();
}

Type::Type(const string &name, size_t size) {
    this->name = name;
    this->size = size;
    length = 0;
}

Type::Type() {
    this->name = "error";
    this->size = 0;
    length = 0;
}

bool Type::setMax(const Type &a, const Type &b) {
    if (a.isPointer() > 0 && b.isPointer() > 0) {
        return 1;
    }
    if (!a.isDefault() || !a.isDefault()) {
        return 0;
    }
    if (a.isPointer() > 0) {
        name = a.name;
        size = a.size;
        return 1;
    }
    if (b.isPointer() > 0) {
        name = b.name;
        size = b.size;
        return 1;
    }
    if (a.size < b.size) {
        name = a.name;
        size = a.size;
        return 1;
    } else {
        name = b.name;
        size = b.size;
        return 1;
    }
}

Type Type::toPointer() {
    return Type(this->name + "*");
}

Type Type::setLength(size_t length) {
    this->length = length;
    setSize();
    return *this;
}

void Type::dereference() {
    name.pop_back();
    setSize();
}
