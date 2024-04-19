#include "filter.h"


void Crop::Apply(Image *img) {
    Pixel *new_img = new Pixel[width_ * height_];
    size_t ptr = 0;
    for (uint32_t i = std::max(uint32_t(), img->GetHeight() - height_); i < img->GetHeight(); ++i) {
        for (uint32_t j = 0; j < std::min(img->GetWidth(), width_); ++j) {
            new_img[ptr++] = *img->Get(i, j);
        }
    }
    delete[] img->img_;
    img->SetWidth(width_);
    img->SetHeight(height_);
    img->SetImage(new_img);
}

void Crop::SetParams(std::vector<std::string> params) {
    width_ = stoi(params[0]);
    height_ = stoi(params[1]);
}

void GreyScale::Apply(Image *img) {
    img->GreyScale();
}

void GreyScale::SetParams(std::vector<std::string> params) {
    // а что тут должно вообще быть если метод pure virtual
}
