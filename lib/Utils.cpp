#include "Utils.h"

#include <sstream>


string fileToString(string file_name) {
    std::ifstream file(file_name.c_str());
    if (file.is_open()) {
        string bufferString = "", resultString = "";
        while (file) {
            resultString += bufferString + '\n';
            getline(file, bufferString);
        }
        file.close();
        return resultString;
    } else {
        return "";
    }
}

int fileFromString(string file_name, string source) {
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
    n = -n;
    if (n < 0) {
        sstm << n;
    } else if (n > 0) {
        sstm << "+" << n;
    } else {
        sstm << "-0";
    }
    return sstm.str();
}

