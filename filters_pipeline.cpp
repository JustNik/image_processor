//
// Created by justnik on 30.10.2023.
//

#include "filters_pipeline.h"

void Pipeline::Apply(Image *img) {
    for (Filter *filter: pipeline_) {
        filter->Apply(img);
    }
}

void Pipeline::Add(Filter *filter) {
    pipeline_.push_back(filter);
}
