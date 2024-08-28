#pragma once

#include "config.h"

#include <string>
#include <set>

class FileProcessor {
public:
    FileProcessor(Config config);

    static std::string GetFileName(bool input = true);
    void ModifyFile(const std::string& input, const std::string& output);
    void Run();

private:
    Config config_;
    std::set<std::string> output_files_;
};

