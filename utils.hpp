#pragma once
#include <iostream>
#include <string>

// stored data fro consumer
struct entry_t {
    int sequence;
    size_t time;
};

// calculate digits in number 
inline int get_digits(int number) {
    int digits = 0;
    if (number < 0) digits = 1;
    while (number) {
        number /= 10;
        ++digits;
    }

    return digits;
}

// get limit number from program arguments
inline int get_limit(int argc, char **argv) {
    try {
        if (argc >= 2)
            return std::stoi(argv[1]);
    }
    catch (...) {
        std::cerr << "task: unable to convert NUMBER from string represenation";
        return 0;
    }

    std::cerr << "task: missing NUMBER\nUsage: task [NUMBER]" << std::endl;
    return 0;
}