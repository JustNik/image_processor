#include <stdexcept>
#include <iostream>
#include "image.h"

Pixel *Image::GetImageRow(int32_t i = 0) const {
    return &img_[i * GetWidth()];
}

Image::Image(uint32_t width, uint32_t height) {
    width_ = width;
    height_ = height;
    img_ = new Pixel[width * height];
}

Image::~Image() {
    width_ = 0;
    height_ = 0;
    delete[] img_;
    img_ = nullptr;
}

Pixel *Image::Get(uint32_t i, uint32_t j) const {
    if (i >= height_ || j >= width_) {
        throw std::invalid_argument("Invalid pixel coordinates.");
    }
    return &img_[i * width_ + j];
}

void Image::Set(uint32_t i, uint32_t j, Pixel p) {
    if (i >= height_ || j >= width_) {
        throw std::invalid_argument("Invalid pixel coordinates.");
    }
    img_[i * width_ + j] = p;
}

void Image::Clear() {
    width_ = height_ = 0;
    delete[] img_;
    img_ = nullptr;
}

void Image::DebugPrint() {
    for (uint32_t i = GetHeight() - 1; ~i; --i) {
        for (uint32_t j = 0; j < GetWidth(); ++j) {
            std::cout << static_cast<int32_t>(Get(i, j)->r_) << " " << static_cast<int32_t>(Get(i, j)->g_) << " " << static_cast<int32_t>(Get(i, j)->b_) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Image::GreyScale() const {
    for (uint32_t i = 0; i < GetHeight(); ++i) {
        for (uint32_t j = 0; j < GetWidth(); ++j) {
            Get(i, j)->GreyScale();
        }
    }
}
