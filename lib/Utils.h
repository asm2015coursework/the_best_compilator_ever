#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>

using std::string;

string FileToString(string file_name);//returns NULL if failed to read file
int FileFromString(string file_name, string source);//returns 1 if failed to write string

#endif // UTILS_H
