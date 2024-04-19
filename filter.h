#ifndef IMAGE_PROCESSOR_FILTER_H
#define IMAGE_PROCESSOR_FILTER_H

#include <string>
#include <vector>
#include <map>
#include "image.h"

struct FilterParameters {
    std::string filter_name;
    std::vector<std::string> params;
};

class Filter {
public:
    Filter() {}

    Filter(std::string filter_name, std::vector<std::string> filter_params)
            : filter_name_(filter_name), filter_params_(filter_params) {}

    virtual ~Filter() = default;

    virtual void Apply(Image *img) = 0;

    virtual void SetParams(std::vector<std::string> params) = 0;

protected:
    std::string filter_name_;
    std::vector<std::string> filter_params_;
};

class Crop : public Filter {
public:
    void Apply(Image *img) override;

    void SetParams(std::vector<std::string> params) override;

protected:
    uint32_t width_;
    uint32_t height_;
};

class GreyScale: public Filter {
public:
    void Apply(Image *img) override;

    void SetParams(std::vector<std::string> params) override;
};

#endif //IMAGE_PROCESSOR_FILTER_H
