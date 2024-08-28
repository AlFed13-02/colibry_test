#pragma once

#include <string>
#include <cstdint>

struct Config {
    std::string input_file_glob_pattern;
    bool delete_input_file;
    bool rewrite;
    bool run_once;
    int timer_step{};
    int64_t value_for_modification{};
};

void ClearCin();
Config SetConfig();
