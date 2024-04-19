//
// Created by justnik on 29.10.2023.
//

#include "cmd_parser.h"
#include <regex>
#include <stdexcept>

CMDLineParser::CMDLineParser(int argc, char **argv) {
    arguments_cnt_ = argc;
    program_name_ = argv[0];
    input_file_path_ = argv[1];
    if (!std::regex_match(input_file_path_, std::regex("^(.+)\/([^\/]+).bmp"))) { // NOLINT
        throw std::runtime_error("Invalid input file path.");
    }
    output_file_path_ = argv[2];
    if (!std::regex_match(input_file_path_, std::regex("^(.+)\/([^\/]+).bmp"))) { // NOLINT
        throw std::runtime_error("Invalid input file path.");
    }
    for (size_t i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (std::regex_match(arg, std::regex("-.+"))) {
            filters_.push_back({arg.substr(1, arg.length() - 1), {}});
        } else {
            filters_.back().params.push_back(arg);
        }
    }
}

std::vector<FilterParameters> CMDLineParser::GetFilters() {
    return filters_;
}

std::string CMDLineParser::GetInputFilePath() const {
    return input_file_path_;
}

std::string CMDLineParser::GetOutputFilePath() const {
    return output_file_path_;
}
