#include "config.h"

#include <string>
#include <iostream>

using namespace std::literals;

void ClearCin() {
    std::cin.clear();
    std::string line;
    std::getline(std::cin, line);
    std::cout << "Incorrect input"s << std::endl
              << "Try again: "s;
}

Config SetConfig() {
    Config config;

    std::cout << "Enter input file glob pattern: "s;
    std::cin >> config.input_file_glob_pattern;

    std::cout <<"Enter 1 if you want to delete input file after modification, 0 otherwise: "s;
    while (!(std::cin >> config.delete_input_file)) {
        ClearCin();
    }

    std::cout << "\nEnter 1 if you want to rewrite existing output file, 0 if you want to modify it: "s;
    while (!(std::cin >> config.rewrite)) {
        ClearCin();
    }

    std::cout << "\nEnter 1 if you want to run file modification once, 0 if you want to repeat it in equal intervals: "s;
    while (!(std::cin >> config.run_once)) {
        ClearCin();
    }

    if (config.timer_step) {
        std::cout << "\nEnter timer step in seconds: "s;
        while (!(std::cin >> config.timer_step)) {
            ClearCin();
        }
    }

    std::cout << "\nEnter a number: "s;
    while (!(std::cin >> config.value_for_modification)) {
        ClearCin();
    }

    return config;
}
