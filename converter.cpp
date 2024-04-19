#include <stdexcept>
#include "converter.h"

Converter::Converter(std::vector<FilterParameters> filters) {
    Convert(filters);
}

void Converter::Convert(std::vector<FilterParameters> filters) {
    for (auto [name, params]: filters) {
        if (mp_.find(name) == mp_.end()) {
            throw std::runtime_error("Unknown filter type.");
        }
        Filter *filter = mp_[name];
        filter->SetParams(params);
        pipeline_.Add(filter);
    }
}

const Pipeline Converter::GetPipeline() {
    return pipeline_;
}

