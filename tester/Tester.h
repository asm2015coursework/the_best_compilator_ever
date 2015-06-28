#ifndef TESTER_H
#define TESTER_H

#include <string>

class Tester{
    int test(std::string, bool);
    void remove_log();
public:
    int run_all(bool);
    int run_tests(int*, bool);
    int run_one(std::string, bool);
};

#endif // TESTER_H
