#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string;

#define println(x) std::cout << x << std::endl;

string fileToString(string file_name);//returns empty string if failed to read file
int fileFromString(string file_name, string source);//returns 1 if failed to write string
string exec(string);// executes command and returns command's output
string sizeToString(size_t);
string intToString(int);
string offsetToString(long long);

#endif // UTILS_H
