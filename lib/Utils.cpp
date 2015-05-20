#include "Utils.h"

#include <sstream>


string FileToString(string file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        // get length of file:
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);

        char * buffer = new char [length];
        // read data as a block:
        file.read (buffer, length);

        if (!file) {
            file.close();
            delete[] buffer;
            return NULL;
        } else {
            file.close();
            string source(buffer);
            delete[] buffer;
            return source;
        }
    } else {
        file.close();
        return NULL;
    }
}

int FileFromString(string file_name, string source) {
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << source;
        file.close();
        return 0;
    } else {
        return 1;
    }
}

string exec(string cmd) {
    FILE* file = popen(cmd.c_str(), "r");
    if (!file)
        return "Error while run " + cmd;
    char buffer[4096];
    string result = "";
    while(!feof(file)) {
        if(fgets(buffer, 4096, file) != NULL)
            result += buffer;
    }
    pclose(file);
    return result;
}

string sizeToString(size_t n) {
    std::stringstream sstm;
    sstm << n;
    return sstm.str();
}

string intToString(int n) {
    std::stringstream sstm;
    sstm << n;
    return sstm.str();
}

string offsetToString(long long n) {
    std::stringstream sstm;
    if (n > 0) {
        sstm << "+ " << n;
    } else if (n < 0) {
        sstm << n;
    }
    //надеюсь, при нуле будет возвращаться пустая строка
    return sstm.str();
}
