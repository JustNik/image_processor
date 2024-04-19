//
// Created by justnik on 29.10.2023.
//

#include "pixel.h"

void Pixel::Negative() {
    b_ = MAX_COLOR_VALUE - b_;
    g_ = MAX_COLOR_VALUE - g_;
    r_ = MAX_COLOR_VALUE - r_;
}

void Pixel::GreyScale() {
    r_ = b_ = g_ = 0.299 * r_ + 0.587 * g_ + 0.114 * b_;
}


