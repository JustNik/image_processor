//
// Created by justnik on 29.10.2023.
//

#ifndef IMAGE_PROCESSOR_IMAGE_H
#define IMAGE_PROCESSOR_IMAGE_H

#include "pixel.h"

class Image {
public:
    /// img в public иначе очень неудобно работать с ним... да и смысл делать отдельный
    /// геттер, который будет возвращать указатель

    Pixel *img_;

    Image() : width_(0), height_(0), img_(nullptr) {}

    Image(uint32_t width, uint32_t height);

    ~Image();

    void Clear();

    void DebugPrint();

    Pixel *Get(uint32_t i, uint32_t j) const;

    void Set(uint32_t i, uint32_t j, Pixel p);

    void GreyScale() const;

//    void ApplyKernel();

    uint32_t GetWidth() const { return width_; };

    uint32_t GetHeight() const { return height_; };

    Pixel *GetImageRow(int32_t) const;

    void SetWidth(uint32_t width) { width_ = width; }

    void SetHeight(uint32_t height) { height_ = height; }

    void SetImage(Pixel *img) { img_ = img; }

protected:
    uint32_t width_;

    uint32_t height_;
};

#endif //IMAGE_PROCESSOR_IMAGE_H
