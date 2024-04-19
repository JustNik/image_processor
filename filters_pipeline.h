//
// Created by justnik on 30.10.2023.
//

#ifndef IMAGE_PROCESSOR_FILTERS_PIPELINE_H
#define IMAGE_PROCESSOR_FILTERS_PIPELINE_H

#include "image.h"
#include "filter.h"

class Pipeline {
public:
    void Apply(Image *);

    void Add(Filter *);

protected:
    std::vector<Filter *> pipeline_;
};

#endif //IMAGE_PROCESSOR_FILTERS_PIPELINE_H
