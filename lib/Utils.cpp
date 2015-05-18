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

