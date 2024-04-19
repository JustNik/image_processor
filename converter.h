//
// Created by justnik on 30.10.2023.
//

#ifndef IMAGE_PROCESSOR_CONVERTER_H
#define IMAGE_PROCESSOR_CONVERTER_H

#include <functional>
#include "filter.h"
#include "filters_pipeline.h"

/// converts filter_params to filter class
class Converter {
public:
    Converter() {}

    Converter(std::vector<FilterParameters> filters);

    void Convert(std::vector<FilterParameters> filters);

    const Pipeline GetPipeline();

protected:
    Pipeline pipeline_;
    std::map<std::string, Filter *> mp_{{"crop",      new Crop()},
                                        {"gs", new GreyScale()}};
};

#endif //IMAGE_PROCESSOR_CONVERTER_H
