#ifndef TYPE_H
#define TYPE_H

#include <string>

using std::string;

struct Type {
    string name;
    size_t size;
    size_t length;

    bool isDefault() const {
        if (name.substr(0, 3) == "int") {
            return 1;
        }
        if (name.substr(0, 4) == "char") {
            return 1;
        }
        //if (name.substr(0, 4) == "long") {
        //    return 1;
        //}
        return 0;
    }

    //bool isLink() const {
    //    return name.back() == '&';
    //}

    size_t isPointer() const {
        for (int i = name.length() - 1; i >= 0; i--) {
            if (name[i] != '*') {
                return name.length() - i - 1;
            }
        }
        return 0;//Error!
    }

    Type(const string &name) {
        this->name = name;
        length = 0;
        if (isPointer() > 0/* || isLink()*/) {
            size = 8;
        } else if (isDefault()) {
            if (name.substr(0, 3) == "int") {
                size = 8;
            } else if (name.substr(0, 4) == "char") {
                size = 1;
            }// else if (name.substr(0, 4) == "long") {
            //    size = 8;
            //}
        } else {
            //size = ///запилить структуры
        }
    }

    Type(const string &name, size_t size) {
        this->name = name;
        this->size = size;
        length = 0;
    }

    Type() {
        this->name = "error";
        this->size = 0;
        length = 0;
    }

    bool setMax(const Type &a, const Type &b) {
        if (!a.isDefault() || !a.isDefault()) {
            return 0;
        }
        if (a.isPointer() > 0 && b.isPointer() > 0) {
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
        if (a.size > b.size) {
            name = a.name;
            size = a.size;
            return 1;
        } else {
            name = b.name;
            size = b.size;
            return 1;
        }
    }

    Type toPointer() {
        return Type(this->name + "*");
    }

    Type setLength(size_t length) {
        this->length = length;
        return *this;
    }

    void dereference() {
        name.pop_back();
    }

};

#endif // TYPE_H
