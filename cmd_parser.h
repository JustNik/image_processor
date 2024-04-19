//
// Created by justnik on 29.10.2023.
//

#ifndef IMAGE_PROCESSOR_CMD_PARSER_H
#define IMAGE_PROCESSOR_CMD_PARSER_H

#include "filter.h"

#include <cstdint>
#include <string>
#include <vector>

class CMDLineParser {
public:
    CMDLineParser() {}

    CMDLineParser(int argc, char **argv);

    std::string GetInputFilePath() const;

    std::string GetOutputFilePath() const;

    std::vector<FilterParameters> GetFilters();

protected:
    uint32_t arguments_cnt_;
    std::string program_name_;
    std::string input_file_path_;
    std::string output_file_path_;
    std::vector<FilterParameters> filters_;
};

#endif //IMAGE_PROCESSOR_CMD_PARSER_H
