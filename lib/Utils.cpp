#include "Utils.h"

string FileToString(string file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        string bufferString, resultString = "";
        while (!file.eof()) {
            getline(file, bufferString);
            resultString += bufferString + '\n';
        }
        file.close();
        return resultString;
    } else {
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
