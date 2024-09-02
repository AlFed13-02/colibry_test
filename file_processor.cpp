#include "config.h"
#include "file_processor.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <thread>
#include <chrono>
#include <cstdint>

using namespace std::literals;

FileProcessor::FileProcessor(Config config)
    :config_(std::move(config)) {}

std::string FileProcessor::GetFileName(bool input) {
    std::string filename;
    if (input) {
        std::cout << "Enter a file name for modification: "s;
    } else {
        std::cout << "Enter an output file name: "s;
    }
    std::cin >> filename;
    return filename;
}

void FileProcessor::ModifyFile(const std::string& input, const std::string& output) {
    std::fstream input_file(input.data(), std::ios::in | std::ios::binary);
    if (!input_file.is_open()) {
        return;
    }

    std::fstream output_file;

    if (output_files_.count(output) == 0) {
        output_files_.insert(output);
        output_file.open(output.data(), std::ios::out | std::ios::binary);
    } else if (config_.rewrite) {
        output_file.open(output.data(), std::ios::out | std::ios::trunc | std::ios::binary);
    } else {
        output_file.open(output.data(), std::ios::app | std::ios::binary);
    }

    int64_t word{};
    while (input_file.read(reinterpret_cast<char*>(&word), sizeof word)) {
        word = word ^ config_.value_for_modification;
        output_file.write(reinterpret_cast<char*>(&word), sizeof word);
    }

    input_file.close();
    output_file.close();

    if (config_.delete_input_file) {
        std::filesystem::path path{input};
        std::filesystem::remove(path);
    }
}

void FileProcessor::Run() {
    if (config_.run_once) {
        auto input_filename = GetFileName();
        auto output_filename = GetFileName(false);
        ModifyFile(input_filename, output_filename);
    } else {
        bool is_there_a_file;
        while (true) {
            std::cout << "Would you like to modify any file? 0 - no, 1 - yes: "s;
            while(!(std::cin >> is_there_a_file)) {
                ClearCin();
            }

            if (is_there_a_file) {
                auto input_filename = GetFileName();
                auto output_filename = GetFileName(false);
                ModifyFile(input_filename, output_filename);
            }

            std::this_thread::sleep_for(std::chrono::seconds(config_.timer_step));
        }
    }
}


